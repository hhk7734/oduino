/*----------------------------------------------------------------------------*/
/*

	WiringPi ODROID-C0/C1/C1+ Board Header file

 */
/*----------------------------------------------------------------------------*/
#ifndef	__ODROID_C1_H__
#define	__ODROID_C1_H__

/*----------------------------------------------------------------------------*/
#define C1_GPIO_MASK			(0xFFFFFF80)
#define C1_GPIO_BASE			0xC1108000

#define C1_GPIO_PIN_BASE		0

#define C1_GPIODV_PIN_START		50
#define C1_GPIODV_PIN_END		79
#define C1_GPIOY_PIN_START		80
#define C1_GPIOY_PIN_END		96
#define C1_GPIOX_PIN_START		97
#define C1_GPIOX_PIN_END		118

#define C1_GPIOX_FSEL_REG_OFFSET	0x0C
#define C1_GPIOX_OUTP_REG_OFFSET	0x0D
#define C1_GPIOX_INP_REG_OFFSET		0x0E
#define C1_GPIOX_PUPD_REG_OFFSET	0x3E
#define C1_GPIOX_PUEN_REG_OFFSET	0x4C

#define C1_GPIOY_FSEL_REG_OFFSET	0x0F
#define C1_GPIOY_OUTP_REG_OFFSET	0x10
#define C1_GPIOY_INP_REG_OFFSET		0x11
#define C1_GPIOY_PUPD_REG_OFFSET	0x3D
#define C1_GPIOY_PUEN_REG_OFFSET	0x4B

#define C1_GPIODV_FSEL_REG_OFFSET	0x12
#define C1_GPIODV_OUTP_REG_OFFSET	0x13
#define C1_GPIODV_INP_REG_OFFSET	0x14
#define C1_GPIODV_PUPD_REG_OFFSET	0x3A
#define C1_GPIODV_PUEN_REG_OFFSET	0x48

#define	C1_MUX_REG_1_OFFSET		0x2D
#define	C1_MUX_REG_2_OFFSET		0x2E
#define	C1_MUX_REG_3_OFFSET		0x2F
#define	C1_MUX_REG_4_OFFSET		0x30
#define	C1_MUX_REG_5_OFFSET		0x31
#define	C1_MUX_REG_6_OFFSET		0x32
#define	C1_MUX_REG_7_OFFSET		0x33
#define	C1_MUX_REG_8_OFFSET		0x34
#define	C1_MUX_REG_9_OFFSET		0x35

#ifdef __cplusplus
extern "C" {
#endif

extern void init_odroidc1 (struct libodroid *libwiring);

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/
#endif	/* __ODROID_C1_H__ */
/*----------------------------------------------------------------------------*/
