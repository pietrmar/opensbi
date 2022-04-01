/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 */

#include <sbi/riscv_io.h>
#include <sbi/riscv_asm.h>
#include <sbi/riscv_encoding.h>
#include <sbi/sbi_const.h>
#include <sbi/sbi_platform.h>
#include <sbi/sbi_console.h>
#include <sbi_utils/timer/aclint_mtimer.h>

#include "rrv_regs.h"

static void rrv_debug_putc(char ch)
{
	writel(ch, (uint32_t *)RRV_DEBUG_OUTPUT_REG);
}

static struct sbi_console_device rrv_debug_console = {
	.name = "rrv-debug",
	.console_putc = rrv_debug_putc,
};

static struct aclint_mtimer_data mtimer = {
	.mtime_freq = RRV_ACLINT_MTIME_FREQ,
	.mtime_addr = RRV_ACLINT_MTIME_ADDR,
	.mtime_size = ACLINT_DEFAULT_MTIME_SIZE,
	.mtimecmp_addr = RRV_ACLINT_MTIMECMP_ADDR,
	.mtimecmp_size = RRV_ACLINT_MTIMECMP_SIZE,
	.first_hartid = 0,
	.hart_count = 1,
};

/*
 * Initialize the platform console.
 */
static int platform_console_init(void)
{
	sbi_console_set_device(&rrv_debug_console);
	return 0;
}

static int platform_timer_init(bool cold_boot)
{
	int rc;

	if (cold_boot) {
		rc = aclint_mtimer_cold_init(&mtimer, NULL);
		if (rc)
			return rc;
	}

	return aclint_mtimer_warm_init();
}

/*
 * Platform descriptor.
 */
const struct sbi_platform_operations platform_ops = {
	.console_init		= platform_console_init,
	.timer_init		= platform_timer_init,
};

const struct sbi_platform platform = {
	.opensbi_version	= OPENSBI_VERSION,
	.platform_version	= SBI_PLATFORM_VERSION(0x0, 0x00),
	.name			= "rrv",
	// .features		= SBI_PLATFORM_DEFAULT_FEATURES,
	.features		= 0,
	.hart_count		= 1,
	.hart_stack_size	= SBI_PLATFORM_DEFAULT_HART_STACK_SIZE,
	.platform_ops_addr	= (unsigned long)&platform_ops
};
