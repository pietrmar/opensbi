#ifndef __REGS__H__
#define __REGS__H__

#define REG_READ(__reg) (*(volatile uint32_t *)(__reg))
#define REG_WRITE(__reg, __value) (*(volatile uint32_t *)(__reg) = (__value))

#define DEBUG_OUTPUT_REG	0x40001000

#endif /* __REGS__H__ */
