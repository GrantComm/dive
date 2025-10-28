/*
 * Copyright © 2018 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */
#include <ctype.h>

#include "glsl_types.h"
#include "linker_util.h"
#include "util/bitscan.h"
#include "util/set.h"
#include "util/u_range_remap.h"
#include "main/consts_exts.h"

void
linker_error(gl_shader_program *prog, const char *fmt, ...)
{
   va_list ap;

   ralloc_strcat(&prog->data->InfoLog, "error: ");
   va_start(ap, fmt);
   ralloc_vasprintf_append(&prog->data->InfoLog, fmt, ap);
   va_end(ap);

   prog->data->LinkStatus = LINKING_FAILURE;
}

void
linker_warning(gl_shader_program *prog, const char *fmt, ...)
{
   va_list ap;

   ralloc_strcat(&prog->data->InfoLog, "warning: ");
   va_start(ap, fmt);
   ralloc_vasprintf_append(&prog->data->InfoLog, fmt, ap);
   va_end(ap);

}

void
link_shaders_init(struct gl_context *ctx, struct gl_shader_program *prog)
{
   prog->data->LinkStatus = LINKING_SUCCESS; /* All error paths will set this to false */
   prog->data->Validated = false;

   /* Section 7.3 (Program Objects) of the OpenGL 4.5 Core Profile spec says:
    *
    *     "Linking can fail for a variety of reasons as specified in the
    *     OpenGL Shading Language Specification, as well as any of the
    *     following reasons:
    *
    *     - No shader objects are attached to program."
    *
    * The Compatibility Profile specification does not list the error.  In
    * Compatibility Profile missing shader stages are replaced by
    * fixed-function.  This applies to the case where all stages are
    * missing.
    */
   if (prog->NumShaders == 0) {
      if (ctx->API != API_OPENGL_COMPAT)
         linker_error(prog, "no shaders attached to the program\n");
      return;
   }
}

/**
 * Given a string identifying a program resource, break it into a base name
 * and an optional array index in square brackets.
 *
 * If an array index is present, \c out_base_name_end is set to point to the
 * "[" that precedes the array index, and the array index itself is returned
 * as a long.
 *
 * If no array index is present (or if the array index is negative or
 * mal-formed), \c out_base_name_end, is set to point to the null terminator
 * at the end of the input string, and -1 is returned.
 *
 * Only the final array index is parsed; if the string contains other array
 * indices (or structure field accesses), they are left in the base name.
 *
 * No attempt is made to check that the base name is properly formed;
 * typically the caller will look up the base name in a hash table, so
 * ill-formed base names simply turn into hash table lookup failures.
 */
long
link_util_parse_program_resource_name(const GLchar *name, const size_t len,
                                      const GLchar **out_base_name_end)
{
   /* Section 7.3.1 ("Program Interfaces") of the OpenGL 4.3 spec says:
    *
    *     "When an integer array element or block instance number is part of
    *     the name string, it will be specified in decimal form without a "+"
    *     or "-" sign or any extra leading zeroes. Additionally, the name
    *     string will not include white space anywhere in the string."
    */

   *out_base_name_end = name + len;

   if (len == 0 || name[len-1] != ']')
      return -1;

   /* Walk backwards over the string looking for a non-digit character.  This
    * had better be the opening bracket for an array index.
    *
    * Initially, i specifies the location of the ']'.  Since the string may
    * contain only the ']' charcater, walk backwards very carefully.
    */
   unsigned i;
   for (i = len - 1; (i > 0) && isdigit(name[i-1]); --i)
      /* empty */ ;

   if ((i == 0) || name[i-1] != '[')
      return -1;

   long array_index = strtol(&name[i], NULL, 10);
   if (array_index < 0)
      return -1;

   /* Check for leading zero */
   if (name[i] == '0' && name[i+1] != ']')
      return -1;

   *out_base_name_end = name + (i - 1);
   return array_index;
}

/* Utility methods shared between the GLSL IR and the NIR */

