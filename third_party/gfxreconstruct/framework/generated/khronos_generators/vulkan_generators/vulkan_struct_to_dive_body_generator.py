

import sys
from vulkan_base_generator import *
from khronos_struct_to_dive_body_generator import KhronosStructToDiveBodyGenerator
from reformat_code import format_cpp_code, indent_cpp_code, remove_leading_empty_lines, remove_trailing_newlines


class VulkanStructToDiveBodyGeneratorOptions(VulkanBaseGeneratorOptions):
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
        self.begin_end_file_data.specific_headers.extend((
            'generated_vulkan_struct_to_dive.h',
            'generated_vulkan_enum_to_dive.h',
            'util/to_string.h',
        ))
        self.begin_end_file_data.namespaces.extend(('gfxrecon', 'decode'))
        self.begin_end_file_data.common_api_headers = []

# VulkanStructToJsonBodyGenerator - subclass of VulkanBaseGenerator.
# Generates C++ functions for serializing Vulkan API structures to JSON.
class VulkanStructToDiveBodyGenerator(VulkanBaseGenerator, KhronosStructToDiveBodyGenerator):
    """Generate C++ functions for Vulkan FieldToJson(...) functions"""

    def __init__(
        self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout
    ):
        VulkanBaseGenerator.__init__(
            self,
            err_file=err_file,
            warn_file=warn_file,
            diag_file=diag_file
        )

        # The following structures require custom implementations for FieldToJson()
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

    def should_decode_struct(self, struct):
        """Method indended to be overridden.
        Indicates that the provided struct is a struct we want to decode"""
        return not struct in self.customImplementationRequired

    def decode_as_handle(self, parent_type, member):
        """Method indended to be overridden.
        Indicates that the given type should be decoded as a handle."""
        return (
            (
                self.is_handle(member.base_type)
                or member.name in self.formatAsHandle
            ) and not (parent_type in self.notDecoded)
        )

    # Method override
    def endFile(self):
        KhronosStructToDiveBodyGenerator.write_body_contents(self)

        # Finish processing in superclass
        VulkanBaseGenerator.endFile(self)

    #
    # Indicates that the current feature has C++ code to generate.
    def need_feature_generation(self):
        if self.feature_struct_members:
            return True
        return False
