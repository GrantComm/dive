/*
 Copyright 2019 Google LLC

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

// This is a copy of gfx9_plus_merged_f32_me_pm4_packets.h, but with
// enumerated bitfields manually removed. Enumerated bitfields are treated
// differently by different compilers (ie: signed vs unsigned), so
// a "compiler-friendly" version is provided here

#pragma once

namespace Dive
{

//--------------------TYPE_3_HEADER--------------------
typedef union PM4_ME_TYPE_3_HEADER
{
    struct
    {
        uint32_t predicate : 1;
        uint32_t shaderType : 1;
        uint32_t resetFilterCam : 1;
        uint32_t reserved1 : 5;
        uint32_t opcode : 8;
        uint32_t count : 14;
        uint32_t type : 2;
    };
    uint32_t u32All;

} PM4_ME_TYPE_3_HEADER, *PPM4_ME_TYPE_3_HEADER;

//--------------------ACQUIRE_MEM--------------------
enum ME_ACQUIRE_MEM_engine_sel_enum
{
    engine_sel__me_acquire_mem__micro_engine = 1,
};

//--------------------ACQUIRE_MEM__GFX09--------------------
typedef struct PM4_ME_ACQUIRE_MEM__GFX09
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t coher_cntl : 31;
            uint32_t engine_sel : 1;  // ME_ACQUIRE_MEM_engine_sel_enum
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t coher_size;

    union
    {
        struct
        {
            uint32_t coher_size_hi : 8;
            uint32_t reserved1 : 24;
        } bitfields4;
        uint32_t ordinal4;
    };

    uint32_t coher_base_lo;

    union
    {
        struct
        {
            uint32_t coher_base_hi : 24;
            uint32_t reserved1 : 8;
        } bitfields6;
        uint32_t ordinal6;
    };

    union
    {
        struct
        {
            uint32_t poll_interval : 16;
            uint32_t reserved1 : 16;
        } bitfields7;
        uint32_t ordinal7;
    };

} PM4ME_ACQUIRE_MEM__GFX09, *PPM4ME_ACQUIRE_MEM__GFX09;

//--------------------ATOMIC_GDS--------------------
enum ME_ATOMIC_GDS_atom_cmp_swap_enum
{
    atom_cmp_swap__me_atomic_gds__dont_repeat = 0,
    atom_cmp_swap__me_atomic_gds__repeat_until_pass = 1,
};

enum ME_ATOMIC_GDS_atom_complete_enum
{
    atom_complete__me_atomic_gds__dont_wait = 0,
    atom_complete__me_atomic_gds__wait_for_completion = 1,
};

enum ME_ATOMIC_GDS_atom_rd_cntl_enum
{
    atom_rd_cntl__me_atomic_gds__32bits_1returnval = 0,
    atom_rd_cntl__me_atomic_gds__32bits_2returnval = 1,
    atom_rd_cntl__me_atomic_gds__64bits_1returnval = 2,
    atom_rd_cntl__me_atomic_gds__64bits_2returnval = 3,
};

enum ME_ATOMIC_GDS_atom_read_enum
{
    atom_read__me_atomic_gds__dont_read_preop_data = 0,
    atom_read__me_atomic_gds__read_preop_data = 1,
};

enum ME_ATOMIC_GDS_engine_sel_enum
{
    engine_sel__me_atomic_gds__micro_engine = 0,
};

typedef struct PM4_ME_ATOMIC_GDS
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t atom_op : 7;
            uint32_t reserved1 : 9;
            uint32_t atom_cmp_swap : 1;  // ME_ATOMIC_GDS_atom_cmp_swap_enum
            uint32_t atom_complete : 1;  // ME_ATOMIC_GDS_atom_complete_enum
            uint32_t atom_read : 1;      // ME_ATOMIC_GDS_atom_read_enum
            uint32_t atom_rd_cntl : 2;   // ME_ATOMIC_GDS_atom_rd_cntl_enum
            uint32_t reserved2 : 9;
            uint32_t engine_sel : 2;  // ME_ATOMIC_GDS_engine_sel_enum
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t auto_inc_bytes : 6;
            uint32_t reserved1 : 2;
            uint32_t dmode : 1;
            uint32_t reserved2 : 23;
        } bitfields3;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t atom_base : 16;
            uint32_t reserved1 : 16;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t atom_size : 16;
            uint32_t reserved1 : 16;
        } bitfields5;
        uint32_t ordinal5;
    };

    union
    {
        struct
        {
            uint32_t atom_offset0 : 8;
            uint32_t reserved1 : 8;
            uint32_t atom_offset1 : 8;
            uint32_t reserved2 : 8;
        } bitfields6;
        uint32_t ordinal6;
    };

    uint32_t atom_dst;

    uint32_t atom_src0;

    uint32_t atom_src0_u;

    uint32_t atom_src1;

    uint32_t atom_src1_u;

} PM4ME_ATOMIC_GDS, *PPM4ME_ATOMIC_GDS;

//--------------------ATOMIC_MEM--------------------
enum ME_ATOMIC_MEM_cache_policy_enum
{
    cache_policy__me_atomic_mem__lru = 0,
    cache_policy__me_atomic_mem__stream = 1,
};

enum ME_ATOMIC_MEM_command_enum
{
    command__me_atomic_mem__single_pass_atomic = 0,
    command__me_atomic_mem__loop_until_compare_satisfied = 1,
};

enum ME_ATOMIC_MEM_engine_sel_enum
{
    engine_sel__me_atomic_mem__micro_engine = 0,
};

typedef struct PM4_ME_ATOMIC_MEM
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t atomic : 7;
            uint32_t reserved1 : 1;
            uint32_t command : 4;  // ME_ATOMIC_MEM_command_enum
            uint32_t reserved2 : 13;
            uint32_t cache_policy : 2;  // ME_ATOMIC_MEM_cache_policy_enum
            uint32_t reserved3 : 3;
            uint32_t engine_sel : 2;  // ME_ATOMIC_MEM_engine_sel_enum
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t addr_lo;

    uint32_t addr_hi;

    uint32_t src_data_lo;

    uint32_t src_data_hi;

    uint32_t cmp_data_lo;

    uint32_t cmp_data_hi;

    union
    {
        struct
        {
            uint32_t loop_interval : 13;
            uint32_t reserved1 : 19;
        } bitfields9;
        uint32_t ordinal9;
    };

} PM4ME_ATOMIC_MEM, *PPM4ME_ATOMIC_MEM;

//--------------------CLEAR_STATE--------------------
enum ME_CLEAR_STATE_cmd_enum
{
    cmd__me_clear_state__clear_state = 0,
    cmd__me_clear_state__push_state = 1,
    cmd__me_clear_state__pop_state = 2,
    cmd__me_clear_state__push_clear_state = 3,
};

typedef struct PM4_ME_CLEAR_STATE
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t cmd : 4;  // ME_CLEAR_STATE_cmd_enum
            uint32_t reserved1 : 28;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4ME_CLEAR_STATE, *PPM4ME_CLEAR_STATE;

//--------------------COND_WRITE--------------------
enum ME_COND_WRITE_function_enum
{
    function__me_cond_write__always_pass = 0,
    function__me_cond_write__less_than_ref_value = 1,
    function__me_cond_write__less_than_equal_to_the_ref_value = 2,
    function__me_cond_write__equal_to_the_reference_value = 3,
    function__me_cond_write__not_equal_reference_value = 4,
    function__me_cond_write__greater_than_or_equal_reference_value = 5,
    function__me_cond_write__greater_than_reference_value = 6,
};

enum ME_COND_WRITE_poll_space_enum
{
    poll_space__me_cond_write__register = 0,
    poll_space__me_cond_write__memory = 1,
};

enum ME_COND_WRITE_write_space_enum
{
    write_space__me_cond_write__register = 0,
    write_space__me_cond_write__memory = 1,
    write_space__me_cond_write__scratch = 2,
};

typedef struct PM4_ME_COND_WRITE
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t function : 3;  // ME_COND_WRITE_function_enum
            uint32_t reserved1 : 1;
            uint32_t poll_space : 1;  // ME_COND_WRITE_poll_space_enum
            uint32_t reserved2 : 3;
            uint32_t write_space : 2;  // ME_COND_WRITE_write_space_enum
            uint32_t reserved3 : 22;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t poll_address_lo;

    uint32_t poll_address_hi;

    uint32_t reference;

    uint32_t mask;

    uint32_t write_address_lo;

    uint32_t write_address_hi;

    uint32_t write_data;

} PM4ME_COND_WRITE, *PPM4ME_COND_WRITE;

//--------------------CONTEXT_CONTROL--------------------
typedef struct PM4_ME_CONTEXT_CONTROL
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t load_global_config : 1;
            uint32_t load_per_context_state : 1;
            uint32_t reserved1 : 13;
            uint32_t load_global_uconfig : 1;
            uint32_t load_gfx_sh_regs : 1;
            uint32_t reserved2 : 7;
            uint32_t load_cs_sh_regs : 1;
            uint32_t reserved3 : 3;
            uint32_t load_ce_ram : 1;
            uint32_t reserved4 : 2;
            uint32_t update_load_enables : 1;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t shadow_global_config : 1;
            uint32_t shadow_per_context_state : 1;
            uint32_t reserved1 : 13;
            uint32_t shadow_global_uconfig : 1;
            uint32_t shadow_gfx_sh_regs : 1;
            uint32_t reserved2 : 7;
            uint32_t shadow_cs_sh_regs : 1;
            uint32_t reserved3 : 6;
            uint32_t update_shadow_enables : 1;
        } bitfields3;
        uint32_t ordinal3;
    };

} PM4ME_CONTEXT_CONTROL, *PPM4ME_CONTEXT_CONTROL;

//--------------------CONTEXT_REG_RMW--------------------
typedef struct PM4_ME_CONTEXT_REG_RMW
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 16;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t reg_mask;

    uint32_t reg_data;

} PM4ME_CONTEXT_REG_RMW, *PPM4ME_CONTEXT_REG_RMW;

//--------------------COPY_DATA--------------------
enum ME_COPY_DATA_count_sel_enum
{
    count_sel__me_copy_data__32_bits_of_data = 0,
    count_sel__me_copy_data__64_bits_of_data = 1,
};

enum ME_COPY_DATA_dst_cache_policy_enum
{
    dst_cache_policy__me_copy_data__lru = 0,
    dst_cache_policy__me_copy_data__stream = 1,
};

enum ME_COPY_DATA_dst_sel_enum
{
    dst_sel__me_copy_data__mem_mapped_register = 0,
    dst_sel__me_copy_data__memory_sync_across_grbm = 1,
    dst_sel__me_copy_data__tc_l2 = 2,
    dst_sel__me_copy_data__gds = 3,
    dst_sel__me_copy_data__perfcounters = 4,
    dst_sel__me_copy_data__memory__GFX09 = 5,
};

enum ME_COPY_DATA_engine_sel_enum
{
    engine_sel__me_copy_data__micro_engine = 0,
};

enum ME_COPY_DATA_src_cache_policy_enum
{
    src_cache_policy__me_copy_data__lru = 0,
    src_cache_policy__me_copy_data__stream = 1,
};

enum ME_COPY_DATA_src_sel_enum
{
    src_sel__me_copy_data__mem_mapped_register = 0,
    src_sel__me_copy_data__memory__GFX09 = 1,
    src_sel__me_copy_data__tc_l2 = 2,
    src_sel__me_copy_data__gds = 3,
    src_sel__me_copy_data__perfcounters = 4,
    src_sel__me_copy_data__immediate_data = 5,
    src_sel__me_copy_data__atomic_return_data = 6,
    src_sel__me_copy_data__gds_atomic_return_data0 = 7,
    src_sel__me_copy_data__gds_atomic_return_data1 = 8,
    src_sel__me_copy_data__gpu_clock_count = 9,
    src_sel__me_copy_data__system_clock_count = 10,
};

enum ME_COPY_DATA_wr_confirm_enum
{
    wr_confirm__me_copy_data__do_not_wait_for_confirmation = 0,
    wr_confirm__me_copy_data__wait_for_confirmation = 1,
};

typedef struct PM4_ME_COPY_DATA
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t src_sel : 4;  // ME_COPY_DATA_src_sel_enum
            uint32_t reserved1 : 4;
            uint32_t dst_sel : 4;  // ME_COPY_DATA_dst_sel_enum
            uint32_t reserved2 : 1;
            uint32_t src_cache_policy : 2;  // ME_COPY_DATA_src_cache_policy_enum
            uint32_t reserved3 : 1;
            uint32_t count_sel : 1;  // ME_COPY_DATA_count_sel_enum
            uint32_t reserved4 : 3;
            uint32_t wr_confirm : 1;  // ME_COPY_DATA_wr_confirm_enum
            uint32_t reserved5 : 4;
            uint32_t dst_cache_policy : 2;  // ME_COPY_DATA_dst_cache_policy_enum
            uint32_t reserved6 : 3;
            uint32_t engine_sel : 2;  // ME_COPY_DATA_engine_sel_enum
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t src_reg_offset : 18;
            uint32_t reserved1 : 14;
        } bitfields3a;
        struct
        {
            uint32_t reserved1 : 2;
            uint32_t src_32b_addr_lo : 30;
        } bitfields3b;
        struct
        {
            uint32_t reserved1 : 3;
            uint32_t src_64b_addr_lo : 29;
        } bitfields3c;
        struct
        {
            uint32_t src_gds_addr_lo : 16;
            uint32_t reserved1 : 16;
        } bitfields3d;
        uint32_t imm_data;
        uint32_t ordinal3;
    };

    union
    {
        uint32_t src_memtc_addr_hi;
        uint32_t src_imm_data;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t dst_reg_offset : 18;
            uint32_t reserved1 : 14;
        } bitfields5a;
        struct
        {
            uint32_t reserved1 : 2;
            uint32_t dst_32b_addr_lo : 30;
        } bitfields5b;
        struct
        {
            uint32_t reserved1 : 3;
            uint32_t dst_64b_addr_lo : 29;
        } bitfields5c;
        struct
        {
            uint32_t dst_gds_addr_lo : 16;
            uint32_t reserved1 : 16;
        } bitfields5d;
        uint32_t ordinal5;
    };

    uint32_t dst_addr_hi;

} PM4ME_COPY_DATA, *PPM4ME_COPY_DATA;

//--------------------DISPATCH_DIRECT--------------------
typedef struct PM4_ME_DISPATCH_DIRECT
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t dim_x;

    uint32_t dim_y;

    uint32_t dim_z;

    uint32_t dispatch_initiator;

} PM4ME_DISPATCH_DIRECT, *PPM4ME_DISPATCH_DIRECT;

//--------------------DISPATCH_INDIRECT--------------------
typedef struct PM4_ME_DISPATCH_INDIRECT
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t data_offset;

    uint32_t dispatch_initiator;

} PM4ME_DISPATCH_INDIRECT, *PPM4ME_DISPATCH_INDIRECT;

//--------------------DMA_DATA--------------------
enum ME_DMA_DATA_daic_enum
{
    daic__me_dma_data__increment = 0,
    daic__me_dma_data__no_increment = 1,
};

enum ME_DMA_DATA_das_enum
{
    das__me_dma_data__memory = 0,
    das__me_dma_data__register = 1,
};

enum ME_DMA_DATA_dst_cache_policy_enum
{
    dst_cache_policy__me_dma_data__lru = 0,
    dst_cache_policy__me_dma_data__stream = 1,
};

enum ME_DMA_DATA_dst_sel_enum
{
    dst_sel__me_dma_data__dst_addr_using_das = 0,
    dst_sel__me_dma_data__gds = 1,
    dst_sel__me_dma_data__dst_nowhere = 2,
    dst_sel__me_dma_data__dst_addr_using_l2 = 3,
};

enum ME_DMA_DATA_engine_sel_enum
{
    engine_sel__me_dma_data__micro_engine = 0,
};

enum ME_DMA_DATA_saic_enum
{
    saic__me_dma_data__increment = 0,
    saic__me_dma_data__no_increment = 1,
};

enum ME_DMA_DATA_sas_enum
{
    sas__me_dma_data__memory = 0,
    sas__me_dma_data__register = 1,
};

enum ME_DMA_DATA_src_cache_policy_enum
{
    src_cache_policy__me_dma_data__lru = 0,
    src_cache_policy__me_dma_data__stream = 1,
};

enum ME_DMA_DATA_src_sel_enum
{
    src_sel__me_dma_data__src_addr_using_sas = 0,
    src_sel__me_dma_data__gds = 1,
    src_sel__me_dma_data__data = 2,
    src_sel__me_dma_data__src_addr_using_l2 = 3,
};

typedef struct PM4_ME_DMA_DATA
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t engine_sel : 1;  // ME_DMA_DATA_engine_sel_enum
            uint32_t reserved1 : 12;
            uint32_t src_cache_policy : 2;  // ME_DMA_DATA_src_cache_policy_enum
            uint32_t reserved2 : 5;
            uint32_t dst_sel : 2;  // ME_DMA_DATA_dst_sel_enum
            uint32_t reserved3 : 3;
            uint32_t dst_cache_policy : 2;  // ME_DMA_DATA_dst_cache_policy_enum
            uint32_t reserved4 : 2;
            uint32_t src_sel : 2;  // ME_DMA_DATA_src_sel_enum
            uint32_t cp_sync : 1;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t src_addr_lo_or_data;

    uint32_t src_addr_hi;

    uint32_t dst_addr_lo;

    uint32_t dst_addr_hi;

    union
    {
        struct
        {
            uint32_t byte_count : 26;
            uint32_t sas : 1;   // ME_DMA_DATA_sas_enum
            uint32_t das : 1;   // ME_DMA_DATA_das_enum
            uint32_t saic : 1;  // ME_DMA_DATA_saic_enum
            uint32_t daic : 1;  // ME_DMA_DATA_daic_enum
            uint32_t raw_wait : 1;
            uint32_t dis_wc : 1;
        } bitfields7;
        uint32_t ordinal7;
    };

} PM4ME_DMA_DATA, *PPM4ME_DMA_DATA;

//--------------------DMA_DATA_FILL_MULTI--------------------
enum ME_DMA_DATA_FILL_MULTI_dst_cache_policy_enum
{
    dst_cache_policy__me_dma_data_fill_multi__lru = 0,
    dst_cache_policy__me_dma_data_fill_multi__stream = 1,
};

enum ME_DMA_DATA_FILL_MULTI_dst_sel_enum
{
    dst_sel__me_dma_data_fill_multi__dst_addr_using_l2 = 3,
};

enum ME_DMA_DATA_FILL_MULTI_engine_sel_enum
{
    engine_sel__me_dma_data_fill_multi__micro_engine = 0,
    engine_sel__me_dma_data_fill_multi__prefetch_parser = 1,
};

enum ME_DMA_DATA_FILL_MULTI_src_sel_enum
{
    src_sel__me_dma_data_fill_multi__data = 2,
};

typedef struct PM4_ME_DMA_DATA_FILL_MULTI
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t engine_sel : 1;  // ME_DMA_DATA_FILL_MULTI_engine_sel_enum
            uint32_t reserved1 : 9;
            uint32_t memlog_clear : 1;
            uint32_t reserved2 : 9;
            uint32_t dst_sel : 2;  // ME_DMA_DATA_FILL_MULTI_dst_sel_enum
            uint32_t reserved3 : 3;
            uint32_t dst_cache_policy : 2;  // ME_DMA_DATA_FILL_MULTI_dst_cache_policy_enum
            uint32_t reserved4 : 2;
            uint32_t src_sel : 2;  // ME_DMA_DATA_FILL_MULTI_src_sel_enum
            uint32_t cp_sync : 1;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t byte_stride;

    uint32_t dma_count;

    uint32_t dst_addr_lo;

    uint32_t dst_addr_hi;

    union
    {
        struct
        {
            uint32_t byte_count : 26;
            uint32_t reserved1 : 6;
        } bitfields7;
        uint32_t ordinal7;
    };

} PM4ME_DMA_DATA_FILL_MULTI, *PPM4ME_DMA_DATA_FILL_MULTI;

//--------------------DRAW_INDEX_2--------------------
typedef struct PM4_ME_DRAW_INDEX_2
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t max_size;

    uint32_t index_base_lo;

    uint32_t index_base_hi;

    uint32_t index_count;

    uint32_t draw_initiator;

} PM4ME_DRAW_INDEX_2, *PPM4ME_DRAW_INDEX_2;

//--------------------DRAW_INDEX_AUTO--------------------
typedef struct PM4_ME_DRAW_INDEX_AUTO
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t index_count;

    uint32_t draw_initiator;

} PM4ME_DRAW_INDEX_AUTO, *PPM4ME_DRAW_INDEX_AUTO;

//--------------------DRAW_INDEX_INDIRECT--------------------
typedef struct PM4_ME_DRAW_INDEX_INDIRECT
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t data_offset;

    union
    {
        struct
        {
            uint32_t base_vtx_loc : 16;
            uint32_t start_indx_loc : 16;
        } bitfields3;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t start_inst_loc : 16;
            uint32_t reserved1 : 12;
            uint32_t start_indx_enable : 1;
            uint32_t reserved2 : 3;
        } bitfields4;
        uint32_t ordinal4;
    };

    uint32_t draw_initiator;

} PM4ME_DRAW_INDEX_INDIRECT, *PPM4ME_DRAW_INDEX_INDIRECT;

//--------------------DRAW_INDEX_INDIRECT_MULTI--------------------
typedef struct PM4_ME_DRAW_INDEX_INDIRECT_MULTI
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t data_offset;

    union
    {
        struct
        {
            uint32_t base_vtx_loc : 16;
            uint32_t reserved1 : 16;
        } bitfields3;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t start_inst_loc : 16;
            uint32_t reserved1 : 16;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        uint32_t draw_initiator;
    };

} PM4ME_DRAW_INDEX_INDIRECT_MULTI, *PPM4ME_DRAW_INDEX_INDIRECT_MULTI;

//--------------------DRAW_INDEX_MULTI_AUTO--------------------
typedef struct PM4_ME_DRAW_INDEX_MULTI_AUTO
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t prim_count;

    uint32_t draw_initiator;

    union
    {
        struct
        {
            uint32_t index_offset : 16;
            uint32_t prim_type : 5;
            uint32_t index_count : 11;
        } bitfields4;
        uint32_t ordinal4;
    };

} PM4ME_DRAW_INDEX_MULTI_AUTO, *PPM4ME_DRAW_INDEX_MULTI_AUTO;

//--------------------DRAW_INDEX_MULTI_INST--------------------
typedef struct PM4_ME_DRAW_INDEX_MULTI_INST
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t instance_count;

    uint32_t index_count;

    uint32_t draw_initiator;

} PM4ME_DRAW_INDEX_MULTI_INST, *PPM4ME_DRAW_INDEX_MULTI_INST;

//--------------------DRAW_INDEX_OFFSET_2--------------------
typedef struct PM4_ME_DRAW_INDEX_OFFSET_2
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t max_size;

    uint32_t index_offset;

    uint32_t index_count;

    uint32_t draw_initiator;

} PM4ME_DRAW_INDEX_OFFSET_2, *PPM4ME_DRAW_INDEX_OFFSET_2;

//--------------------DRAW_INDIRECT--------------------
typedef struct PM4_ME_DRAW_INDIRECT
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t data_offset;

    union
    {
        struct
        {
            uint32_t start_vtx_loc : 16;
            uint32_t reserved1 : 16;
        } bitfields3;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t start_inst_loc : 16;
            uint32_t reserved1 : 16;
        } bitfields4;
        uint32_t ordinal4;
    };

    uint32_t draw_initiator;

} PM4ME_DRAW_INDIRECT, *PPM4ME_DRAW_INDIRECT;

//--------------------DRAW_INDIRECT_MULTI--------------------
typedef struct PM4_ME_DRAW_INDIRECT_MULTI
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t data_offset;

    union
    {
        struct
        {
            uint32_t start_vtx_loc : 16;
            uint32_t reserved1 : 16;
        } bitfields3;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t start_inst_loc : 16;
            uint32_t reserved1 : 16;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        uint32_t draw_initiator;
    };

} PM4ME_DRAW_INDIRECT_MULTI, *PPM4ME_DRAW_INDIRECT_MULTI;

//--------------------EVENT_WRITE--------------------
enum ME_EVENT_WRITE_event_index_enum
{
    event_index__me_event_write__other = 0,
    event_index__me_event_write__zpass_pixel_pipe_stat_control_or_dump = 1,
    event_index__me_event_write__sample_pipelinestats = 2,
    event_index__me_event_write__sample_streamoutstat = 3,
    event_index__me_event_write__cs_vs_ps_partial_flush = 4,
};

typedef struct PM4_ME_EVENT_WRITE
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t event_type : 6;
            uint32_t reserved1 : 2;
            uint32_t event_index : 4;  // ME_EVENT_WRITE_event_index_enum
            uint32_t reserved2 : 20;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 3;
            uint32_t address_lo : 29;
        } bitfields3;
        uint32_t ordinal3;
    };

    uint32_t address_hi;

} PM4ME_EVENT_WRITE, *PPM4ME_EVENT_WRITE;

//--------------------FRAME_CONTROL--------------------
enum ME_FRAME_CONTROL_command_enum
{
    command__me_frame_control__kmd_frame_begin = 0,
    command__me_frame_control__kmd_frame_end = 1,
};

enum ME_FRAME_CONTROL_tmz_enum
{
    tmz__me_frame_control__tmz_off = 0,
    tmz__me_frame_control__tmz_on = 1,
};

typedef struct PM4_ME_FRAME_CONTROL
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t tmz : 1;  // ME_FRAME_CONTROL_tmz_enum
            uint32_t reserved1 : 27;
            uint32_t command : 4;  // ME_FRAME_CONTROL_command_enum
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4ME_FRAME_CONTROL, *PPM4ME_FRAME_CONTROL;

//--------------------GET_LOD_STATS--------------------
enum ME_GET_LOD_STATS_cache_policy_enum
{
    cache_policy__me_get_lod_stats__lru = 0,
    cache_policy__me_get_lod_stats__stream = 1,
};

typedef struct PM4_ME_GET_LOD_STATS
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t bu_size;

    union
    {
        struct
        {
            uint32_t reserved1 : 6;
            uint32_t base_lo : 26;
        } bitfields3;
        uint32_t ordinal3;
    };

    uint32_t base_hi;

    union
    {
        struct
        {
            uint32_t reserved1 : 2;
            uint32_t interval : 8;
            uint32_t reset_cnt : 8;
            uint32_t reset_force : 1;
            uint32_t report_and_reset : 1;
            uint32_t reserved2 : 8;
            uint32_t cache_policy : 2;  // ME_GET_LOD_STATS_cache_policy_enum
            uint32_t reserved3 : 2;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4ME_GET_LOD_STATS, *PPM4ME_GET_LOD_STATS;

//--------------------INCREMENT_DE_COUNTER--------------------
typedef struct PM4_ME_INCREMENT_DE_COUNTER
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t dummy_data;

} PM4ME_INCREMENT_DE_COUNTER, *PPM4ME_INCREMENT_DE_COUNTER;

//--------------------LOAD_CONFIG_REG--------------------
typedef struct PM4_ME_LOAD_CONFIG_REG
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 2;
            uint32_t base_addr_lo : 30;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t base_addr_hi;

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 16;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t num_dwords : 14;
            uint32_t reserved1 : 18;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4ME_LOAD_CONFIG_REG, *PPM4ME_LOAD_CONFIG_REG;

//--------------------LOAD_CONTEXT_REG--------------------
typedef struct PM4_ME_LOAD_CONTEXT_REG
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 2;
            uint32_t base_addr_lo : 30;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t base_addr_hi;

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 16;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t num_dwords : 14;
            uint32_t reserved1 : 18;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4ME_LOAD_CONTEXT_REG, *PPM4ME_LOAD_CONTEXT_REG;

//--------------------LOAD_CONTEXT_REG_INDEX--------------------
enum ME_LOAD_CONTEXT_REG_INDEX_data_format_enum
{
    data_format__me_load_context_reg_index__offset_and_size = 0,
    data_format__me_load_context_reg_index__offset_and_data = 1,
};

enum ME_LOAD_CONTEXT_REG_INDEX_index_enum
{
    index__me_load_context_reg_index__direct_addr = 0,
    index__me_load_context_reg_index__offset = 1,
};

typedef struct PM4_ME_LOAD_CONTEXT_REG_INDEX
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t index : 1;  // ME_LOAD_CONTEXT_REG_INDEX_index_enum
            uint32_t reserved1 : 1;
            uint32_t mem_addr_lo : 30;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        uint32_t mem_addr_hi;
        uint32_t addr_offset;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 15;
            uint32_t data_format : 1;  // ME_LOAD_CONTEXT_REG_INDEX_data_format_enum
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t num_dwords : 14;
            uint32_t reserved1 : 18;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4ME_LOAD_CONTEXT_REG_INDEX, *PPM4ME_LOAD_CONTEXT_REG_INDEX;

//--------------------LOAD_SH_REG--------------------
typedef struct PM4_ME_LOAD_SH_REG
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 2;
            uint32_t base_address_lo : 30;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t base_address_hi;

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 16;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t num_dword : 14;
            uint32_t reserved1 : 18;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4ME_LOAD_SH_REG, *PPM4ME_LOAD_SH_REG;

//--------------------LOAD_SH_REG_INDEX--------------------
enum ME_LOAD_SH_REG_INDEX_data_format_enum
{
    data_format__me_load_sh_reg_index__offset_and_size = 0,
    data_format__me_load_sh_reg_index__offset_and_data = 1,
};

enum ME_LOAD_SH_REG_INDEX_index_enum
{
    index__me_load_sh_reg_index__direct_addr = 0,
    index__me_load_sh_reg_index__offset = 1,
};

typedef struct PM4_ME_LOAD_SH_REG_INDEX
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t index : 1;  // ME_LOAD_SH_REG_INDEX_index_enum
            uint32_t reserved1 : 1;
            uint32_t mem_addr_lo : 30;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        uint32_t mem_addr_hi;
        uint32_t addr_offset;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 15;
            uint32_t data_format : 1;  // ME_LOAD_SH_REG_INDEX_data_format_enum
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t num_dwords : 14;
            uint32_t reserved1 : 18;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4ME_LOAD_SH_REG_INDEX, *PPM4ME_LOAD_SH_REG_INDEX;

//--------------------LOAD_UCONFIG_REG--------------------
typedef struct PM4_ME_LOAD_UCONFIG_REG
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 2;
            uint32_t base_address_lo : 30;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t base_address_hi;

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 16;
        } bitfields4;
        uint32_t ordinal4;
    };

    union
    {
        struct
        {
            uint32_t num_dwords : 14;
            uint32_t reserved1 : 18;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4ME_LOAD_UCONFIG_REG, *PPM4ME_LOAD_UCONFIG_REG;

//--------------------MEM_SEMAPHORE--------------------
enum ME_MEM_SEMAPHORE_sem_sel_enum
{
    sem_sel__me_mem_semaphore__signal_semaphore = 6,
    sem_sel__me_mem_semaphore__wait_semaphore = 7,
};

enum ME_MEM_SEMAPHORE_signal_type_enum
{
    signal_type__me_mem_semaphore__signal_type_increment = 0,
    signal_type__me_mem_semaphore__signal_type_write = 1,
};

enum ME_MEM_SEMAPHORE_use_mailbox_enum
{
    use_mailbox__me_mem_semaphore__do_not_wait_for_mailbox = 0,
    use_mailbox__me_mem_semaphore__wait_for_mailbox = 1,
};

typedef struct PM4_ME_MEM_SEMAPHORE
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 3;
            uint32_t address_lo : 29;
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t address_hi;

    union
    {
        struct
        {
            uint32_t reserved1 : 16;
            uint32_t use_mailbox : 1;  // ME_MEM_SEMAPHORE_use_mailbox_enum
            uint32_t reserved2 : 3;
            uint32_t signal_type : 1;  // ME_MEM_SEMAPHORE_signal_type_enum
            uint32_t reserved3 : 8;
            uint32_t sem_sel : 3;  // ME_MEM_SEMAPHORE_sem_sel_enum
        } bitfields4;
        uint32_t ordinal4;
    };

} PM4ME_MEM_SEMAPHORE, *PPM4ME_MEM_SEMAPHORE;

//--------------------PFP_SYNC_ME--------------------
typedef struct PM4_ME_PFP_SYNC_ME
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    uint32_t dummy_data;

} PM4ME_PFP_SYNC_ME, *PPM4ME_PFP_SYNC_ME;

//--------------------PREAMBLE_CNTL--------------------
enum ME_PREAMBLE_CNTL_command_enum
{
    command__me_preamble_cntl__preamble_begin = 0,
    command__me_preamble_cntl__preamble_end = 1,
    command__me_preamble_cntl__begin_of_clear_state_initialization = 2,
    command__me_preamble_cntl__end_of_clear_state_initialization = 3,
};

typedef struct PM4_ME_PREAMBLE_CNTL
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 28;
            uint32_t command : 4;  // ME_PREAMBLE_CNTL_command_enum
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4ME_PREAMBLE_CNTL, *PPM4ME_PREAMBLE_CNTL;

//--------------------PRIME_UTCL2--------------------
enum ME_PRIME_UTCL2_cache_perm_enum
{
    cache_perm__me_prime_utcl2__read = 0,
    cache_perm__me_prime_utcl2__write = 1,
    cache_perm__me_prime_utcl2__execute = 2,
};

enum ME_PRIME_UTCL2_engine_sel_enum
{
    engine_sel__me_prime_utcl2__microengine = 0,
};

enum ME_PRIME_UTCL2_prime_mode_enum
{
    prime_mode__me_prime_utcl2__dont_wait_for_xack = 0,
    prime_mode__me_prime_utcl2__wait_for_xack = 1,
};

typedef struct PM4_ME_PRIME_UTCL2
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t cache_perm : 3;  // ME_PRIME_UTCL2_cache_perm_enum
            uint32_t prime_mode : 1;  // ME_PRIME_UTCL2_prime_mode_enum
            uint32_t reserved1 : 26;
            uint32_t engine_sel : 2;  // ME_PRIME_UTCL2_engine_sel_enum
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t addr_lo;

    uint32_t addr_hi;

    union
    {
        struct
        {
            uint32_t requested_pages : 14;
            uint32_t reserved1 : 18;
        } bitfields5;
        uint32_t ordinal5;
    };

} PM4ME_PRIME_UTCL2, *PPM4ME_PRIME_UTCL2;

//--------------------REG_RMW--------------------
enum ME_REG_RMW_and_mask_src_enum
{
    and_mask_src__me_reg_rmw__immediate = 0,
    and_mask_src__me_reg_rmw__reg_and_addr = 1,
};

enum ME_REG_RMW_or_mask_src_enum
{
    or_mask_src__me_reg_rmw__immediate = 0,
    or_mask_src__me_reg_rmw__reg_or_addr = 1,
};

enum ME_REG_RMW_shadow_base_sel_enum
{
    shadow_base_sel__me_reg_rmw__no_shadow = 0,
    shadow_base_sel__me_reg_rmw__shadow_global_uconfig = 1,
};

typedef struct PM4_ME_REG_RMW
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t mod_addr : 18;
            uint32_t reserved1 : 6;
            uint32_t shadow_base_sel : 2;  // ME_REG_RMW_shadow_base_sel_enum
            uint32_t reserved2 : 4;
            uint32_t or_mask_src : 1;   // ME_REG_RMW_or_mask_src_enum
            uint32_t and_mask_src : 1;  // ME_REG_RMW_and_mask_src_enum
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t and_addr : 18;
            uint32_t reserved1 : 14;
        } bitfields3;
        uint32_t and_mask;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t or_addr : 18;
            uint32_t reserved1 : 14;
        } bitfields4;
        uint32_t or_mask;
        uint32_t ordinal4;
    };

} PM4ME_REG_RMW, *PPM4ME_REG_RMW;

//--------------------RELEASE_MEM--------------------
enum ME_RELEASE_MEM_cache_policy_enum
{
    cache_policy__me_release_mem__lru = 0,
    cache_policy__me_release_mem__stream = 1,
};

enum ME_RELEASE_MEM_data_sel_enum
{
    data_sel__me_release_mem__none = 0,
    data_sel__me_release_mem__send_32_bit_low = 1,
    data_sel__me_release_mem__send_64_bit_data = 2,
    data_sel__me_release_mem__send_gpu_clock_counter = 3,
    data_sel__me_release_mem__send_cp_perfcounter_hi_lo = 4,
    data_sel__me_release_mem__store_gds_data_to_memory = 5,
};

enum ME_RELEASE_MEM_dst_sel_enum
{
    dst_sel__me_release_mem__memory_controller = 0,
    dst_sel__me_release_mem__tc_l2 = 1,
    dst_sel__me_release_mem__queue_write_pointer_register = 2,
    dst_sel__me_release_mem__queue_write_pointer_poll_mask_bit = 3,
};

enum ME_RELEASE_MEM_event_index_enum
{
    event_index__me_release_mem__end_of_pipe = 5,
    event_index__me_release_mem__shader_done = 6,
};

enum ME_RELEASE_MEM_int_sel_enum
{
    int_sel__me_release_mem__none = 0,
    int_sel__me_release_mem__send_interrupt_only = 1,
    int_sel__me_release_mem__send_interrupt_after_write_confirm = 2,
    int_sel__me_release_mem__send_data_after_write_confirm = 3,
    int_sel__me_release_mem__unconditionally_send_int_ctxid = 4,
    int_sel__me_release_mem__conditionally_send_int_ctxid_based_on_32_bit_compare = 5,
    int_sel__me_release_mem__conditionally_send_int_ctxid_based_on_64_bit_compare = 6,
};

//--------------------RELEASE_MEM__GFX09--------------------
typedef struct PM4_ME_RELEASE_MEM__GFX09
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t event_type : 6;
            uint32_t reserved1 : 2;
            uint32_t event_index : 4;  // ME_RELEASE_MEM_event_index_enum
            uint32_t tcl1_vol_action_ena : 1;
            uint32_t tc_vol_action_ena : 1;
            uint32_t reserved2 : 1;
            uint32_t tc_wb_action_ena : 1;
            uint32_t tcl1_action_ena : 1;
            uint32_t tc_action_ena : 1;
            uint32_t reserved3 : 1;
            uint32_t tc_nc_action_ena : 1;
            uint32_t tc_wc_action_ena : 1;
            uint32_t tc_md_action_ena : 1;
            uint32_t reserved4 : 3;
            uint32_t cache_policy : 2;  // ME_RELEASE_MEM_cache_policy_enum
            uint32_t reserved5 : 1;
            uint32_t execute : 1;
            uint32_t reserved6 : 3;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 16;
            uint32_t dst_sel : 2;  // ME_RELEASE_MEM_dst_sel_enum
            uint32_t reserved2 : 6;
            uint32_t int_sel : 3;  // ME_RELEASE_MEM_int_sel_enum
            uint32_t reserved3 : 2;
            uint32_t data_sel : 3;  // ME_RELEASE_MEM_data_sel_enum
        } bitfields3;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 2;
            uint32_t address_lo_32b : 30;
        } bitfields4a;
        struct
        {
            uint32_t reserved1 : 3;
            uint32_t address_lo_64b : 29;
        } bitfields4b;
        uint32_t reserved12;
        uint32_t ordinal4;
    };

    union
    {
        uint32_t address_hi;
        uint32_t reserved13;
        uint32_t ordinal5;
    };

    union
    {
        struct
        {
            uint32_t dw_offset : 16;
            uint32_t num_dwords : 16;
        } bitfields6;
        uint32_t data_lo;
        uint32_t cmp_data_lo;
        uint32_t reserved14;
        uint32_t ordinal6;
    };

    union
    {
        uint32_t data_hi;
        uint32_t cmp_data_hi;
        uint32_t reserved15;
        uint32_t reserved16;
        uint32_t ordinal7;
    };

    uint32_t int_ctxid;

} PM4ME_RELEASE_MEM__GFX09, *PPM4ME_RELEASE_MEM__GFX09;

//--------------------SET_CONFIG_REG--------------------
typedef struct PM4_ME_SET_CONFIG_REG
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 16;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4ME_SET_CONFIG_REG, *PPM4ME_SET_CONFIG_REG;

//--------------------SET_CONTEXT_REG--------------------
typedef struct PM4_ME_SET_CONTEXT_REG
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 16;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4ME_SET_CONTEXT_REG, *PPM4ME_SET_CONTEXT_REG;

//--------------------SET_CONTEXT_REG_INDEX__GFX09--------------------
typedef struct PM4_ME_SET_CONTEXT_REG_INDEX__GFX09
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 16;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4ME_SET_CONTEXT_REG_INDEX__GFX09, *PPM4ME_SET_CONTEXT_REG_INDEX__GFX09;

//--------------------SET_SH_REG--------------------
typedef struct PM4_ME_SET_SH_REG
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 16;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4ME_SET_SH_REG, *PPM4ME_SET_SH_REG;

//--------------------SET_SH_REG_INDEX--------------------
enum ME_SET_SH_REG_INDEX_index_enum
{
    index__me_set_sh_reg_index__apply_kmd_cu_and_mask = 3,
};

typedef struct PM4_ME_SET_SH_REG_INDEX
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 12;
            uint32_t index : 4;  // ME_SET_SH_REG_INDEX_index_enum
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4ME_SET_SH_REG_INDEX, *PPM4ME_SET_SH_REG_INDEX;

//--------------------SET_SH_REG_OFFSET--------------------
enum ME_SET_SH_REG_OFFSET_index_enum
{
    index__me_set_sh_reg_offset__normal_operation = 0,
    index__me_set_sh_reg_offset__data_indirect_2dw_256b = 1,
    index__me_set_sh_reg_offset__data_indirect_1dw = 2,
};

typedef struct PM4_ME_SET_SH_REG_OFFSET
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 14;
            uint32_t index : 2;  // ME_SET_SH_REG_OFFSET_index_enum
        } bitfields2;
        uint32_t ordinal2;
    };

    uint32_t calculated_lo;

    union
    {
        struct
        {
            uint32_t calculated_hi : 16;
            uint32_t driver_data : 16;
        } bitfields4;
        uint32_t ordinal4;
    };

} PM4ME_SET_SH_REG_OFFSET, *PPM4ME_SET_SH_REG_OFFSET;

//--------------------SET_UCONFIG_REG--------------------
typedef struct PM4_ME_SET_UCONFIG_REG
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 16;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4ME_SET_UCONFIG_REG, *PPM4ME_SET_UCONFIG_REG;

//--------------------SET_UCONFIG_REG_INDEX--------------------
typedef struct PM4_ME_SET_UCONFIG_REG_INDEX
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t reg_offset : 16;
            uint32_t reserved1 : 16;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4ME_SET_UCONFIG_REG_INDEX, *PPM4ME_SET_UCONFIG_REG_INDEX;

//--------------------STRMOUT_BUFFER_UPDATE--------------------
enum ME_STRMOUT_BUFFER_UPDATE_buffer_select_enum
{
    buffer_select__me_strmout_buffer_update__stream_out_buffer_0 = 0,
    buffer_select__me_strmout_buffer_update__stream_out_buffer_1 = 1,
    buffer_select__me_strmout_buffer_update__stream_out_buffer_2 = 2,
    buffer_select__me_strmout_buffer_update__stream_out_buffer_3 = 3,
};

enum ME_STRMOUT_BUFFER_UPDATE_data_type_enum
{
    data_type__me_strmout_buffer_update__dwords = 0,
    data_type__me_strmout_buffer_update__bytes = 1,
};

enum ME_STRMOUT_BUFFER_UPDATE_source_select_enum
{
    source_select__me_strmout_buffer_update__use_buffer_offset = 0,
    source_select__me_strmout_buffer_update__read_vgt_strmout_buffer_filled_size = 1,
    source_select__me_strmout_buffer_update__from_src_address = 2,
    source_select__me_strmout_buffer_update__none = 3,
};

enum ME_STRMOUT_BUFFER_UPDATE_update_memory_enum
{
    update_memory__me_strmout_buffer_update__dont_update_memory = 0,
    update_memory__me_strmout_buffer_update__update_memory_at_dst_address = 1,
};

typedef struct PM4_ME_STRMOUT_BUFFER_UPDATE
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t update_memory : 1;  // ME_STRMOUT_BUFFER_UPDATE_update_memory_enum
            uint32_t source_select : 2;  // ME_STRMOUT_BUFFER_UPDATE_source_select_enum
            uint32_t reserved1 : 4;
            uint32_t data_type : 1;      // ME_STRMOUT_BUFFER_UPDATE_data_type_enum
            uint32_t buffer_select : 2;  // ME_STRMOUT_BUFFER_UPDATE_buffer_select_enum
            uint32_t reserved2 : 22;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 2;
            uint32_t dst_address_lo : 30;
        } bitfields3;
        uint32_t ordinal3;
    };

    uint32_t dst_address_hi;

    uint32_t offset_or_address_lo;

    uint32_t src_address_hi;

} PM4ME_STRMOUT_BUFFER_UPDATE, *PPM4ME_STRMOUT_BUFFER_UPDATE;

//--------------------SWITCH_BUFFER--------------------
typedef struct PM4_ME_SWITCH_BUFFER
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        uint32_t ordinal2__GFX09;
    };

} PM4ME_SWITCH_BUFFER, *PPM4ME_SWITCH_BUFFER;

//--------------------WAIT_ON_CE_COUNTER--------------------
typedef struct PM4_ME_WAIT_ON_CE_COUNTER
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t cond_surface_sync : 1;
            uint32_t force_sync : 1;
            uint32_t reserved1 : 25;
            uint32_t mem_volatile : 1;
            uint32_t reserved2 : 4;
        } bitfields2;
        uint32_t ordinal2;
    };

} PM4ME_WAIT_ON_CE_COUNTER, *PPM4ME_WAIT_ON_CE_COUNTER;

//--------------------WAIT_REG_MEM--------------------
enum ME_WAIT_REG_MEM_cache_policy_enum
{
};

enum ME_WAIT_REG_MEM_engine_sel_enum
{
    engine_sel__me_wait_reg_mem__micro_engine = 0,
};

enum ME_WAIT_REG_MEM_function_enum
{
    function__me_wait_reg_mem__always_pass = 0,
    function__me_wait_reg_mem__less_than_ref_value = 1,
    function__me_wait_reg_mem__less_than_equal_to_the_ref_value = 2,
    function__me_wait_reg_mem__equal_to_the_reference_value = 3,
    function__me_wait_reg_mem__not_equal_reference_value = 4,
    function__me_wait_reg_mem__greater_than_or_equal_reference_value = 5,
    function__me_wait_reg_mem__greater_than_reference_value = 6,
};

enum ME_WAIT_REG_MEM_mem_space_enum
{
    mem_space__me_wait_reg_mem__register_space = 0,
    mem_space__me_wait_reg_mem__memory_space = 1,
};

enum ME_WAIT_REG_MEM_operation_enum
{
    operation__me_wait_reg_mem__wait_reg_mem = 0,
    operation__me_wait_reg_mem__wait_reg_mem_cond = 2,
    operation__me_wait_reg_mem__wait_mem_preemptable = 3,
};

typedef struct PM4_ME_WAIT_REG_MEM
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t function : 3;  // ME_WAIT_REG_MEM_function_enum
            uint32_t reserved1 : 1;
            uint32_t mem_space : 2;   // ME_WAIT_REG_MEM_mem_space_enum
            uint32_t operation : 2;   // ME_WAIT_REG_MEM_operation_enum
            uint32_t engine_sel : 2;  // ME_WAIT_REG_MEM_engine_sel_enum
            uint32_t reserved2 : 15;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 2;
            uint32_t mem_poll_addr_lo : 30;
        } bitfields3a;
        struct
        {
            uint32_t reg_poll_addr : 18;
            uint32_t reserved1 : 14;
        } bitfields3b;
        struct
        {
            uint32_t reg_write_addr1 : 18;
            uint32_t reserved1 : 14;
        } bitfields3c;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t reg_write_addr2 : 18;
            uint32_t reserved1 : 14;
        } bitfields4;
        uint32_t mem_poll_addr_hi;
        uint32_t ordinal4;
    };

    uint32_t reference;

    uint32_t mask;

    union
    {
        struct
        {
            uint32_t poll_interval : 16;
            uint32_t reserved1 : 16;
        } bitfields7;
        uint32_t ordinal7;
    };

} PM4ME_WAIT_REG_MEM, *PPM4ME_WAIT_REG_MEM;

//--------------------WAIT_REG_MEM64--------------------
enum ME_WAIT_REG_MEM64_cache_policy_enum
{
};

enum ME_WAIT_REG_MEM64_engine_sel_enum
{
    engine_sel__me_wait_reg_mem64__micro_engine = 0,
};

enum ME_WAIT_REG_MEM64_function_enum
{
    function__me_wait_reg_mem64__always_pass = 0,
    function__me_wait_reg_mem64__less_than_ref_value = 1,
    function__me_wait_reg_mem64__less_than_equal_to_the_ref_value = 2,
    function__me_wait_reg_mem64__equal_to_the_reference_value = 3,
    function__me_wait_reg_mem64__not_equal_reference_value = 4,
    function__me_wait_reg_mem64__greater_than_or_equal_reference_value = 5,
    function__me_wait_reg_mem64__greater_than_reference_value = 6,
};

enum ME_WAIT_REG_MEM64_mem_space_enum
{
    mem_space__me_wait_reg_mem64__register_space = 0,
    mem_space__me_wait_reg_mem64__memory_space = 1,
};

enum ME_WAIT_REG_MEM64_operation_enum
{
    operation__me_wait_reg_mem64__wait_reg_mem = 0,
    operation__me_wait_reg_mem64__wait_reg_mem_cond = 2,
    operation__me_wait_reg_mem64__wait_mem_preemptable = 3,
};

typedef struct PM4_ME_WAIT_REG_MEM64
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t function : 3;  // ME_WAIT_REG_MEM64_function_enum
            uint32_t reserved1 : 1;
            uint32_t mem_space : 2;   // ME_WAIT_REG_MEM64_mem_space_enum
            uint32_t operation : 2;   // ME_WAIT_REG_MEM64_operation_enum
            uint32_t engine_sel : 2;  // ME_WAIT_REG_MEM64_engine_sel_enum
            uint32_t reserved2 : 15;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t reserved1 : 3;
            uint32_t mem_poll_addr_lo : 29;
        } bitfields3a;
        struct
        {
            uint32_t reg_poll_addr : 18;
            uint32_t reserved1 : 14;
        } bitfields3b;
        struct
        {
            uint32_t reg_write_addr1 : 18;
            uint32_t reserved1 : 14;
        } bitfields3c;
        uint32_t ordinal3;
    };

    union
    {
        struct
        {
            uint32_t reg_write_addr2 : 18;
            uint32_t reserved1 : 14;
        } bitfields4;
        uint32_t mem_poll_addr_hi;
        uint32_t ordinal4;
    };

    uint32_t reference;

    uint32_t reference_hi;

    uint32_t mask;

    uint32_t mask_hi;

    union
    {
        struct
        {
            uint32_t poll_interval : 16;
            uint32_t reserved1 : 16;
        } bitfields9;
        uint32_t ordinal9;
    };

} PM4ME_WAIT_REG_MEM64, *PPM4ME_WAIT_REG_MEM64;

//--------------------WRITE_DATA--------------------
enum ME_WRITE_DATA_addr_incr_enum
{
    addr_incr__me_write_data__increment_address = 0,
    addr_incr__me_write_data__do_not_increment_address = 1,
};

enum ME_WRITE_DATA_cache_policy_enum
{
    cache_policy__me_write_data__lru = 0,
    cache_policy__me_write_data__stream = 1,
};

enum ME_WRITE_DATA_dst_sel_enum
{
    dst_sel__me_write_data__mem_mapped_register = 0,
    dst_sel__me_write_data__memory_sync_across_grbm = 1,
    dst_sel__me_write_data__tc_l2 = 2,
    dst_sel__me_write_data__gds = 3,
    dst_sel__me_write_data__memory = 5,
};

enum ME_WRITE_DATA_engine_sel_enum
{
    engine_sel__me_write_data__micro_engine = 0,
};

enum ME_WRITE_DATA_wr_confirm_enum
{
    wr_confirm__me_write_data__do_not_wait_for_write_confirmation = 0,
    wr_confirm__me_write_data__wait_for_write_confirmation = 1,
};

typedef struct PM4_ME_WRITE_DATA
{
    union
    {
        PM4_ME_TYPE_3_HEADER header;
        uint32_t             ordinal1;
    };

    union
    {
        struct
        {
            uint32_t                        reserved1 : 8;
            ME_WRITE_DATA_dst_sel_enum      dst_sel : 4;
            uint32_t                        reserved2 : 4;
            ME_WRITE_DATA_addr_incr_enum    addr_incr : 1;
            uint32_t                        reserved3 : 2;
            uint32_t                        resume_vf : 1;
            ME_WRITE_DATA_wr_confirm_enum   wr_confirm : 1;
            uint32_t                        reserved4 : 4;
            ME_WRITE_DATA_cache_policy_enum cache_policy : 2;
            uint32_t                        reserved5 : 3;
            ME_WRITE_DATA_engine_sel_enum   engine_sel : 2;
        } bitfields2;
        uint32_t ordinal2;
    };

    union
    {
        struct
        {
            uint32_t dst_mmreg_addr : 18;
            uint32_t reserved1 : 14;
        } bitfields3a;
        struct
        {
            uint32_t dst_gds_addr : 16;
            uint32_t reserved1 : 16;
        } bitfields3b;
        struct
        {
            uint32_t reserved1 : 2;
            uint32_t dst_mem_addr_lo : 30;
        } bitfields3c;
        uint32_t ordinal3;
    };

    uint32_t dst_mem_addr_hi;

} PM4ME_WRITE_DATA, *PPM4ME_WRITE_DATA;

}  // namespace Dive