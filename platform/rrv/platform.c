/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_encoding.h>
#include <sbi/sbi_const.h>
#include <sbi/sbi_platform.h>
#include <sbi/sbi_console.h>

#include "regs.h"

static void rrv_debug_putc(char ch)
{
	REG_WRITE(DEBUG_OUTPUT_REG, ch);
}

static struct sbi_console_device rrv_debug_console = {
	.name = "rrv-debug",
	.console_putc = rrv_debug_putc,
};

/*
 * Initialize the platform console.
 */
static int platform_console_init(void)
{
	sbi_console_set_device(&rrv_debug_console);
	return 0;
}

/*
 * Platform descriptor.
 */
const struct sbi_platform_operations platform_ops = {
	.console_init		= platform_console_init,
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
