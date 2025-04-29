#!/usr/bin/python3 -i
#
# Copyright (c) 2022-2023 LunarG, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

import sys
from vulkan_base_generator import VulkanBaseGenerator, VulkanBaseGeneratorOptions, write
from khronos_dive_consumer_body_generator import KhronosExportDiveConsumerBodyGenerator
from reformat_code import format_cpp_code, indent_cpp_code, remove_trailing_newlines


class VulkanExportDiveConsumerBodyGeneratorOptions(VulkanBaseGeneratorOptions, KhronosExportDiveConsumerBodyGenerator):
    """Options for generating a C++ class for Vulkan capture file to JSON file generation."""

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
            'generated/generated_vulkan_dive_consumer.h',
        ))
        self.begin_end_file_data.namespaces.extend(('gfxrecon', 'decode'))


class VulkanExportDiveConsumerBodyGenerator(VulkanBaseGenerator, KhronosExportDiveConsumerBodyGenerator):
    """VulkanExportDiveConsumerBodyGenerator - subclass of VulkanBaseGenerator.
    Generates C++ member definitions for the VulkanExportDiveConsumer class responsible for
    generating a textfile containing decoded Vulkan API call parameter data.
    Generate a C++ class for Vulkan capture file to Dive generation.
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

        self.customImplementationRequired = {
            'vkCmdBuildAccelerationStructuresIndirectKHR',
            'vkCmdPushConstants',
            'vkCreatePipelineCache',
            'vkCreateShaderModule',
            'vkGetPipelineCacheData',
        }

        self.formatAsHex = {
            'VkDeviceAddress',
        }

        # Parameters using this name should be output as handles even though they are uint64_t
        self.formatAsHandle = {
            'objectHandle',
        }

        self.queueSubmit = {
            "vkQueueSubmit",
            "vkQueueSubmit2",
            "vkQueuePresentKHR",
            "vkQueueSubmit2KHR",
            }

    def endFile(self):
        """Method override."""
        # TODO: Each code generator is passed a blacklist like framework\generated\vulkan_generators\blacklists.json
        # of functions and structures not to generate code for. Once the feature is implemented, the following can be
        # replaced with adding vkCreateRayTracingPipelinesKHR in corresponding blacklist.
        if 'vkCreateRayTracingPipelinesKHR' in self.APICALL_BLACKLIST:
            self.APICALL_BLACKLIST.remove('vkCreateRayTracingPipelinesKHR')

        KhronosExportDiveConsumerBodyGenerator.generate_content(self)

        # Finish processing in superclass
        VulkanBaseGenerator.endFile(self)

    def need_feature_generation(self):
        """Indicates that the current feature has C++ code to generate."""
        if self.feature_cmd_params:
            return True
        return False

    def skip_generating_command_json(self, command):
        """Method override"""
        return command in self.customImplementationRequired

    def decode_as_handle(self, value):
        """Method override
        Indicates that the given type should be decoded as a handle."""
        return (
            (
                self.is_handle_like(value.base_type)
                or value.name in self.formatAsHandle
            )
        )

    def decode_as_hex(self, value):
        """Method override"""
        return value.base_type in self.formatAsHex

    # yapf: disable
    def make_consumer_func_body(self, return_type, name, values):
        """Return class member function definition."""
        body = ''
        body += KhronosExportDiveConsumerBodyGenerator.make_consumer_func_body(self, return_type, name, values)
        if KhronosExportDiveConsumerBodyGenerator.is_command_buffer_cmd(self, name):
            body += '    uint32_t cmd_buffer_index = GetCommandBufferRecordIndex(commandBuffer);\n'
        return body
    # yapf: enable
