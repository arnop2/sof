// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright 2019 NXP
//
// Author: Daniel Baluta <daniel.baluta@nxp.com>

#include <sof/alloc.h>
#include <ipc/header.h>

STATIC_ASSERT(0 == (HEAP_BUF_ALIGNMENT % PLATFORM_DCACHE_ALIGN),
	      invalid_heap_buf_alignment);

/* Heap blocks for system runtime */
static struct block_hdr sys_rt_block64[HEAP_SYS_RT_COUNT64];
static struct block_hdr sys_rt_block512[HEAP_SYS_RT_COUNT512];
static struct block_hdr sys_rt_block1024[HEAP_SYS_RT_COUNT1024];

/* Heap memory for system runtime */
static struct block_map sys_rt_heap_map[] = {
	BLOCK_DEF(64, HEAP_SYS_RT_COUNT64, sys_rt_block64),
	BLOCK_DEF(512, HEAP_SYS_RT_COUNT512, sys_rt_block512),
	BLOCK_DEF(1024, HEAP_SYS_RT_COUNT1024, sys_rt_block1024),
};

/* Heap blocks for modules */
static struct block_hdr mod_block16[HEAP_RT_COUNT16];
static struct block_hdr mod_block32[HEAP_RT_COUNT32];
static struct block_hdr mod_block64[HEAP_RT_COUNT64];
static struct block_hdr mod_block128[HEAP_RT_COUNT128];
static struct block_hdr mod_block256[HEAP_RT_COUNT256];
static struct block_hdr mod_block512[HEAP_RT_COUNT512];
static struct block_hdr mod_block1024[HEAP_RT_COUNT1024];

/* Heap memory map for modules */
static struct block_map rt_heap_map[] = {
	BLOCK_DEF(16, HEAP_RT_COUNT16, mod_block16),
	BLOCK_DEF(32, HEAP_RT_COUNT32, mod_block32),
	BLOCK_DEF(64, HEAP_RT_COUNT64, mod_block64),
	BLOCK_DEF(128, HEAP_RT_COUNT128, mod_block128),
	BLOCK_DEF(256, HEAP_RT_COUNT256, mod_block256),
	BLOCK_DEF(512, HEAP_RT_COUNT512, mod_block512),
	BLOCK_DEF(1024, HEAP_RT_COUNT1024, mod_block1024),
};

/* Heap blocks for buffers */
static struct block_hdr buf_block[HEAP_BUFFER_COUNT];

/* Heap memory map for buffers */
static struct block_map buf_heap_map[] = {
	BLOCK_DEF(HEAP_BUFFER_BLOCK_SIZE, HEAP_BUFFER_COUNT, buf_block),
};

struct mm memmap = {
	.system[0] = {
		.heap = HEAP_SYSTEM_BASE,
		.size = HEAP_SYSTEM_SIZE,
		.info = {.free = HEAP_SYSTEM_SIZE,},
		.caps = SOF_MEM_CAPS_RAM | SOF_MEM_CAPS_CACHE |
			SOF_MEM_CAPS_DMA,
	},
	.system_runtime[0] = {
		.blocks = ARRAY_SIZE(sys_rt_heap_map),
		.map = sys_rt_heap_map,
		.heap = HEAP_SYS_RUNTIME_BASE,
		.size = HEAP_SYS_RUNTIME_SIZE,
		.info = {.free = HEAP_SYS_RUNTIME_SIZE,},
		.caps = SOF_MEM_CAPS_RAM | SOF_MEM_CAPS_CACHE |
			SOF_MEM_CAPS_DMA,
	},
	.runtime[0] = {
		.blocks = ARRAY_SIZE(rt_heap_map),
		.map = rt_heap_map,
		.heap = HEAP_RUNTIME_BASE,
		.size = HEAP_RUNTIME_SIZE,
		.info = {.free = HEAP_RUNTIME_SIZE,},
		.caps = SOF_MEM_CAPS_RAM | SOF_MEM_CAPS_CACHE |
			SOF_MEM_CAPS_DMA,
	},
	.buffer[0] = {
		.blocks = ARRAY_SIZE(buf_heap_map),
		.map = buf_heap_map,
		.heap = HEAP_BUFFER_BASE,
		.size = HEAP_BUFFER_SIZE,
		.info = {.free = HEAP_BUFFER_SIZE,},
		.caps = SOF_MEM_CAPS_RAM | SOF_MEM_CAPS_CACHE |
			SOF_MEM_CAPS_DMA,
	},
	.total = {.free = HEAP_SYSTEM_SIZE + HEAP_SYS_RUNTIME_SIZE +
			HEAP_RUNTIME_SIZE + HEAP_BUFFER_SIZE,},
};

void platform_init_memmap(void)
{
	/* memmap has been initialized statically as a part of .data */
}
