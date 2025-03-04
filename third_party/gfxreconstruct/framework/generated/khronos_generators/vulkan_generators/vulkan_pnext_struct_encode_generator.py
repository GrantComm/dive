#!/usr/bin/python3 -i
#
# Copyright (c) 2018 Valve Corporation
# Copyright (c) 2018 LunarG, Inc.
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
from base_generator import BaseGenerator, BaseGeneratorOptions, write
from khronos_encode_extended_struct_generator import KhronosEncodeExtendedStructGenerator


class EncodePNextStructGeneratorOptions(BaseGeneratorOptions):
    """Eliminates JSON black_lists and platform_types files, which are not necessary for
    pNext switch statement generation.
    Options for Vulkan API pNext structure encoding C++ code generation.
    """

    def __init__(
        self,
        filename=None,
        directory='.',
        prefix_text='',
        protect_file=False,
        protect_feature=True,
        extra_headers=[]
    ):
        BaseGeneratorOptions.__init__(
            self,
            None,
            None,
            filename,
            directory,
            prefix_text,
            protect_file,
            protect_feature,
            extra_headers=extra_headers
        )


class EncodePNextStructGenerator(BaseGenerator, KhronosEncodeExtendedStructGenerator):
    """EncodePNextStructGenerator - subclass of BaseGenerator.
    Generates C++ code for Vulkan API pNext structure encoding.
    Generate pNext structure encoding C++ code.
    """

    def __init__(
        self, err_file=sys.stderr, warn_file=sys.stderr, diag_file=sys.stdout
    ):
        BaseGenerator.__init__(
            self,
            err_file=err_file,
            warn_file=warn_file,
            diag_file=diag_file
        )

    def beginFile(self, gen_opts):
        """Method override."""
        BaseGenerator.beginFile(self, gen_opts)

        KhronosEncodeExtendedStructGenerator.write_common_headers(self, gen_opts)

        self.newline()
        write('GFXRECON_BEGIN_NAMESPACE(gfxrecon)', file=self.outFile)
        write('GFXRECON_BEGIN_NAMESPACE(encode)', file=self.outFile)
        self.newline()

        KhronosEncodeExtendedStructGenerator.write_encode_struct_definition_prefix(self)

    def endFile(self):
        """Method override."""
        KhronosEncodeExtendedStructGenerator.write_encode_struct_definition_data(self)

        self.newline()
        write('GFXRECON_END_NAMESPACE(encode)', file=self.outFile)
        write('GFXRECON_END_NAMESPACE(gfxrecon)', file=self.outFile)

        # Finish processing in superclass
        BaseGenerator.endFile(self)

    def need_feature_generation(self):
        """Indicates that the current feature has C++ code to generate."""
        if self.feature_extended_structs:
            return True
        return False

    def write_encode_struct_while_loop_statement(self, current_api_data):
        """Method Override"""
        write(
            '    while ((base != nullptr) && ((base->{} == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO) ||'.format(current_api_data.struct_type_variable),
            file=self.outFile
        )
        write(
            '                                 (base->{} == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO)))'.format(current_api_data.struct_type_variable),
            file=self.outFile
        )
