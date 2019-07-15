/*----------------------------------------------------------------------------*/
/*

	WiringPi ODROID-N1 Board Header file

 */
/*----------------------------------------------------------------------------*/
#ifndef	__ODROID_N1_H__
#define	__ODROID_N1_H__

/*----------------------------------------------------------------------------*/
// Common mmap block size for ODROID-N1 GRF register
#define N1_GRF_BLOCK_SIZE		0xF000

// Common offset for GPIO registers from each GPIO bank's base address
#define N1_GPIO_CON_OFFSET		0x04		// GPIO_SWPORTA_DDR
#define N1_GPIO_SET_OFFSET		0x00		// GPIO_SWPORTA_DR
#define N1_GPIO_GET_OFFSET		0x50		// GPIO_EXT_PORTA

#define N1_FUNC_GPIO			0b00		// Bit for IOMUX GPIO mode

// GPIO{0, 1}
#define N1_PMUGRF_BASE			0xFF320000
#define N1_PMUGRF_IOMUX_OFFSET		0x0000		// GRF_GPIO0A_IOMUX
#define N1_PMUGRF_PUPD_OFFSET		0x0040		// PMUGRF_GPIO0A_P

// GPIO{2, 3, 4}
#define N1_GRF_BASE 			0xFF770000
#define N1_GRF_IOMUX_OFFSET		0xE000		// GRF_GPIO2A_IOMUX
#define N1_GRF_PUPD_OFFSET		0xE040		// GRF_GPIO2A_P

// Offset to control GPIO clock
// Make 31:16 bit HIGH to enable the writing corresponding bit
#define N1_PMUCRU_BASE			0xFF750000
#define N1_PMUCRU_GPIO_CLK_OFFSET	0x0104		// PMUCRU_CLKGATE_CON1

#define N1_CRU_BASE			0xFF760000
#define N1_CRU_GPIO_CLK_OFFSET		0x037C		// CRU_CLKGATE_CON31

#define N1_CLK_ENABLE			0b0
#define N1_CLK_DISABLE			0b1

// Only for Linux kernel for now. Edit to 0 for Android
#define N1_GPIO_PIN_BASE		1000

// GPIO1_A.	0,1,2,3,4,7
// GPIO1_B. 	0,1,2,3,4,5
// GPIO1_C.	2,4,5,6
// GPIO1_D.	0
#define N1_GPIO_1_BASE			0xFF730000

// GPIO2_C.	0_B,1_B
#define N1_GPIO_2_BASE			0xFF780000

// GPIO4_C.	5,6
// GPIO4_D.	0,4,5,6
#define N1_GPIO_4_BASE			0xFF790000

// Reserved
// GPIO{0, 3}
#define N1_GPIO_0_BASE			0xFF720000
#define N1_GPIO_3_BASE			0xFF788000

#ifdef __cplusplus
extern "C" {
#endif

extern void init_odroidn1 (struct libodroid *libwiring);

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/
#endif	/* __ODROID_N1_H__ */
/*----------------------------------------------------------------------------*/
