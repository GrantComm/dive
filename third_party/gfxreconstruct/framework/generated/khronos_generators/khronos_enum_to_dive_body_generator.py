

import sys, textwrap
from khronos_base_generator import write
from reformat_code import format_cpp_code


# KhronosEnumToJsonBodyGenerator
# Generates C++ functions for stringifying Khronos API enums.
class KhronosEnumToDiveBodyGenerator():
    """Generate C++ functions to serialize Khronos enumaration to JSON"""

    def skip_generating_enum_to_dive_for_type(self, type):
        """ Method may be overridden"""
        return False

    def make_decls(self):
        body = format_cpp_code(
            '''
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
        '''
        )
        write(body, file=self.outFile)
        self.newline()
        self.newline()

        # Set of enums that have been processed since we'll encounter enums that are
        #   referenced by extensions multiple times.  This list is prepopulated with
        #   enums that should be skipped.
        processedEnums = set()

        for enum in sorted(self.enum_names):
            if enum in self.processedEnums or enum in self.enumAliases or enum in self.SKIP_ENUM or self.skip_generating_enum_to_dive_for_type(
                enum
            ):
                continue

            self.processedEnums.add(enum)

            if self.is_flags_enum_64bit(enum):
                body = 'void FieldToDive({0}_t, std::map<std::string, std::map<std::string, std::string>>& data_map, const {0}& value)\n'
            else:
                body = 'void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const {0}& value)\n'
            body += '{{\n'
            # Copy this from the khronos_enum_to_json_body.py file
            body += '}}\n'
            body = body.format(enum)
            write(body, file=self.outFile)

        for flag in sorted(self.flags_types):
            if flag in self.flags_type_aliases or self.skip_generating_enum_to_dive_for_type(flag):
                continue

            bittype = None
            if flag in self.flags_to_enum_bits:
                bittype = self.flags_to_enum_bits[flag]

            body = 'void FieldToDive({0}_t, std::map<std::string, std::map<std::string, std::string>>& data_map, const {1} flags)\n'
            body += '{{\n'
            # Copy this from the khronos_enum_to_json_body.py file
            body += '}}\n'
            write(body.format(flag, self.flags_types[flag]), file=self.outFile)
