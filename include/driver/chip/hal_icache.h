/**
 * @file  hal_icache.h
 * @author  XRADIO IOT WLAN Team
 */

/*
 * Copyright (C) 2017 XRADIO TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of XRADIO TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _DRIVER_CHIP_HAL_ICACHE_H_
#define _DRIVER_CHIP_HAL_ICACHE_H_

#include <stdbool.h>
#include "sys/param.h"
#include "driver/chip/hal_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (CONFIG_CHIP_ARCH_VER == 2)

typedef struct {
	uint32_t way_mode;
	uint8_t vc_en;
	uint8_t wrap_en;
	uint8_t bypass;
} ICache_Config;

typedef struct {
	/*uint32_t prefetch_cache_size;*/   /* in bytes, recommended size is no more than ICache_Config.cache_size */
	bool prefetch_2nd_branch;
	uint32_t addr_prefetch_start;
} ICache_PrefetchConfig;

typedef enum {
	FLASH_CACHE_PREFETCH_ENABLE = 0,
	FLASH_CACHE_PREFETCH_DISABLE = 1
} Flash_Cache_Prefetch;

typedef struct {
	struct {
		uint32_t addr_interrupt_vector;
		uint32_t addr_interrupt_cb;
	} prefetch_interrupt[16];
} FlashCache_PrefetchIntConfig;

typedef struct {
	__IO uint32_t CACHE_COM_CFG;                    /* ,     Address offset: 0x000   */
	__IO uint32_t RESERVE4[39];
	__I uint32_t MISS_COUNT_H;                      /* ,     Address offset: 0x0A0   */
	__I uint32_t MISS_COUNT_L;                      /* ,     Address offset: 0x0A4   */
	__I uint32_t HIT_COUNT_H;                       /* ,     Address offset: 0x0A8   */
	__I uint32_t HIT_COUNT_L;                       /* ,     Address offset: 0x0AC   */
	__I uint32_t CACHE_STA;                         /* ,     Address offset: 0x0B0   */
	__I uint32_t INSTR_WAIT_H;                      /* ,     Address offset: 0x0B4   */
	__I uint32_t INSTR_WAIT_L;                      /* ,     Address offset: 0x0B8   */
} ICACHE_T;
#define ICACHE_CTRL ((ICACHE_T *)FLASH_CACHE_BASE)
/* I-cache Common Configuration */
#define ICACHE_ENABLE_SHIFT                     0
#define ICACHE_ENABLE_MASK                      (0x1U << ICACHE_ENABLE_SHIFT)
#define ICACHE_ASSOCIATE_MODE_SHIFT             3
#define ICACHE_ASSOCIATE_MODE_MASK              (0x3U << ICACHE_ASSOCIATE_MODE_SHIFT)
enum ICACHE_ASSO_MOD {
	ICACHE_ASSO_MOD_DIR =                       (0 << ICACHE_ASSOCIATE_MODE_SHIFT),
	ICACHE_ASSO_MOD_2W  =                       (1 << ICACHE_ASSOCIATE_MODE_SHIFT),
	ICACHE_ASSO_MOD_4W  =                       (2 << ICACHE_ASSOCIATE_MODE_SHIFT),
};

#define ICACHE_FLUSH_ALL_SHIFT                  5
#define ICACHE_FLUSH_ALL_MASK                   (0x1U << ICACHE_FLUSH_ALL_SHIFT)
#define ICACHE_EN_VICTIM_CACHE_SHIFT            6
#define ICACHE_EN_VICTIM_CACHE_MASK             (0x1U << ICACHE_EN_VICTIM_CACHE_SHIFT)
#define ICACHE_EN_ICACHE_WRAP_SHIFT             7
#define ICACHE_EN_ICACHE_WRAP_MASK              (0x1U << ICACHE_EN_ICACHE_WRAP_SHIFT)
#define ICACHE_COUNTER_EN_SHIFT                 8
#define ICACHE_COUNTER_EN_MASK                  (0x1U << ICACHE_COUNTER_EN_SHIFT)
#define ICACHE_CBUS_HREADY_TIMEOUT_EN_SHIFT     9
#define ICACHE_CBUS_HREADY_TIMEOUT_EN_MASK      (0x1U << ICACHE_CBUS_HREADY_TIMEOUT_EN_SHIFT)
#define ICACHE_CBUS_HREADY_WAIT_TIMEOUT_SHIFT   10
#define ICACHE_CBUS_HREADY_WAIT_TIMEOUT_MASK    (0xFFU << ICACHE_CBUS_HREADY_WAIT_TIMEOUT_SHIFT)

/* Miss Count Status H-Register */
#define ICACHE_MISS_COUNT_H_SHIFT               0
#define ICACHE_MISS_COUNT_H_MASK                (0xFFFFU << ICACHE_MISS_COUNT_H_SHIFT)

/* Miss Count Status L-Register */
#define ICACHE_MISS_COUNT_L_SHIFT               0
#define ICACHE_MISS_COUNT_L_MASK                (0xFFFFU << ICACHE_MISS_COUNT_L_SHIFT)

/* Hit Count Status H-Register */
#define ICACHE_HIT_COUNT_H_SHIFT                0
#define ICACHE_HIT_COUNT_H_MASK                 (0xFFFFFFFFU << ICACHE_HIT_COUNT_H_SHIFT)

/* Hit Count Status L-Register */
#define ICACHE_HIT_COUNT_L_SHIFT                0
#define ICACHE_HIT_COUNT_L_MASK                 (0xFFFFFFFFU << ICACHE_HIT_COUNT_L_SHIFT)

/* Cache State Register */
#define ICACHE_CACHE_STATE_SHIFT                0
#define ICACHE_CACHE_STATE_MASK                 (0x7U << ICACHE_CACHE_STATE_SHIFT)

/* Instruction Wait Cycle H-Register */
#define ICACHE_INSTR_WAIT_H_SHIFT               0
#define ICACHE_INSTR_WAIT_H_MASK                (0xFFFFFFFFU << ICACHE_INSTR_WAIT_H_SHIFT)

/* Instruction Wait Cycle L-Register */
#define ICACHE_INSTR_WAIT_L_SHIFT               0
#define ICACHE_INSTR_WAIT_L_MASK                (0xFFFFFFFFU << ICACHE_INSTR_WAIT_L_SHIFT)

#define ICACHE_ASSOCIATE_MODE_DIRECT            0
#define ICACHE_ASSOCIATE_MODE_TWO_WAY           1
#define ICACHE_ASSOCIATE_MODE_FOUR_WAY          2

void HAL_ICache_Flush(void);

HAL_Status HAL_ICache_Config(ICache_Config *cfg);
HAL_Status HAL_ICache_DeConfig(void);

HAL_Status HAL_ICache_Init(ICache_Config *cfg);
HAL_Status HAL_ICache_Deinit(void);

HAL_Status HAL_ICache_EnablePrefetch(ICache_PrefetchConfig *cfg);
HAL_Status HAL_ICache_DisablePrefetch(void);
#endif /* CONFIG_CHIP_ARCH_VER */

#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_CHIP_HAL_ICACHE_H_ */
