
import sys
from vulkan_base_generator import *
from khronos_enum_to_dive_header_generator import KhronosEnumToDiveHeaderGenerator
from reformat_code import format_cpp_code

class VulkanEnumToDiveHeaderGeneratorOptions(VulkanBaseGeneratorOptions):
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
        extra_headers=[]
    ):
        VulkanBaseGeneratorOptions.__init__(
            self,
            blacklists,
            platform_types,
            filename,
            directory,
            prefixText,
            protectFile,
            protectFeature,
            extra_headers=extra_headers
        )
        
        self.begin_end_file_data.specific_headers.extend((
            'format/platform_types.h',
        ))

        self.begin_end_file_data.system_headers.extend((
            'string',
            'map',
        ))

        #include <map>
#include <string>

        self.begin_end_file_data.namespaces.extend(('gfxrecon', 'decode'))



# VulkanEnumToStringHeaderGenerator - subclass of VulkanBaseGenerator.
# Generates C++ functions for stringifying Vulkan API enums.
class VulkanEnumToDiveHeaderGenerator(VulkanBaseGenerator, KhronosEnumToDiveHeaderGenerator):
    """Generate C++ functions to serialize Vulkan enumaration to JSON"""

    SKIP_ENUM = [
    ]

    def __init__(
        self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout
    ):
        VulkanBaseGenerator.__init__(
            self,
            err_file=err_file,
            warn_file=warn_file,
            diag_file=diag_file
        )

    # Method override
    def endFile(self):
        self.newline()
        KhronosEnumToDiveHeaderGenerator.make_decls(self)
        self.newline()

        # Finish processing in superclass
        VulkanBaseGenerator.endFile(self)

    #
    # Indicates that the current feature has C++ code to generate.
    def need_feature_generation(self):
        if self.feature_struct_members:
            return True
        return False
