
import sys
from khronos_base_generator import write


# KhronosEnumToDiveHeaderGenerator
# Generates C++ functions for stringifying Khronos API enums.
class KhronosEnumToDiveHeaderGenerator():
    """Generate C++ functions to serialize Khronos enumaration to JSON"""

    def skip_generating_enum_to_dive_for_type(self, type):
        """ Method may be overridden"""
        return False

    def make_decls(self):
        # Set of enums that have been processed since we'll encounter enums that are
        #   referenced by extensions multiple times.  This list is prepopulated with
        #   enums that should be skipped.
        processedEnums = set()

        for flag in sorted(self.flags_types):
            if flag in self.flags_type_aliases or self.skip_generating_enum_to_dive_for_type(
                flag
            ):
                continue
            body = 'struct {0}_t {{ }};'
            write(body.format(flag), file=self.outFile)

        for enum in sorted(self.enum_names):
            if enum in self.enumAliases or self.skip_generating_enum_to_dive_for_type(
                enum
            ):
                continue
            if self.is_flags_enum_64bit(enum):
                body = 'struct {0}_t {{ }};'
                write(body.format(enum), file=self.outFile)

        self.newline()
        for enum in sorted(self.enum_names):
            if enum in processedEnums or enum in self.SKIP_ENUM or self.skip_generating_enum_to_dive_for_type(
                enum
            ):
                continue
            processedEnums.add(enum)
            if not enum in self.enumAliases:
                if self.is_flags_enum_64bit(enum):
                    body = 'void FieldToDive({0}_t, std::map<std::string, std::map<std::string, std::string>>& data_map, const {0}& value);'
                else:
                    body = 'void FieldToDive(std::map<std::string, std::map<std::string, std::string>>& data_map, const {0}& value);'
                write(body.format(enum), file=self.outFile)

        for flag in sorted(self.flags_types):
            if flag in self.flags_type_aliases or self.skip_generating_enum_to_dive_for_type(flag):
                continue
            body = 'void FieldToDive({0}_t, std::map<std::string, std::map<std::string, std::string>>& data_map, const {1} flags);'
            write(body.format(flag, self.flags_types[flag]), file=self.outFile)
