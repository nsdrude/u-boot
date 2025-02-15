/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2018 Stefan Roese <sr@denx.de>
 */

#ifndef __CONFIG_GARDENA_SMART_GATEWAY_H
#define __CONFIG_GARDENA_SMART_GATEWAY_H

/* CPU */
#define CONFIG_SYS_MIPS_TIMER_FREQ	290000000

/* RAM */
#define CONFIG_SYS_SDRAM_BASE		0x80000000

#define CONFIG_SYS_INIT_SP_OFFSET	0x400000

/* SPL */

#define CONFIG_SYS_UBOOT_START		CONFIG_SYS_TEXT_BASE
#define CONFIG_SPL_BSS_START_ADDR	0x80010000
#define CONFIG_SPL_BSS_MAX_SIZE		0x10000
#define CONFIG_SPL_MAX_SIZE		0x10000
#define CONFIG_SPL_PAD_TO		0

/* Dummy value */
#define CONFIG_SYS_UBOOT_BASE		0

/* Serial SPL */
#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_SERIAL)
#define CONFIG_SYS_NS16550_MEM32
#define CONFIG_SYS_NS16550_CLK		40000000
#define CONFIG_SYS_NS16550_REG_SIZE	-4
#define CONFIG_SYS_NS16550_COM1		0xb0000c00
#endif

/* UART */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200, \
					  230400, 460800, 921600 }

/* RAM */

/* Memory usage */
#define CONFIG_SYS_MAXARGS		64
#define CONFIG_SYS_BOOTPARAMS_LEN	(128 * 1024)
#define CONFIG_SYS_CBSIZE		512

/* Environment settings */

/*
 * Environment is right behind U-Boot in flash. Make sure U-Boot
 * doesn't grow into the environment area.
 */
#define CONFIG_BOARD_SIZE_LIMIT		CONFIG_ENV_OFFSET

#endif /* __CONFIG_GARDENA_SMART_GATEWAY_H */
