/*
 * Copyright (C) 2018 XRADIO TECHNOLOGY CO., LTD. All rights reserved.
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

#include "cmd_util.h"
#include "cmd_keyboard.h"
#include "kernel/os/os.h"
#include "driver/chip/hal_keyboard.h"


#define NON_KEY_PRESS            0xffffffff
#define KeyTask_PRIO             4
#define KeyTask_STACKSIZE        1024
static OS_Thread_t g_key_thread;

typedef struct {
	OS_Semaphore_t   key_sem;
	uint8_t          len;
	uint32_t         buffer[KEY_SCAN_BUFFER_MAX];
	uint8_t          p_col;
	uint8_t          p_row;
	uint8_t          flag;
} key_priv;

static key_priv      gkeypriv;

void keyboard_press_cols_rows(uint8_t index, uint32_t value)
{
	for (uint8_t i = 0; i < 32; i++) {
		if ((value & 0x01) == 0) {
			gkeypriv.p_row = i % KEY_SCAN_ROWS_MAX;
			gkeypriv.p_col = (index * 32 + i) / KEY_SCAN_ROWS_MAX;
			CMD_DBG("press key row: %d, col: %d\n", gkeypriv.p_row,
			        gkeypriv.p_col);
		}
		value >>= 1;
	}
}

/*
* keyboard callback function
*/
void keyboard_callback(uint32_t *rowdata, uint8_t len)
{
	OS_Status ret;

	gkeypriv.len = len;
	for (uint8_t i = 0; i < len; i++) {
		gkeypriv.buffer[i] = rowdata[i];
	}
	gkeypriv.flag = 1;
	ret = OS_SemaphoreRelease(&gkeypriv.key_sem);
	if (ret != OS_OK)
		CMD_ERR("%s,%d release semap err!\n", __func__, __LINE__);
}

void Get_KeyValue_Task(void *arg)
{
	while (1) {
		if (OS_SemaphoreWait(&gkeypriv.key_sem, OS_WAIT_FOREVER) != OS_OK)
			continue;

		for (uint8_t i = 0; i < gkeypriv.len; i++) {
			if ((gkeypriv.buffer[i] != NON_KEY_PRESS)) {
				CMD_DBG("keydata[%d]: 0x%08x\n", i, gkeypriv.buffer[i]);
				keyboard_press_cols_rows(i, gkeypriv.buffer[i]);
			}
		}
	}
}

/*
 * drv keyboard open f=<freq> c=<cols> r=<rows> t=<timecycle> s=<scan> d=<debounce>
 */
static enum cmd_status cmd_keyboard_open_exec(char *cmd)
{
	keyboard_InitParam param;
	uint32_t freq, cols, rows, time, scan, debounce;
	int cnt;

	cnt = cmd_sscanf(cmd, "f=%u c=0x%x r=0x%x t=0x%x s=0x%x d=0x%x",
	                 &freq, &cols, &rows, &time, &scan, &debounce);
	if (cnt != 6) {
		return CMD_STATUS_INVALID_ARG;
	}
	param.freq      = freq;
	param.cols      = cols;
	param.rows      = rows;
	param.timecycle = time;//0x3c00;
	param.scan      = scan;//0x100;
	param.debounce  = debounce;//0x100;

	HAL_KeyBoard_Open(&param, keyboard_callback);

	if (OS_SemaphoreCreate(&gkeypriv.key_sem, 0, 1) != OS_OK) {
		CMD_ERR("create semaphore failed\n");
		return -1;
	}

	if (OS_ThreadCreate(&g_key_thread,
	                    "user",
	                    Get_KeyValue_Task,
	                    NULL,
	                    KeyTask_PRIO,
	                    KeyTask_STACKSIZE) != OS_OK) {
		CMD_ERR("create key task failed!\r\n");
	}

	return CMD_STATUS_OK;
}

/*
 * drv keyboard close
 */
static enum cmd_status cmd_keyboard_close_exec(char *cmd)
{
	OS_SemaphoreDelete(&gkeypriv.key_sem);
	OS_ThreadDelete(&g_key_thread);
	HAL_KeyBoard_Close();
	return CMD_STATUS_OK;
}

static struct cmd_data g_keyboard_cmds[] = {
	{"open",  cmd_keyboard_open_exec},
	{"close", cmd_keyboard_close_exec},
};

enum cmd_status cmd_keyboard_exec(char *cmd)
{
	return cmd_exec(cmd, g_keyboard_cmds, cmd_nitems(g_keyboard_cmds));
}