/* From the OpenGL 4.6 specification, 7.3.1.1 Naming Active Resources:
 *
 *    "For an active shader storage block member declared as an array of an
 *     aggregate type, an entry will be generated only for the first array
 *     element, regardless of its type. Such block members are referred to as
 *     top-level arrays. If the block member is an aggregate type, the
 *     enumeration rules are then applied recursively."
 */
bool
link_util_should_add_buffer_variable(struct gl_shader_program *prog,
                                     struct gl_uniform_storage *uniform,
                                     int top_level_array_base_offset,
                                     int top_level_array_size_in_bytes,
                                     int second_element_offset,
                                     int block_index)
{
   /* If the uniform is not a shader storage buffer or is not an array return
    * true.
    */
   if (!uniform->is_shader_storage || top_level_array_size_in_bytes == 0)
      return true;

   int after_top_level_array = top_level_array_base_offset +
      top_level_array_size_in_bytes;

   /* Check for a new block, or that we are not dealing with array elements of
    * a top member array other than the first element.
    */
   if (block_index != uniform->block_index ||
       uniform->offset >= after_top_level_array ||
       uniform->offset < second_element_offset) {
      return true;
   }

   return false;
}

bool
link_util_add_program_resource(struct gl_shader_program *prog,
                               struct set *resource_set,
                               GLenum type, const void *data, uint8_t stages)
{
   assert(data);

   /* If resource already exists, do not add it again. */
   if (_mesa_set_search(resource_set, data))
      return true;

   prog->data->ProgramResourceList =
      reralloc(prog->data,
               prog->data->ProgramResourceList,
               gl_program_resource,
               prog->data->NumProgramResourceList + 1);

   if (!prog->data->ProgramResourceList) {
      linker_error(prog, "Out of memory during linking.\n");
      return false;
   }

   struct gl_program_resource *res =
      &prog->data->ProgramResourceList[prog->data->NumProgramResourceList];

   res->Type = type;
   res->Data = data;
   res->StageReferences = stages;

   prog->data->NumProgramResourceList++;

   _mesa_set_add(resource_set, data);

   return true;
}

/**
 * Search through the list of empty blocks to find one that fits the current
 * uniform.
 */
int
link_util_find_empty_block(struct gl_shader_program *prog,
                           struct gl_uniform_storage *uniform)
{
   const unsigned entries = MAX2(1, uniform->array_elements);

   ir_foreach_list_typed(struct empty_uniform_block, block, link,
                      &prog->EmptyUniformLocations) {
      /* Found a block with enough slots to fit the uniform */
      if (block->slots == entries) {
         unsigned start = block->start;
         ir_exec_node_remove(&block->link);
         ralloc_free(block);

         return start;
      /* Found a block with more slots than needed. It can still be used. */
      } else if (block->slots > entries) {
         unsigned start = block->start;
         block->start += entries;
         block->slots -= entries;

         return start;
      }
   }

   return -1;
}

void
link_util_update_empty_uniform_locations(const struct gl_constants *consts,
                                         struct gl_shader_program *prog)
{
   int prev_end = -1;
   list_for_each_entry_safe(struct range_entry, e, prog->UniformRemapTable, node) {
      unsigned next_slot = prev_end + 1;
      if (e->start > next_slot) {
         /* We've found the beginning of a new continous block of empty slots */
         struct empty_uniform_block *current_block =
            rzalloc(prog, struct empty_uniform_block);
         current_block->start = next_slot;
         current_block->slots = e->start - next_slot;
         ir_exec_list_push_tail(&prog->EmptyUniformLocations,
                                &current_block->link);
      }

      prev_end = e->end;
   }

   /* Add the remaining continous block of empty slots */
   unsigned next_slot = prev_end + 1;
   /* Some drivers assign a max assignable value greater than max block size
    * so we work around this by taking the max of either to get the remaining
    * empty slots.
    */
   unsigned max_slot = MAX2(consts->MaxUniformBlockSize,
                            consts->MaxUserAssignableUniformLocations) - 1;
   if (max_slot >= next_slot) {
      struct empty_uniform_block *current_block =
         rzalloc(prog, struct empty_uniform_block);
      current_block->start = next_slot;
      current_block->slots = max_slot + 1 - next_slot;

      ir_exec_list_push_tail(&prog->EmptyUniformLocations,
                             &current_block->link);
   }
}

