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

#ifndef _PRJ_CONFIG_H_
#define _PRJ_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * project base config
 */

/* main thread priority */
#define PRJCONF_MAIN_THREAD_PRIO        OS_THREAD_PRIO_APP

/* main thread stack size */
#define PRJCONF_MAIN_THREAD_STACK_SIZE  (16 * 1024)

/* sys ctrl enable/disable */
#define PRJCONF_SYS_CTRL_EN             1

/* sys ctrl thread priority */
#define PRJCONF_SYS_CTRL_PRIO           OS_THREAD_PRIO_SYS_CTRL

/* sys ctrl stack size */
#define PRJCONF_SYS_CTRL_STACK_SIZE     (2 * 1024)

/* sys ctrl queue length for receiving message */
#define PRJCONF_SYS_CTRL_QUEUE_LEN      6

/* image flash ID */
#define PRJCONF_IMG_FLASH               0

/* image start address, including bootloader */
#define PRJCONF_IMG_ADDR                (0x00000000)
#if (CONFIG_CHIP_ARCH_VER > 1)
/* icache and dcache size config */
#define PRJCONF_CACHE_SIZE              (DCACHE_ASSOCIATE_MODE_FOUR_WAY) /* 32K */
#endif

/* icache and dcache size config */
#define PRJCONF_ICACHE_MODE             (ICACHE_ASSOCIATE_MODE_TWO_WAY) /* 16K */
#define PRJCONF_DCACHE_MODE             (DCACHE_ASSOCIATE_MODE_TWO_WAY) /* 16K */
#define PRJCONF_CACHE_MIXED_MODE        (DCACHE_MIXED_MODE_ID)

/* image max size, including bootloader */
#define PRJCONF_IMG_MAX_SIZE            ((1024 - 4) * 1024)

/* save sysinfo to flash or not */
#define PRJCONF_SYSINFO_SAVE_TO_FLASH   0

#if PRJCONF_SYSINFO_SAVE_TO_FLASH

/* sysinfo flash ID */
#define PRJCONF_SYSINFO_FLASH           0

/* sysinfo start address */
#define PRJCONF_SYSINFO_ADDR            (PRJCONF_IMG_ADDR + PRJCONF_IMG_MAX_SIZE)

/* sysinfo size */
#define PRJCONF_SYSINFO_SIZE            (4 * 1024)

/* enable/disable checking whether sysinfo is overlap with image */
#define PRJCONF_SYSINFO_CHECK_OVERLAP   0

#endif /* PRJCONF_SYSINFO_SAVE_TO_FLASH */

/* MAC address source */
#define PRJCONF_MAC_ADDR_SOURCE         SYSINFO_MAC_ADDR_CHIPID

/* watchdog enable/disable */
#define PRJCONF_WDG_EN                  0

/* watchdog timeout value */
#define PRJCONF_WDG_TIMEOUT             WDG_TIMEOUT_16SEC

/* watchdog feeding period (in ms), MUST less than PRJCONF_WDG_TIMEOUT */
#define PRJCONF_WDG_FEED_PERIOD         (10 * 1000)

/*
 * project hardware feature
 */

/* uart enable/disable */
#define PRJCONF_UART_EN                 1

/* h/w crypto engine enable/disable */
#define PRJCONF_CE_EN                   1

#define PRJCONF_EFUSE_EN                1

/* spi enable/disable */
#define PRJCONF_SPI_EN                  1

/* Xradio internal codec sound card enable/disable */
#define PRJCONF_INTERNAL_SOUNDCARD_EN   0

/* AC107 sound card enable/disable */
#define PRJCONF_AC107_SOUNDCARD_EN      0

/*
 * project service feature
 */

/* console enable/disable */
#define PRJCONF_CONSOLE_EN              1

/* network and wlan enable/disable */
#define PRJCONF_NET_EN                  0

#define PRJCONF_TEMP_MONITOR_EN         0

/* environment variable "TZ" for time zone setting */
#define PRJCONF_ENV_TZ                  "TZ=GMT-8"

#ifdef CONFIG_BLE
#define PRJCONF_BLE_ETF
#endif

#ifdef __cplusplus
}
#endif

#endif /* _PRJ_CONFIG_H_ */
