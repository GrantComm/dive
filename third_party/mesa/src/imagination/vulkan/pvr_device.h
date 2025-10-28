/*
 * Copyright © 2022 Imagination Technologies Ltd.
 *
 * based in part on anv driver which is:
 * Copyright © 2015 Intel Corporation
 *
 * based in part on radv driver which is:
 * Copyright © 2016 Red Hat.
 * Copyright © 2016 Bas Nieuwenhuizen
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef PVR_DEVICE_H
#define PVR_DEVICE_H

#include "vk_device.h"
#include "vk_device_memory.h"
#include "vk_instance.h"
#include "vk_physical_device.h"

#include "wsi_common.h"

#include "util/mesa-sha1.h"

#include "pvr_border.h"
#include "pvr_clear.h"
#include "pvr_common.h"
#include "pvr_pds.h"
#include "pvr_spm.h"
#include "pvr_usc.h"

#if defined(VK_USE_PLATFORM_DISPLAY_KHR)
#   define PVR_USE_WSI_PLATFORM_DISPLAY true
#else
#   define PVR_USE_WSI_PLATFORM_DISPLAY false
#endif

#if PVR_USE_WSI_PLATFORM_DISPLAY
#   define PVR_USE_WSI_PLATFORM true
#else
#   define PVR_USE_WSI_PLATFORM false
#endif

typedef struct _pco_ctx pco_ctx;

struct pvr_instance;
struct pvr_queue;

struct pvr_physical_device {
   struct vk_physical_device vk;

   /* Back-pointer to instance */
   struct pvr_instance *instance;

   char *render_path;
   char *display_path;

   /* primary node (cardN) of the render device */
   dev_t primary_devid;
   /* render node (renderN) of the render device */
   dev_t render_devid;

   struct pvr_winsys *ws;
   struct pvr_device_info dev_info;
   struct pvr_device_runtime_info dev_runtime_info;

   VkPhysicalDeviceMemoryProperties memory;

   struct wsi_device wsi_device;

   pco_ctx *pco_ctx;

   uint8_t device_uuid[SHA1_DIGEST_LENGTH];
   uint8_t cache_uuid[SHA1_DIGEST_LENGTH];
};

struct pvr_instance {
   struct vk_instance vk;

   uint32_t active_device_count;

   uint8_t driver_build_sha[SHA1_DIGEST_LENGTH];
};

struct pvr_compute_query_shader {
   struct pvr_suballoc_bo *usc_bo;

   struct pvr_pds_upload pds_prim_code;
   uint32_t primary_data_size_dw;
   uint32_t primary_num_temps;

   struct pvr_pds_info info;
   struct pvr_pds_upload pds_sec_code;
};

struct pvr_device {
   struct vk_device vk;
   struct pvr_instance *instance;
   struct pvr_physical_device *pdevice;

   struct pvr_winsys *ws;
   struct pvr_winsys_heaps heaps;

   struct pvr_free_list *global_free_list;

   struct pvr_queue *queues;
   uint32_t queue_count;

   /* Running count of the number of job submissions across all queue. */
   uint32_t global_cmd_buffer_submit_count;

   /* Running count of the number of presentations across all queues. */
   uint32_t global_queue_present_count;

   uint32_t pixel_event_data_size_in_dwords;

   uint64_t input_attachment_sampler;

   struct pvr_pds_upload pds_compute_fence_program;
   struct pvr_pds_upload pds_compute_empty_program;

   /* Compute shaders for queries. */
   struct pvr_compute_query_shader availability_shader;
   struct pvr_compute_query_shader reset_queries_shader;
   struct pvr_compute_query_shader copy_results_shader;

   struct pvr_suballocator suballoc_general;
   struct pvr_suballocator suballoc_pds;
   struct pvr_suballocator suballoc_transfer;
   struct pvr_suballocator suballoc_usc;
   struct pvr_suballocator suballoc_vis_test;

   struct {
      struct pvr_pds_upload pds;
      struct pvr_suballoc_bo *usc;
   } nop_program;

   struct pvr_pds_view_index_init_program
      view_index_init_info[PVR_MAX_MULTIVIEW];
   struct pvr_pds_upload view_index_init_programs[PVR_MAX_MULTIVIEW];

   /* Issue Data Fence, Wait for Data Fence state. */
   struct {
      uint32_t usc_shareds;
      struct pvr_suballoc_bo *usc;

      /* Buffer in which the IDF/WDF program performs store ops. */
      struct pvr_bo *store_bo;
      /* Contains the initialization values for the shared registers. */
      struct pvr_bo *shareds_bo;

      struct pvr_pds_upload pds;
      struct pvr_pds_upload sw_compute_barrier_pds;
   } idfwdf_state;

   struct pvr_device_static_clear_state {
      struct pvr_suballoc_bo *usc_vertex_shader_bo;
      struct pvr_suballoc_bo *vertices_bo;
      struct pvr_pds_upload pds;

      /* Only valid if PVR_HAS_FEATURE(dev_info, gs_rta_support). */
      struct pvr_suballoc_bo *usc_multi_layer_vertex_shader_bo;

