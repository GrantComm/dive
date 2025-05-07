
import sys, textwrap
from pickle import NONE
from base_generator import *
from reformat_code import format_cpp_code


class VulkanEnumToDiveBodyGeneratorOptions(BaseGeneratorOptions):
    """Options for generating C++ functions for Vulkan FieldToDive() functions"""

    def __init__(
        self,
        blacklists=None,  # Path to JSON file listing apicalls and structs to ignore.
        platform_types=None,  # Path to JSON file listing platform (WIN32, X11, etc.) defined types.
        filename=None,
        directory='.',
        prefixText='',
        protectFile=False,
        protectFeature=True,
        extraVulkanHeaders=[]
    ):
        BaseGeneratorOptions.__init__(
            self,
            blacklists,
            platform_types,
            filename,
            directory,
            prefixText,
            protectFile,
            protectFeature,
            extraVulkanHeaders=extraVulkanHeaders
        )


# VulkanEnumToStringBodyGenerator - subclass of BaseGenerator.
# Generates C++ functions for stringifying Vulkan API enums.
class VulkanEnumToDiveBodyGenerator(BaseGenerator):
    """Generate C++ functions for Vulkan FieldToDive() functions"""

    SKIP_ENUM = [
    ]

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

        # Set of enums that have been processed since we'll encounter enums that are
        #   referenced by extensions multiple times.  This list is prepopulated with
        #   enums that should be skipped.
        self.processedEnums = set()
        self.enumType = dict()
        self.flagsType = dict()
        self.flagEnumBitsType = dict()

    # Method override
    # yapf: disable
    def beginFile(self, genOpts):
        BaseGenerator.beginFile(self, genOpts)
        body = format_cpp_code('''
            #include "generated_vulkan_enum_to_dive.h"
            #include "util/to_string.h"

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)

            using util::to_hex_fixed_width;

            template<typename TFlags, typename ToStringFunctionType>
            std::string ExpandFlags(TFlags flags, ToStringFunctionType toString)
            {
                if (flags == 0)
                {
                    return to_hex_fixed_width(flags);
                }
                uint32_t bit_number = 0;
                bool first = true;
                std::ostringstream ostr;
                while (flags != 0)
                {
                    if (flags & 1)
                    {
                        if (!first) ostr << "|";
                        ostr << toString((flags & 1) << bit_number);
                        first = false;
                    }
                    bit_number++;
                    flags = flags >> 1;
                }
                return ostr.str();
            }
        ''')
        write(body, file=self.outFile)
    # yapf: enable

    # Method override
    # yapf: disable
    def endFile(self):
        write('\n', file=self.outFile)
        self.make_decls()
        body = format_cpp_code('''
            GFXRECON_END_NAMESPACE(decode)
            GFXRECON_END_NAMESPACE(gfxrecon)
        ''')
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

    def genGroup(self, groupinfo, group_name, alias):
        BaseGenerator.genGroup(self, groupinfo, group_name, alias)
        type_elem = groupinfo.elem
        if type_elem.get('bitwidth') == '64':
            self.enumType[group_name] = 'VkFlags64'
        else:
            self.enumType[group_name] = 'VkFlags'


    def genType(self, typeinfo, name, alias):
        super().genType(typeinfo, name, alias)
        if self.is_flags(name) and alias is None:
            self.flagsType[name] = self.flags_types[name]
            bittype = typeinfo.elem.get('requires')
            if bittype is None:
                bittype = typeinfo.elem.get('bitvalues')
            if bittype is not None:
                self.flagEnumBitsType[name] = bittype
    #
    # Performs C++ code generation for the feature.
    # yapf: disable
    def make_decls(self):
        for enum in sorted(self.enum_names):
            if not enum in self.processedEnums and not enum in self.enumAliases and not enum in self.SKIP_ENUM and not enum in self.flagEnumBitsType:
                self.processedEnums.add(enum)
                bitwidth = 'VkFlags'

                if enum in self.enumType and self.enumType[enum] == 'VkFlags64':
                    body = 'void FieldToDive({0}_t, std::map<std::string, std::map<std::string, std::string>>& data_map, const {0}& value)\n'
                else:
                    body = 'void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const {0}& value)\n'
                body += '{{\n'
                    # Copy this from the vulkan_enum_to_json_body.py file
                body += '}}\n'
                body = body.format(enum, bitwidth)
                write(body, file=self.outFile)

        for enum in sorted(self.flagsType):
            bittype = None
            if enum in self.flagEnumBitsType:
                bittype = self.flagEnumBitsType[enum]
            body = 'void FieldToDive({0}_t, std::map<std::string, std::map<std::string, std::string>>& data_map, const {1} flags)\n'
            body += '{{\n'
            '''
            if bittype is not None and bittype in self.enum_names and len(self.enumEnumerants[bittype]):
                body += "    if (!options.expand_flags)\n"
                body += "    {{\n"
                body += "        data_map = to_hex_fixed_width(flags);\n"
                body += "        return;\n"
                body += "    }}\n"
                body += "    data_map = ExpandFlags(flags, []({1} flags)\n"
                body += "    {{\n"
                body += '        switch (flags)\n'
                body += '        {{\n'
                for enumerant in self.enumEnumerants[bittype]:
                    body += textwrap.indent(prefix='            ', text=textwrap.dedent('''\
                    case {0}:
                        return std::string("{0}");
                    '''.format(enumerant)))
                body += '        }}\n'
                body += '        return to_hex_fixed_width(flags);\n'
                body += '    }});\n'
            else:
                body += '    data_map = to_hex_fixed_width(flags);\n'
            '''
            body += '}}\n'
            write(body.format(enum, self.flags_types[enum]), file=self.outFile)

    # yapf: enable
