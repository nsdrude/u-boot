/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2011 Freescale Semiconductor, Inc.
 * Jason Liu <r64343@freescale.com>
 *
 * Configuration settings for Freescale MX53 low cost board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/arch/imx-regs.h>

#define CONFIG_MXC_UART_BASE	UART1_BASE

/* MMC Configs */
#define CONFIG_SYS_FSL_ESDHC_ADDR	0
#define CONFIG_SYS_FSL_ESDHC_NUM	2

/* USB Configs */
#define CONFIG_MXC_USB_PORT	1
#define CONFIG_MXC_USB_PORTSC	(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS	0

/* PMIC Controller */
#define CONFIG_POWER_FSL
#define CONFIG_POWER_FSL_MC13892
#define CONFIG_SYS_DIALOG_PMIC_I2C_ADDR	0x48
#define CONFIG_SYS_FSL_PMIC_I2C_ADDR	0x8

/* Command definition */

#define CONFIG_EXTRA_ENV_SETTINGS \
	"script=boot.scr\0" \
	"image=zImage\0" \
	"fdt_addr=0x71000000\0" \
	"boot_fdt=try\0" \
	"ip_dyn=yes\0" \
	"mmcdev=0\0" \
	"mmcpart=1\0" \
	"mmcroot=/dev/mmcblk0p2 rw rootwait\0" \
	"mmcargs=setenv bootargs console=ttymxc0,${baudrate} root=${mmcroot}\0" \
	"loadbootscript=" \
		"load mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0" \
	"bootscript=echo Running bootscript from mmc ...; " \
		"source\0" \
	"loadimage=load mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
	"loadfdt=load mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if run loadfdt; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \
	"netargs=setenv bootargs console=ttymxc0,${baudrate} " \
		"root=/dev/nfs " \
		"ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
	"netboot=echo Booting from net ...; " \
		"run netargs; " \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi; " \
		"${get_cmd} ${image}; " \
		"if test ${boot_fdt} = yes ||  test ${boot_fdt} = try; then " \
			"if ${get_cmd} ${fdt_addr} ${fdt_file}; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo ERROR: Cannot load the DT; " \
					"exit; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0"

/* Miscellaneous configurable options */
#define CONFIG_SYS_CBSIZE		512	/* Console I/O Buffer Size */

/* Physical Memory Map */
#define PHYS_SDRAM_1			CSD0_BASE_ADDR
#define PHYS_SDRAM_1_SIZE		(gd->bd->bi_dram[0].size)
#define PHYS_SDRAM_2			CSD1_BASE_ADDR
#define PHYS_SDRAM_2_SIZE		(gd->bd->bi_dram[1].size)
#define PHYS_SDRAM_SIZE			(gd->ram_size)

#define CONFIG_SYS_SDRAM_BASE		(PHYS_SDRAM_1)
#define CONFIG_SYS_INIT_RAM_ADDR	(IRAM_BASE_ADDR)
#define CONFIG_SYS_INIT_RAM_SIZE	(IRAM_SIZE)

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* Environment starts at 768k = 768 * 1024 = 786432 */
/*
 * Detect overlap between U-Boot image and environment area in build-time
 *
 * CONFIG_BOARD_SIZE_LIMIT = CONFIG_ENV_OFFSET - u-boot.imx offset
 * CONFIG_BOARD_SIZE_LIMIT = 768k - 1k = 767k = 785408
 *
 * Currently CONFIG_BOARD_SIZE_LIMIT does not handle expressions, so
 * write the direct value here
 */
#define CONFIG_BOARD_SIZE_LIMIT		785408

#ifdef CONFIG_CMD_SATA
	#define CONFIG_DWC_AHSATA_PORT_ID       0
	#define CONFIG_DWC_AHSATA_BASE_ADDR     SATA_BASE_ADDR
	#define CONFIG_LBA48
#endif

/* Framebuffer and LCD */

#endif				/* __CONFIG_H */
