
import sys
from base_generator import *
from reformat_code import format_cpp_code, indent_cpp_code, remove_trailing_newlines


class VulkanStructToDiveHeaderGeneratorOptions(BaseGeneratorOptions):
    """Options for generating C++ functions for to_json functions"""

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


# VulkanStructToJsonHeaderGenerator - subclass of BaseGenerator.
# Generates C++ functions for stringifying Vulkan API structures.
class VulkanStructToDiveHeaderGenerator(BaseGenerator):
    """Generate C++ functions to serialize Vulkan structures to JSON"""

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

        self.customImplementationRequired = {
            'VkPipelineCacheCreateInfo',
            'VkShaderModuleCreateInfo',
            'VkPipelineExecutableStatisticKHR',
        }

    # Method override
    # yapf: disable
    def beginFile(self, genOpts):
        BaseGenerator.beginFile(self, genOpts)
        body = format_cpp_code('''
            #include "decode/custom_vulkan_struct_to_dive.h"

            GFXRECON_BEGIN_NAMESPACE(gfxrecon)
            GFXRECON_BEGIN_NAMESPACE(decode)
            ''')
        body += "\n"
        write(body, file=self.outFile)
    # yapf: enable

    # Method override
    # yapf: disable
    def endFile(self):
        body = remove_trailing_newlines(indent_cpp_code('''
            /// Works out the type of the struct at the end of a pNext pointer and dispatches
            /// recursively to the FieldToDive for that.
            void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const PNextNode* data);

            GFXRECON_END_NAMESPACE(decode)
            GFXRECON_END_NAMESPACE(gfxrecon)
        '''))
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
                body = "void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const Decoded_{0}* data);".format(struct)
                write(body, file=self.outFile)
    # yapf: enable

