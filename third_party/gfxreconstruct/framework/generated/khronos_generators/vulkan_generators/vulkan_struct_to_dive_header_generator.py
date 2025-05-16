

import sys
from vulkan_base_generator import *
from khronos_struct_to_dive_header_generator import KhronosStructToDiveHeaderGenerator
from reformat_code import format_cpp_code, indent_cpp_code, remove_trailing_newlines


class VulkanStructToDiveHeaderGeneratorOptions(VulkanBaseGeneratorOptions):
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
        extra_headers=[]
    ):
        VulkanBaseGeneratorOptions.__init__(
            self,
            blacklists,
            platform_types,
            filename,
            directory,
            prefix_text,
            protect_file,
            protect_feature,
            extra_headers=extra_headers
        )
        self.begin_end_file_data.specific_headers.append('decode/custom_vulkan_struct_to_dive.h')
        self.begin_end_file_data.namespaces.extend(('gfxrecon', 'decode'))
        self.begin_end_file_data.common_api_headers = []


# VulkanStructToJsonHeaderGenerator - subclass of VulkanBaseGenerator.
# Generates C++ functions for stringifying Vulkan API structures.
class VulkanStructToDiveHeaderGenerator(
    VulkanBaseGenerator, KhronosStructToDiveHeaderGenerator
):
    """Generate C++ functions to serialize Vulkan structures to JSON"""

    def __init__(
        self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout
    ):
        VulkanBaseGenerator.__init__(
            self, err_file=err_file, warn_file=warn_file, diag_file=diag_file
        )

        self.customImplementationRequired = {
            'VkPipelineCacheCreateInfo',
            'VkShaderModuleCreateInfo',
            'VkPipelineExecutableStatisticKHR',
        }

    def should_decode_struct(self, struct):
        """Method override"""
        return not struct in self.customImplementationRequired


    # Method override
    def endFile(self):
        KhronosStructToDiveHeaderGenerator.write_header_contents(self)

        # Finish processing in superclass
        VulkanBaseGenerator.endFile(self)

    #
    # Indicates that the current feature has C++ code to generate.
    def need_feature_generation(self):
        if self.feature_struct_members:
            return True
        return False
