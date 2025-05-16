
from khronos_base_generator import write

class KhronosStructToDiveHeaderGenerator():
    """KhronosStructToJsonHeaderGenerator
    Generate C++ function declarations to serialize Khronos structures to JSON"""

    def should_decode_struct(self, struct):
        """Method indended to be overridden.
        Indicates that the provided struct is a struct we want to decode"""
        return True

    def write_parent_child_to_dive_func(self):
        struct_type = self.get_struct_type_enum_name()
        body = '\n'
        body += 'template <typename T>\n'
        body += 'void ParentChildFieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const T* data)\n'
        body += '{\n'
        body += '    // First read in the type to know which child we need to handle\n'
        body += f'    {struct_type} struct_type;\n'
        body += '    FieldToDive(data_map["type"], struct_type, options);\n'
        body += '\n'
        body += '    switch (struct_type)\n'
        body += '    {\n'
        body += '        default:\n'
        body += '        {\n'
        body += '            GFXRECON_LOG_WARNING("ParentChildFieldToDive: unrecognized child structure type %d", struct_type);\n'
        body += '            break;\n'
        body += '        }\n'
        for child_list in self.children_structs:
            for child in self.children_structs[child_list]:
                struct_type_name = self.struct_type_names[child]
                body += f'        case {struct_type_name}:\n'
                body += '        {\n'
                body += f'            FieldToDive(data_map, reinterpret_cast<const Decoded_{child}*>(data), options);\n'
                body += '            break;\n'
                body += '        }\n'
        body += '    }\n'
        body += '}\n'
        write(body, file=self.outFile)

    def write_header_contents(self):
        for struct in self.get_all_filtered_struct_names():
            if self.should_decode_struct(struct):
                body = "void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const Decoded_{0}* data);".format(struct)
                write(body, file=self.outFile)
        self.newline()

        # If there are parent/child structs, write the utility function to help
        if len(self.children_structs) > 0:
            self.write_parent_child_to_json_func()

        var_name = self.get_extended_struct_var_name()
        prefix = self.get_extended_struct_func_prefix()
        if len(var_name) > 0 and len(prefix) > 0:
            write(f'/// Works out the type of the struct at the end of a {var_name} pointer and dispatches', file=self.outFile)
            write('/// recursively to the FieldToDive for that.', file=self.outFile)
            write(f'void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const {prefix}Node* data);', file=self.outFile)