void
link_util_check_subroutine_resources(struct gl_shader_program *prog)
{
   unsigned mask = prog->data->linked_stages;
   while (mask) {
      const int i = u_bit_scan(&mask);
      struct gl_program *p = prog->_LinkedShaders[i]->Program;

      if (p->sh.NumSubroutineUniformRemapTable > MAX_SUBROUTINE_UNIFORM_LOCATIONS) {
         linker_error(prog, "Too many %s shader subroutine uniforms\n",
                      _mesa_shader_stage_to_string(i));
      }
   }
}

/**
 * Validate uniform resources used by a program versus the implementation limits
 */
void
link_util_check_uniform_resources(const struct gl_constants *consts,
                                  struct gl_shader_program *prog)
{
   unsigned total_uniform_blocks = 0;
   unsigned total_shader_storage_blocks = 0;

   for (unsigned i = 0; i < MESA_SHADER_MESH_STAGES; i++) {
      struct gl_linked_shader *sh = prog->_LinkedShaders[i];

      if (sh == NULL)
         continue;

      if (sh->num_uniform_components >
          consts->Program[i].MaxUniformComponents) {
         if (consts->GLSLSkipStrictMaxUniformLimitCheck) {
            linker_warning(prog, "Too many %s shader default uniform block "
                           "components, but the driver will try to optimize "
                           "them out; this is non-portable out-of-spec "
                           "behavior\n",
                           _mesa_shader_stage_to_string(i));
         } else {
            linker_error(prog, "Too many %s shader default uniform block "
                         "components\n",
                         _mesa_shader_stage_to_string(i));
         }
      }

      if (sh->num_combined_uniform_components >
          consts->Program[i].MaxCombinedUniformComponents) {
         if (consts->GLSLSkipStrictMaxUniformLimitCheck) {
            linker_warning(prog, "Too many %s shader uniform components, "
                           "but the driver will try to optimize them out; "
                           "this is non-portable out-of-spec behavior\n",
                           _mesa_shader_stage_to_string(i));
         } else {
            linker_error(prog, "Too many %s shader uniform components\n",
                         _mesa_shader_stage_to_string(i));
         }
      }

      total_shader_storage_blocks += sh->Program->info.num_ssbos;
      total_uniform_blocks += sh->Program->info.num_ubos;
   }

   if (total_uniform_blocks > consts->MaxCombinedUniformBlocks) {
      linker_error(prog, "Too many combined uniform blocks (%d/%d)\n",
                   total_uniform_blocks, consts->MaxCombinedUniformBlocks);
   }

   if (total_shader_storage_blocks > consts->MaxCombinedShaderStorageBlocks) {
      linker_error(prog, "Too many combined shader storage blocks (%d/%d)\n",
                   total_shader_storage_blocks,
                   consts->MaxCombinedShaderStorageBlocks);
   }

   for (unsigned i = 0; i < prog->data->NumUniformBlocks; i++) {
      if (prog->data->UniformBlocks[i].UniformBufferSize >
          consts->MaxUniformBlockSize) {
         linker_error(prog, "Uniform block %s too big (%d/%d)\n",
                      prog->data->UniformBlocks[i].name.string,
                      prog->data->UniformBlocks[i].UniformBufferSize,
                      consts->MaxUniformBlockSize);
      }
   }

   for (unsigned i = 0; i < prog->data->NumShaderStorageBlocks; i++) {
      if (prog->data->ShaderStorageBlocks[i].UniformBufferSize >
          consts->MaxShaderStorageBlockSize) {
         linker_error(prog, "Shader storage block %s too big (%d/%d)\n",
                      prog->data->ShaderStorageBlocks[i].name.string,
                      prog->data->ShaderStorageBlocks[i].UniformBufferSize,
                      consts->MaxShaderStorageBlockSize);
      }
   }
}

