

import sys
from base_generator import *
from reformat_code import format_cpp_code, indent_cpp_code, remove_leading_empty_lines, remove_trailing_newlines

class VulkanStructToDiveBodyGeneratorOptions(BaseGeneratorOptions):
    """Options for generating C++ functions for serializing Vulkan structures to JSON"""

    def __init__(
        self,
        blacklists=None,  # Path to JSON file listing apicalls and structs to ignore.
        platform_types=None,  # Path to JSON file listing platform (WIN32, X11, etc.) defined types.
        filename=None,
        directory='.',
        prefix_text='',
        protect_file=False,
        protect_feature=True,
        extraVulkanHeaders=[]
    ):
        BaseGeneratorOptions.__init__(
            self,
            blacklists,
            platform_types,
            filename,
            directory,
            prefix_text,
            protect_file,
            protect_feature,
            extraVulkanHeaders=extraVulkanHeaders
        )


# VulkanStructToDiveBodyGenerator - subclass of BaseGenerator.
# Generates C++ functions for serializing Vulkan API structures to JSON.
class VulkanStructToDiveBodyGenerator(BaseGenerator):
    """Generate C++ functions for Vulkan FieldToDive(...) functions"""

    def __init__(
        self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout
    ):
        BaseGenerator.__init__(
            self,
            process_cmds=False,
            process_structs=True,
            feature_break=True,
            err_file=err_file,
            warn_file=warn_file,
            diag_file=diag_file
        )

        # The following structures require custom implementations for FieldToDive()
        self.customImplementationRequired = {
            'VkPipelineCacheCreateInfo',
            'VkShaderModuleCreateInfo',
            'VkPipelineExecutableStatisticKHR',
        }

        self.formatAsHex = {
            'VkDeviceAddress',
        }

        # Fields using this name should be output as handles even though they are uint64_t
        self.formatAsHandle = {
            'objectHandle',
        }

        # Struct types here do not have decoded fields.
        self.notDecoded = {
            'VkDeviceMemoryReportCallbackDataEXT',
        }

        self.pnext_extension_structs = dict()
        self.flagsType = dict()
        self.flagsTypeAlias = dict()
        self.flagEnumBitsType = dict()

    # Method override
    # yapf: disable
    def beginFile(self, genOpts):
        BaseGenerator.beginFile(self, genOpts)
        body = format_cpp_code('''
            #include "generated_vulkan_struct_to_dive.h"
            #include "generated_vulkan_enum_to_dive.h"
            #include "util/to_string.h"

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)
            using util::to_hex_variable_width;
            using util::uuid_to_string;
        ''')
        body += "\n"
        write(body, file=self.outFile)
    # yapf: enable

    # Method override
    # yapf: disable
    def endFile(self):
        body = '''
            void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const PNextNode* data)
            {
                if (data && data->GetPointer())
                {
                    const auto s_type = reinterpret_cast<const VkBaseInStructure*>(data->GetPointer())->sType;
                    switch (s_type)
                    {'''
        body += self.make_pnext_body()
        body += '''
                        default:
                        {
                            GFXRECON_LOG_WARNING("Unknown pnext node type: %u.", (unsigned) s_type);
                        }
                    }
                }
            }

            GFXRECON_END_NAMESPACE(decode)
            GFXRECON_END_NAMESPACE(gfxrecon)
        '''
        body = remove_trailing_newlines(indent_cpp_code(body))
        write(body, file=self.outFile)

        # Finish processing in superclass
        BaseGenerator.endFile(self)
    # yapf: enable

    #
    # Indicates that the current feature has C++ code to generate.
    def need_feature_generation(self):
        self.feature_break = False
        if self.feature_struct_members:
            return True
        return False

    #
    # Performs C++ code generation for the feature.
    # yapf: disable
    def generate_feature(self):
        for struct in self.get_filtered_struct_names():
            if not struct in self.customImplementationRequired:
                body = '''
                    void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const Decoded_{0}* data)
                    {{
                        if (data && data->decoded_value)
                        {{
                            const {0}& decoded_value = *data->decoded_value;
                            const Decoded_{0}& meta_struct = *data;

                    '''.format(struct)
                body += self.makeStructBody(struct, self.feature_struct_members[struct])
                body += remove_leading_empty_lines('''
                        }
                    }
                    ''')
                body = remove_trailing_newlines(indent_cpp_code(body))
                write(body, file=self.outFile)
    # yapf: enable

    #
    # Command definition
    # yapf: disable
    def makeStructBody(self, name, values):
        body = ''
        has_pnext = False
        for value in values:
            type_name = self.make_decoded_param_type(value)
            flagsEnumType = value.base_type

            if value.name == 'pNext':
                # move pnext to be the last member
                has_pnext = True
                continue

            # Default to getting the data from the native Vulkan struct:
            to_dive = 'FieldToDive(data_map, decoded_value.{0})'

            if 'pfn' in value.name or 'pUserData' in value.name:
                to_dive = 'FieldToDive(data_map, to_hex_variable_width(meta_struct.{0}))'
            elif value.is_pointer:
                if 'String' in type_name:
                    to_dive = 'FieldToDive(data_map, &meta_struct.{0})'
                elif self.is_handle(value.base_type):
                    to_dive = 'HandleToDive(data_map, &meta_struct.{0})'
                else:
                    to_dive = 'FieldToDive(data_map, meta_struct.{0})'
            else:
                if value.is_array:
                    if 'UUID' in value.array_length or 'LUID' in value.array_length:
                        to_dive = 'FieldToDive(data_map, uuid_to_string(sizeof(decoded_value.{0}), decoded_value.{0}))'
                    elif 'String' in type_name:
                        to_dive = 'FieldToDive(data_map, &meta_struct.{0})'
                    elif self.is_handle(value.base_type):
                        to_dive = 'HandleToDive(data_map, &meta_struct.{0})'
                    elif self.is_struct(value.base_type):
                        to_dive = 'FieldToDive(data_map, meta_struct.{0})'
                    elif not value.is_dynamic:
                        to_dive = 'FieldToDive(data_map, &meta_struct.{0})'
                    else:
                        to_dive = 'FieldToDive(data_map, meta_struct.{0})'
                else:
                    if (self.is_handle(value.base_type) or value.name in self.formatAsHandle) and not (name in self.notDecoded):
                        to_dive = 'HandleToDive(data_map, meta_struct.{0})'
                    elif value.base_type in self.formatAsHex:
                        to_dive = 'FieldToDive(data_map, to_hex_variable_width(decoded_value.{0}))'
                    elif self.is_struct(value.base_type):
                        to_dive = 'FieldToDive(data_map, meta_struct.{0})'
                    elif self.is_flags(value.base_type):
                        if value.base_type in self.flagsTypeAlias:
                            flagsEnumType = self.flagsTypeAlias[value.base_type]
                        to_dive = 'FieldToDive({2}_t(),data_map, decoded_value.{0})'
                    elif self.is_enum(value.base_type):
                        to_dive = 'FieldToDive(data_map, decoded_value.{0})'
                    elif 'VkBool32' == value.base_type:
                        to_dive = 'data_map = static_cast<bool>(decoded_value.{0})'

            to_dive = to_dive.format(value.name, value.base_type, flagsEnumType)
            body += '        {0};\n'.format(to_dive)
        # Save pnext as last member
        if has_pnext:
            body += '        FieldToDive(data_map, meta_struct.pNext);\n'

        return body
    # yapf: enable

    def genStruct(self, typeinfo, typename, alias):
        super().genStruct(typeinfo, typename, alias)

        if not alias:
            if typeinfo.elem.get('structextends'):
                pnext_extension_struct = self.make_structure_type_enum(typeinfo, typename)
                if pnext_extension_struct:
                    self.pnext_extension_structs[typename] = pnext_extension_struct

    def genType(self, typeinfo, name, alias):
        super().genType(typeinfo, name, alias)
        if self.is_flags(name):
            if alias is None:
                self.flagsType[name] = self.flags_types[name]
                bittype = typeinfo.elem.get('requires')
                if bittype is None:
                    bittype = typeinfo.elem.get('bitvalues')
                if bittype is not None:
                    self.flagEnumBitsType[bittype] = name
            else:
                self.flagsTypeAlias[name] = alias

    def make_pnext_body(self):
        body = ''
        for struct in self.pnext_extension_structs:
            body += '''
            case {1}:
            {{
               const auto* pnext = reinterpret_cast<const Decoded_{0}*>(data->GetMetaStructPointer());
               FieldToDive(data_map, pnext);
               break;
            }}
            '''.format(struct, self.pnext_extension_structs[struct])
        return body
