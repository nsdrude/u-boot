/* SPDX-License-Identifier: GPL-2.0
 *
 * Copyright (C) 2017-2019 Intel Corporation <www.intel.com>
 *
 */

#ifndef __CONFIG_SOCFPGA_SOC64_COMMON_H__
#define __CONFIG_SOCFPGA_SOC64_COMMON_H__

#include <asm/arch/base_addr_soc64.h>
#include <asm/arch/handoff_soc64.h>
#include <linux/stringify.h>

/*
 * U-Boot general configurations
 */
/* sysmgr.boot_scratch_cold4 & 5 (64bit) will be used for PSCI_CPU_ON call */
#define CPU_RELEASE_ADDR		0xFFD12210

/*
 * U-Boot console configurations
 */
#define CONFIG_SYS_MAXARGS		64
#define CONFIG_SYS_CBSIZE		2048
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

/* Extend size of kernel image for uncompression */
#define CONFIG_SYS_BOOTM_LEN		(32 * 1024 * 1024)

/*
 * U-Boot run time memory configurations
 */
#define CONFIG_SYS_INIT_RAM_ADDR	0xFFE00000
#define CONFIG_SYS_INIT_RAM_SIZE	0x40000
#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR  \
					+ CONFIG_SYS_INIT_RAM_SIZE \
					- SOC64_HANDOFF_SIZE)
#else
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_TEXT_BASE \
					+ 0x100000)
#endif
#define CONFIG_SYS_INIT_SP_OFFSET	(CONFIG_SYS_INIT_SP_ADDR)

/*
 * U-Boot environment configurations
 */

/*
 * QSPI support
 */
 #ifdef CONFIG_CADENCE_QSPI
/* Enable it if you want to use dual-stacked mode */
/*#define CONFIG_QSPI_RBF_ADDR		0x720000*/

/* Flash device info */

#ifndef CONFIG_SPL_BUILD
#define MTDIDS_DEFAULT			"nor0=ff705000.spi.0"
#endif /* CONFIG_SPL_BUILD */

#ifndef __ASSEMBLY__
unsigned int cm_get_qspi_controller_clk_hz(void);
#define CONFIG_CQSPI_REF_CLK		cm_get_qspi_controller_clk_hz()
#endif

#endif /* CONFIG_CADENCE_QSPI */

/*
 * Environment variable
 */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=" __stringify(CONFIG_SYS_LOAD_ADDR) "\0" \
	"bootfile=" CONFIG_BOOTFILE "\0" \
	"fdt_addr=8000000\0" \
	"fdtimage=" CONFIG_DEFAULT_DEVICE_TREE ".dtb\0" \
	"mmcroot=/dev/mmcblk0p2\0" \
	"mmcboot=setenv bootargs " CONFIG_BOOTARGS \
		" root=${mmcroot} rw rootwait;" \
		"booti ${loadaddr} - ${fdt_addr}\0" \
	"mmcload=mmc rescan;" \
		"load mmc 0:1 ${loadaddr} ${bootfile};" \
		"load mmc 0:1 ${fdt_addr} ${fdtimage}\0" \
	"mmcfitboot=setenv bootargs " CONFIG_BOOTARGS \
		" root=${mmcroot} rw rootwait;" \
		"bootm ${loadaddr}\0" \
	"mmcfitload=mmc rescan;" \
		"load mmc 0:1 ${loadaddr} ${bootfile}\0" \
	"linux_qspi_enable=if sf probe; then " \
		"echo Enabling QSPI at Linux DTB...;" \
		"fdt addr ${fdt_addr}; fdt resize;" \
		"fdt set /soc/spi@ff8d2000 status okay;" \
		"fdt set /soc/clkmgr/clocks/qspi_clk clock-frequency " \
		" ${qspi_clock}; fi; \0" \
	"scriptaddr=0x02100000\0" \
	"scriptfile=u-boot.scr\0" \
	"fatscript=if fatload mmc 0:1 ${scriptaddr} ${scriptfile};" \
		   "then source ${scriptaddr}; fi\0" \
	"socfpga_legacy_reset_compat=1\0"

/*
 * External memory configurations
 */
#define PHYS_SDRAM_1			0x0
#define PHYS_SDRAM_1_SIZE		(1 * 1024 * 1024 * 1024)
#define CONFIG_SYS_SDRAM_BASE		0

/*
 * Serial / UART configurations
 */
#define CONFIG_SYS_NS16550_CLK		100000000
#define CONFIG_SYS_NS16550_MEM32

/*
 * Timer & watchdog configurations
 */
#define COUNTER_FREQUENCY		400000000

/*
 * SDMMC configurations
 */
#ifdef CONFIG_CMD_MMC
#define CONFIG_SYS_MMC_MAX_BLK_COUNT	256
#endif
/*
 * Flash configurations
 */

/* Ethernet on SoC (EMAC) */
#if defined(CONFIG_CMD_NET)
#define CONFIG_DW_ALTDESCRIPTOR
#endif /* CONFIG_CMD_NET */

/*
 * L4 Watchdog
 */
#define CONFIG_DW_WDT_BASE		SOCFPGA_L4WD0_ADDRESS
#ifdef CONFIG_TARGET_SOCFPGA_STRATIX10
#ifndef __ASSEMBLY__
unsigned int cm_get_l4_sys_free_clk_hz(void);
#define CONFIG_DW_WDT_CLOCK_KHZ		(cm_get_l4_sys_free_clk_hz() / 1000)
#endif
#else
#define CONFIG_DW_WDT_CLOCK_KHZ		100000
#endif

/*
 * SPL memory layout
 *
 * On chip RAM
 * 0xFFE0_0000 ...... Start of OCRAM
 * SPL code, rwdata
 * empty space
 * 0xFFEx_xxxx ...... Top of stack (grows down)
 * 0xFFEy_yyyy ...... Global Data
 * 0xFFEz_zzzz ...... Malloc prior relocation (size CONFIG_SYS_MALLOC_F_LEN)
 * 0xFFE3_F000 ...... Hardware handdoff blob (size 4KB)
 * 0xFFE3_FFFF ...... End of OCRAM
 *
 * SDRAM
 * 0x0000_0000 ...... Start of SDRAM_1
 * unused / empty space for image loading
 * Size 64MB   ...... MALLOC (size CONFIG_SYS_SPL_MALLOC_SIZE)
 * Size 1MB    ...... BSS (size CONFIG_SPL_BSS_MAX_SIZE)
 * 0x8000_0000 ...... End of SDRAM_1 (assume 2GB)
 *
 */
#define CONFIG_SPL_TARGET		"spl/u-boot-spl-dtb.hex"
#define CONFIG_SPL_MAX_SIZE		CONFIG_SYS_INIT_RAM_SIZE
#define CONFIG_SPL_STACK		CONFIG_SYS_INIT_SP_ADDR
#define CONFIG_SPL_BSS_MAX_SIZE		0x100000	/* 1 MB */
#define CONFIG_SPL_BSS_START_ADDR	(PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE \
					- CONFIG_SPL_BSS_MAX_SIZE)
#define CONFIG_SYS_SPL_MALLOC_SIZE	(CONFIG_SYS_MALLOC_LEN)
#define CONFIG_SYS_SPL_MALLOC_START	(CONFIG_SPL_BSS_START_ADDR \
					- CONFIG_SYS_SPL_MALLOC_SIZE)

/* SPL SDMMC boot support */
#ifdef CONFIG_SPL_LOAD_FIT
#define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME		"u-boot.itb"
#else
#define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME		"u-boot.img"
#endif

#endif	/* __CONFIG_SOCFPGA_SOC64_COMMON_H__ */
