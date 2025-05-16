
from khronos_base_generator import write
from reformat_code import indent_cpp_code, remove_leading_empty_lines, remove_trailing_newlines

class KhronosStructToDiveBodyGenerator():
    """KhronosStructToDiveBodyGenerator
    Generate C++ function definitions to serialize Khronos structures to JSON"""

    def should_decode_struct(self, struct):
        """Method indended to be overridden.
        Indicates that the provided struct is a struct we want to decode"""
        return True

    def get_local_type_var_name(self):
        return 's_type'

    def decode_as_handle(self, parent_type, member):
        """ Method which may be overridden.
        Indicates that the given type should be decoded as a handle."""
        return self.is_handle(member.base_type)

    def write_body_contents(self):
        write('using util::to_hex_variable_width;', file=self.outFile)
        write('using util::uuid_to_string;', file=self.outFile)
        self.newline()

        for struct in self.get_all_filtered_struct_names():
            if self.should_decode_struct(struct):
                body = indent_cpp_code('''
                    void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const Decoded_{0}* data)
                    {{
                        if (data && data->decoded_value)
                        {{
                            const {0}& decoded_value = *data->decoded_value;
                            const Decoded_{0}& meta_struct = *data;
                    '''.format(struct))

                if struct in self.children_structs:
                    body += self.make_base_struct_body(struct)

                body += self.makeStructBody(
                    struct, self.all_struct_members[struct]
                )

                body += '    }\n'
                body += '}\n'

                body = remove_trailing_newlines(body)
                write(body, file=self.outFile)

        stype_var = self.get_struct_type_var_name()
        extended_type_prefix = self.get_extended_struct_func_prefix()
        stype_auto = self.get_local_type_var_name()
        base_in_struct = self.get_base_input_structure_name()
        
        body = '''
            void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const {}Node* data)
            {{
                if (data && data->GetPointer())
                {{
        '''.format(extended_type_prefix)
        body += '            const auto {} = reinterpret_cast<const {}*>(data->GetPointer())->{};'.format(
            stype_auto, base_in_struct, stype_var
        )
        body += '''
                    switch ({})
                    {{'''.format(stype_auto)
        body += self.make_extended_struct_body()
        body = indent_cpp_code(body)
        write(body, file=self.outFile)

    def make_base_struct_body(
            self,
            base_struct_type,
            indent = '    ',
            decoded_value='decoded_value',
            data='data',
            data_map='data_map'):
        # Otherwise, we need to go through and actually decode the appropriate
        # type of the struct pointed at by the base header struct pointer.
        body = ''
        indent1 = indent + '    '
        indent2 = indent1 + '    '

        body += f'{indent1}switch ({decoded_value}.type)\n'
        body += f'{indent1}{{\n'
        body += f'{indent2}default:\n'
        body += f'{indent2}    // Handle as base-type below\n'
        body += f'{indent2}    break;\n'

        for child in self.children_structs[base_struct_type]:
            struct_type = self.struct_type_names[child]
            body += f'{indent2}case {struct_type}:\n'
            body += f'{indent2}    FieldToDive({data_map},\n'
            body += f'{indent2}                reinterpret_cast<const Decoded_{child}*>({data}));\n'
            body += f'{indent2}    // Return here because we processed the appropriate data in\n'
            body += f'{indent2}    // the correct structure type\n'
            body += f'{indent2}    return;\n'

        body += f'{indent1}}}\n\n'

        return body


    #
    # Command definition
    def makeStructBody(self, name, values):
        body = ''
        has_extended_struct = False
        extended_struct_var_name = self.get_extended_struct_var_name()
        for value in values:
            type_name = self.make_decoded_param_type(value)

            # Determine the appropriate type.  If it's an alias, get
            # the original type
            value_type = value.base_type
            if (self.is_struct(value.base_type) and value.base_type in self.all_struct_aliases):
                value_type = self.all_struct_aliases[value.base_type]
            flagsEnumType = value_type

            if value.name == extended_struct_var_name:
                has_extended_struct = True
                continue

            # Default to getting the data from the native Vulkan struct:
            to_dive = 'FieldToDive(data_map, decoded_value.{0})'

            if (
                self.is_function_ptr(value_type)
                or ('pUserData' == value.name or 'userData' == value.name)
            ):
                to_dive = 'FieldToDive(data_map, to_hex_variable_width(meta_struct.{0}))'
            elif value.is_pointer:
                if 'String' in type_name:
                    to_dive = 'FieldToDive(data_map, &meta_struct.{0})'
                elif self.is_handle_like(value_type):
                    to_dive = 'HandleToDive(data_map, &meta_struct.{0})'
                else:
                    to_dive = 'FieldToDive(data_map, meta_struct.{0})'
            else:
                if value.is_array:
                    if 'UUID' in value.array_length or 'LUID' in value.array_length:
                        to_dive = 'FieldToDive(data_map, uuid_to_string(sizeof(decoded_value.{0}), decoded_value.{0}))'
                    elif 'String' in type_name:
                        to_dive = 'FieldToDive(data_map, &meta_struct.{0})'
                    elif self.is_handle_like(value_type):
                        to_dive = 'HandleToDive(data_map, &meta_struct.{0})'
                    elif self.is_struct(value_type):
                        # If this is a parent class, generate the parent->child conversion info
                        # appropriately
                        if value_type in self.children_structs.keys():
                            to_dive = 'ParentChildFieldToDive(args, {0})'
                        else:
                            to_dive = 'FieldToDive(data_map, meta_struct.{0})'
                    elif not value.is_dynamic:
                        to_dive = 'FieldToDive(data_map, &meta_struct.{0})'
                    else:
                        to_dive = 'FieldToDive(data_map, meta_struct.{0})'
                else:
                    if self.decode_as_handle(name, value):
                        to_dive = 'HandleToDive(data_map, meta_struct.{0})'
                    elif value_type in self.formatAsHex:
                        to_dive = 'FieldToDive(data_map, to_hex_variable_width(decoded_value.{0}))'
                    elif self.is_struct(value_type):
                        to_dive = 'FieldToDive(data_map, meta_struct.{0})'
                    elif self.is_flags(value_type):
                        if value_type in self.flags_type_aliases:
                            flagsEnumType = self.flags_type_aliases[
                                value_type]
                        to_dive = 'FieldToDive({2}_t(),data_map, decoded_value.{0})'
                    elif self.is_enum(value_type):
                        to_dive = 'FieldToDive(data_map, decoded_value.{0})'
                    elif self.is_boolean_type(value_type):
                        '''
                        to_dive = 'data_map = static_cast<bool>(decoded_value.{0})'
                        '''

            to_dive = to_dive.format(
                value.name, value_type, flagsEnumType
            )
            body += '        {0};\n'.format(to_dive)

        # Handle the extended struct last
        if has_extended_struct:
            body += '        FieldToDive(data_map, meta_struct.{0});\n'.format(
                extended_struct_var_name
            )

        return body

    def make_extended_struct_body(self):
        body = ''
        var_name = self.get_extended_struct_var_name().lower()
        stype_auto = self.get_local_type_var_name()

        extended_list = []
        for struct in self.all_extended_structs:
            for ext_struct in self.all_extended_structs[struct]:
                if ext_struct not in extended_list and ext_struct not in self.all_struct_aliases:
                    extended_list.append(ext_struct)

        for struct in sorted(extended_list):
            if struct not in self.struct_type_names:
                continue
            body += '''
            case {1}:
            {{
               const auto* {2} = reinterpret_cast<const Decoded_{0}*>(data->GetMetaStructPointer());
               FieldToDive(data_map, {2});
               break;
            }}
            '''.format(struct, self.struct_type_names[struct], var_name)
        body += '\n'
        body += '            default:\n'
        body += '            {\n'
        body += '                GFXRECON_LOG_WARNING("Unknown {} node type: %u.", (unsigned) {});\n'.format(
            var_name, stype_auto
        )
        body += '            }\n'
        body += '        }\n'
        body += '    }\n'
        body += '}\n'
        return body