      struct pvr_static_clear_ppp_base ppp_base;
      /* Indexable using VkImageAspectFlags. */
      struct pvr_static_clear_ppp_template
         ppp_templates[PVR_STATIC_CLEAR_VARIANT_COUNT];

      const uint32_t *vdm_words;
      const uint32_t *large_clear_vdm_words;

      struct pvr_suballoc_bo *usc_clear_attachment_programs;
      struct pvr_suballoc_bo *pds_clear_attachment_programs;
      /* TODO: See if we can use PVR_CLEAR_ATTACHMENT_PROGRAM_COUNT to save some
       * memory.
       */
      struct pvr_pds_clear_attachment_program_info {
         pvr_dev_addr_t texture_program_offset;
         pvr_dev_addr_t pixel_program_offset;

         uint32_t texture_program_pds_temps_count;
         /* Size in dwords. */
         uint32_t texture_program_data_size;
      } pds_clear_attachment_program_info[PVR_NUM_CLEAR_ATTACH_SHADERS];
   } static_clear_state;

   struct {
      struct pvr_suballoc_bo *usc_programs;
      struct pvr_suballoc_bo *pds_programs;

      struct pvr_spm_per_load_program_state {
         pvr_dev_addr_t pds_pixel_program_offset;
         pvr_dev_addr_t pds_uniform_program_offset;

         uint32_t pds_texture_program_data_size;
         uint32_t pds_texture_program_temps_count;
      } load_program[PVR_NUM_SPM_LOAD_SHADERS];
   } spm_load_state;

   struct pvr_device_tile_buffer_state {
      simple_mtx_t mtx;

#define PVR_MAX_TILE_BUFFER_COUNT 7U
      struct pvr_bo *buffers[PVR_MAX_TILE_BUFFER_COUNT];
      uint32_t buffer_count;
   } tile_buffer_state;

   struct pvr_spm_scratch_buffer_store spm_scratch_buffer_store;

   struct pvr_bo_store *bo_store;

   struct pvr_bo *robustness_buffer;

   struct vk_sync *presignaled_sync;

   struct pvr_border_color_table border_color_table;
};

struct pvr_device_memory {
   struct vk_device_memory vk;
   struct pvr_winsys_bo *bo;
};

VK_DEFINE_HANDLE_CASTS(pvr_instance,
                       vk.base,
                       VkInstance,
                       VK_OBJECT_TYPE_INSTANCE)

VK_DEFINE_HANDLE_CASTS(pvr_physical_device,
                       vk.base,
                       VkPhysicalDevice,
                       VK_OBJECT_TYPE_PHYSICAL_DEVICE)

VK_DEFINE_NONDISP_HANDLE_CASTS(pvr_device_memory,
                               vk.base,
                               VkDeviceMemory,
                               VK_OBJECT_TYPE_DEVICE_MEMORY)

VK_DEFINE_HANDLE_CASTS(pvr_device, vk.base, VkDevice, VK_OBJECT_TYPE_DEVICE)

static inline struct pvr_device *vk_to_pvr_device(struct vk_device *device)
{
   return container_of(device, struct pvr_device, vk);
}

uint32_t pvr_calc_fscommon_size_and_tiles_in_flight(
   const struct pvr_device_info *dev_info,
   const struct pvr_device_runtime_info *dev_runtime_info,
   uint32_t fs_common_size,
   uint32_t min_tiles_in_flight);

VkResult pvr_device_tile_buffer_ensure_cap(struct pvr_device *device,
                                           uint32_t capacity,
                                           uint32_t size_in_bytes);

VkResult pvr_pds_compute_shader_create_and_upload(
   struct pvr_device *device,
   struct pvr_pds_compute_shader_program *program,
   struct pvr_pds_upload *const pds_upload_out);

VkResult pvr_bind_memory(struct pvr_device *device,
                         struct pvr_device_memory *mem,
                         VkDeviceSize offset,
                         VkDeviceSize size,
                         VkDeviceSize alignment,
                         struct pvr_winsys_vma **const vma_out,
                         pvr_dev_addr_t *const dev_addr_out);
void pvr_unbind_memory(struct pvr_device *device, struct pvr_winsys_vma *vma);

VkResult pvr_gpu_upload(struct pvr_device *device,
                        struct pvr_winsys_heap *heap,
                        const void *data,
                        size_t size,
                        uint64_t alignment,
                        struct pvr_suballoc_bo **const pvr_bo_out);
VkResult pvr_gpu_upload_pds(struct pvr_device *device,
                            const uint32_t *data,
                            uint32_t data_size_dwords,
                            uint32_t data_alignment,
                            const uint32_t *code,
                            uint32_t code_size_dwords,
                            uint32_t code_alignment,
                            uint64_t min_alignment,
                            struct pvr_pds_upload *const pds_upload_out);
VkResult pvr_gpu_upload_usc(struct pvr_device *device,
                            const void *code,
                            size_t code_size,
                            uint64_t code_alignment,
                            struct pvr_suballoc_bo **const pvr_bo_out);

#endif /* PVR_DEVICE_H */
