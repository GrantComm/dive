/*
 * Copyright © 2025 Valve Corporation
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
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "ralloc.h"
#include "u_range_remap.h"

/* Binary search for the range that contains n */
static struct range_entry *
get_range_entry(unsigned n, const struct list_head *r_list)
{
   if (list_is_empty(r_list))
      return NULL;

   unsigned low = 0;
   unsigned high = list_length(r_list) - 1;
   unsigned mid = (low + high) / 2;

   struct range_entry *mid_entry =
      list_first_entry(r_list, struct range_entry, node);

   /* Advance to the initial mid position */
   unsigned i = 0;
   while (i < mid) {
      mid_entry = list_entry(mid_entry->node.next, struct range_entry, node);
      i++;
   }

   while (low <= high) {
      if (n < mid_entry->start) {
         if (low == high || mid == low) {
            /* No entry found for n */
            return NULL;
         }

         high = mid - 1;
         unsigned new_mid = (low + high) / 2;

         /* Move backward to new_mid */
         while (mid > new_mid) {
            mid_entry = list_entry(mid_entry->node.prev, struct range_entry, node);
            mid--;
         }
      } else if (n > mid_entry->end) {
         if (low == high || mid == high) {
            /* No entry found for n */
            return NULL;
         }

         low = mid + 1;
         unsigned new_mid = (low + high) / 2;

         /* Move forward to new_mid */
         while (mid < new_mid) {
            mid_entry = list_entry(mid_entry->node.next, struct range_entry, node);
            mid++;
        }
      } else {
         /* n is within the current range */
         return mid_entry;
      }
   }

   return NULL;
}

/* Insert a new range entry or update an existing entries pointer value if
 * start and end match exactly. If the range overlaps an existing entry we
 * return NULL.
 */
struct range_entry *
util_range_insert_remap(unsigned start, unsigned end,
                        struct list_head *r_list, void *ptr)
{
   struct range_entry *entry = NULL;
   if (list_is_empty(r_list)) {
      entry = rzalloc(r_list, struct range_entry);
      list_addtail(&entry->node, r_list);
      goto insert_end;
   }

   /* Shortcut for consecutive location inserts */
   struct range_entry *last_entry =
      list_last_entry(r_list, struct range_entry, node);
   if (last_entry->end < start) {
      entry = rzalloc(r_list, struct range_entry);
      list_addtail(&entry->node, r_list);
      goto insert_end;
   }

   unsigned low = 0;
   unsigned high = list_length(r_list) - 1;
   unsigned mid = (low + high) / 2;

   struct range_entry *mid_entry =
      list_first_entry(r_list, struct range_entry, node);
   unsigned i = 0;
   while (i < mid) {
      mid_entry = list_entry(mid_entry->node.next, struct range_entry, node);
      i++;
   }

   while (low <= high) {
      if (end < mid_entry->start) {
         if (low == high || mid == low) {
            entry = rzalloc(r_list, struct range_entry);
            list_addtail(&entry->node, &mid_entry->node); /* insert before mid */
            goto insert_end;
         }

         high = mid - 1;
         unsigned new_mid = (low + high) / 2;
         while (mid > new_mid) {
            mid_entry = list_entry(mid_entry->node.prev, struct range_entry, node);
            mid--;
         }
      } else if (start > mid_entry->end) {
         if (low == high || mid == high) {
            entry = rzalloc(r_list, struct range_entry);
            list_add(&entry->node, &mid_entry->node); /* insert after mid */
            goto insert_end;
         }

         low = mid + 1;
         unsigned new_mid = (low + high) / 2;
         while (mid < new_mid) {
            mid_entry =
               list_entry(mid_entry->node.next, struct range_entry, node);
            mid++;
         }
      } else if (mid_entry->start == start && mid_entry->end == end) {
         entry = mid_entry;
         goto insert_end;
      } else {
         /* Attempting to insert an entry that overlaps an existing range */
         return NULL;
      }
   }

insert_end:
   entry->start = start;
   entry->end = end;
   entry->ptr = ptr;

   return entry;
}

/* Return the range entry that maps to n or NULL if no match found. */
struct range_entry *
util_range_remap(unsigned n, const struct list_head *r_list)
{
   return get_range_entry(n, r_list);
}

struct list_head *
util_create_range_remap()
{
   struct range_entry *r = rzalloc(NULL, struct range_entry);
   list_inithead(&r->node);
   return &r->node;
}

/* Free previous list and create a new empty list */
struct list_head *
util_reset_range_remap(struct list_head *r_list)
{
   if (r_list)
      ralloc_free(r_list);

   return util_create_range_remap();
}
