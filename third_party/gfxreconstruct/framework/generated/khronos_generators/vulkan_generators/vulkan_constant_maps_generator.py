#!/usr/bin/python3 -i

import sys
from vulkan_base_generator import VulkanBaseGenerator, VulkanBaseGeneratorOptions, write


class VulkanConstantMapsGeneratorOptions(VulkanBaseGeneratorOptions):
    """Adds the following new option:
    is_override - Specify whether the member function declarations are
                  virtual function overrides or pure virtual functions.
    Options for generating C++ class declarations for Vulkan parameter processing.
    """

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
            'util/defines.h',
        ))
        self.begin_end_file_data.system_headers.extend((
            'unordered_map',
            'vector',
        ))
        self.begin_end_file_data.namespaces.extend(('gfxrecon', 'decode'))


class VulkanConstantMapsGenerator(VulkanBaseGenerator):
    """VulkanColorspaceMapGenerator - subclass of VulkanBaseGenerator.
    """

    def __init__(
        self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout
    ):
        VulkanBaseGenerator.__init__(
            self,
            err_file=err_file,
            warn_file=warn_file,
            diag_file=diag_file
        )

    def beginFile(self, gen_opts):
        """Method override."""
        VulkanBaseGenerator.beginFile(self, gen_opts)

        self.newline()

        colorspace_extensions_names = set()
        colorspace_extension_map = dict.fromkeys(
            filter(
                lambda enum_value: 'VK_COLOR_SPACE' in enum_value,
                self.registry.enumdict
            )
        )
        colorspace_extension_map.pop(
            'VK_COLOR_SPACE_SRGB_NONLINEAR_KHR'
        )  # Remove the core provided color space from extension map
        for extension in self.registry.extensions:
            colorspace_enum = filter(
                lambda element: 'VK_COLOR_SPACE' in element.get('name'),
                extension.findall('require/enum')
            )
            colorspace_enum = map(
                lambda element: element.get('name'), colorspace_enum
            )
            for name in colorspace_enum:
                value = extension.get("name")
                colorspace_extensions_names.add(value)
                colorspace_extension_map[name] = f'"{value}"'

        write(
            'static const std::unordered_map<VkColorSpaceKHR, const char *> kColorSpaceExtensionMap = {',
            file=self.outFile
        )
        for key, value in colorspace_extension_map.items():
            write(f'{{{key}, {value}}},', file=self.outFile)
        write('};', file=self.outFile)
        self.newline()

        write(
            'static const std::vector<const char *> kColorSpaceExtensionNames = {',
            file=self.outFile
        )
        for extension_name in sorted(colorspace_extensions_names):
            write(f'"{extension_name}",', file=self.outFile)
        write('};', file=self.outFile)
        self.newline()
