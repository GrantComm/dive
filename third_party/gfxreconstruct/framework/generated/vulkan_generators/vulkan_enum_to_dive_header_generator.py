
import sys
from base_generator import *
from reformat_code import format_cpp_code

class VulkanEnumToDiveHeaderGeneratorOptions(BaseGeneratorOptions):
    """Options for generating C++ functions for Vulkan ToString() functions"""

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


# VulkanEnumToStringHeaderGenerator - subclass of BaseGenerator.
# Generates C++ functions for stringifying Vulkan API enums.
class VulkanEnumToDivenHeaderGenerator(BaseGenerator):
    """Generate C++ functions to serialize Vulkan enumaration to JSON"""

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
        self.flagBitsType = dict()

    # Method override
    # yapf: disable
    def beginFile(self, genOpts):
        BaseGenerator.beginFile(self, genOpts)
        includes = format_cpp_code('''
            #include "format/platform_types.h"
            #include "util/dive_util.h"

            '''
        )

        write(includes, file=self.outFile)
        self.includeVulkanHeaders(genOpts)
        write("", file=self.outFile)
        namespace = format_cpp_code('''
            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)
            ''')
        write(namespace, file=self.outFile)
    # yapf: enable

    # Method override
    # yapf: disable
    def endFile(self):
        self.newline()
        self.make_decls()

        self.newline()
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
                self.flagBitsType[bittype] = name

    def make_decls(self):
        for flag in sorted(self.flagsType):
            body = 'struct {0}_t {{ }};'
            write(body.format(flag), file=self.outFile)


        for enum in sorted(self.enum_names):
            if not enum in self.enumAliases:
                if enum in self.enumType and self.enumType[enum] == 'VkFlags64':
                    body = 'struct {0}_t {{ }};'
                    write(body.format(enum), file=self.outFile)

        self.newline()
        for enum in sorted(self.enum_names):
            if not enum in self.processedEnums and not enum in self.SKIP_ENUM:
                self.processedEnums.add(enum)
                if not enum in self.enumAliases:
                    if enum in self.enumType and self.enumType[enum] == 'VkFlags64':
                        body = 'void FieldToDive({0}_t, std::map<std::string, std::map<std::string, std::string>>& data_map, const {0}& value);'
                    else:
                        body = 'void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const {0}& value);'
                    write(body.format(enum), file=self.outFile)

        for flag in sorted(self.flagsType):
            body = 'void FieldToDive({0}_t, std::map<std::string, std::map<std::string, std::string>>& data_map, const {1} flags);'
            write(body.format(flag, self.flagsType[flag]), file=self.outFile)