void
link_util_calculate_subroutine_compat(struct gl_shader_program *prog)
{
   unsigned mask = prog->data->linked_stages;
   while (mask) {
      const int i = u_bit_scan(&mask);
      struct gl_program *p = prog->_LinkedShaders[i]->Program;

      for (unsigned j = 0; j < p->sh.NumSubroutineUniformRemapTable; j++) {
         if (p->sh.SubroutineUniformRemapTable[j] == INACTIVE_UNIFORM_EXPLICIT_LOCATION)
            continue;

         struct gl_uniform_storage *uni = p->sh.SubroutineUniformRemapTable[j];

         if (!uni)
            continue;

         int count = 0;
         if (p->sh.NumSubroutineFunctions == 0) {
            linker_error(prog, "subroutine uniform %s defined but no valid functions found\n", glsl_get_type_name(uni->type));
            continue;
         }
         for (unsigned f = 0; f < p->sh.NumSubroutineFunctions; f++) {
            struct gl_subroutine_function *fn = &p->sh.SubroutineFunctions[f];
            for (int k = 0; k < fn->num_compat_types; k++) {
               if (fn->types[k] == uni->type) {
                  count++;
                  break;
               }
            }
         }
         uni->num_compatible_subroutines = count;
      }
   }
}

const char *
interpolation_string(unsigned interpolation)
{
   switch (interpolation) {
   case INTERP_MODE_NONE:          return "no";
   case INTERP_MODE_SMOOTH:        return "smooth";
   case INTERP_MODE_FLAT:          return "flat";
   case INTERP_MODE_NOPERSPECTIVE: return "noperspective";
   }

   assert(!"Should not get here.");
   return "";
}

bool
_mesa_glsl_can_implicitly_convert(const glsl_type *from, const glsl_type *desired,
                                  bool has_implicit_conversions,
                                  bool has_implicit_int_to_uint_conversion)
{
   if (from == desired)
      return true;

   /* GLSL 1.10 and ESSL do not allow implicit conversions. */
   if (!has_implicit_conversions)
      return false;

   /* There is no conversion among matrix types. */
   if (from->matrix_columns > 1 || desired->matrix_columns > 1)
      return false;

   /* Vector size must match. */
   if (from->vector_elements != desired->vector_elements)
      return false;

   /* int and uint can be converted to float. */
   if (glsl_type_is_float(desired) && (glsl_type_is_integer_32(from) ||
       glsl_type_is_float_16(from)))
      return true;

   /* With GLSL 4.0, ARB_gpu_shader5, or MESA_shader_integer_functions, int
    * can be converted to uint.  Note that state may be NULL here, when
    * resolving function calls in the linker. By this time, all the
    * state-dependent checks have already happened though, so allow anything
    * that's allowed in any shader version.
    */
   if (has_implicit_int_to_uint_conversion &&
       desired->base_type == GLSL_TYPE_UINT && from->base_type == GLSL_TYPE_INT)
      return true;

   /* No implicit conversions from double. */
   if (glsl_type_is_double(from))
      return false;

   /* Conversions from different types to double. */
   if (glsl_type_is_double(desired)) {
      if (glsl_type_is_float_16_32(from))
         return true;
      if (glsl_type_is_integer_32(from))
         return true;
   }

   return false;
}

void
resource_name_updated(struct gl_resource_name *name)
{
   if (name->string) {
      name->length = strlen(name->string);

      const char *last_square_bracket = strrchr(name->string, '[');
      if (last_square_bracket) {
         name->last_square_bracket = last_square_bracket - name->string;
         name->suffix_is_zero_square_bracketed =
            strcmp(last_square_bracket, "[0]") == 0;
      } else {
         name->last_square_bracket = -1;
         name->suffix_is_zero_square_bracketed = false;
      }
   } else {
      name->length = 0;
      name->last_square_bracket = -1;
      name->suffix_is_zero_square_bracketed = false;
   }
}
