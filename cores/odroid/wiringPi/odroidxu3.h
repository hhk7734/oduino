/*----------------------------------------------------------------------------*/
/*

	WiringPi ODROID-XU3/XU4 Board Header file

 */
/*----------------------------------------------------------------------------*/
#ifndef	__ODROID_XU3_H__
#define	__ODROID_XU3_H__

/*----------------------------------------------------------------------------*/
#define XU3_GPIO_MASK	(0xFFFFFF00)

#define XU3_GPIO_PIN_BASE		0

// GPX0,1,2,3
#define XU3_GPX_BASE		0x13400000

#define XU3_GPIO_X1_START	16
#define XU3_GPIO_X1_CON_OFFSET	0x0C20
#define XU3_GPIO_X1_DAT_OFFSET	0x0C24
#define XU3_GPIO_X1_PUD_OFFSET	0x0C28
#define XU3_GPIO_X1_DRV_OFFSET	0x0C2C
#define XU3_GPIO_X1_END		23

#define XU3_GPIO_X2_START	24
#define XU3_GPIO_X2_CON_OFFSET	0x0C40
#define XU3_GPIO_X2_DAT_OFFSET	0x0C44
#define XU3_GPIO_X2_PUD_OFFSET	0x0C48
#define XU3_GPIO_X2_DRV_OFFSET	0x0C4C
#define XU3_GPIO_X2_END		31

#define XU3_GPIO_X3_START	32
#define XU3_GPIO_X3_CON_OFFSET	0x0C60
#define XU3_GPIO_X3_DAT_OFFSET	0x0C64
#define XU3_GPIO_X3_PUD_OFFSET	0x0C68
#define XU3_GPIO_X3_DRV_OFFSET	0x0C6C
#define XU3_GPIO_X3_END		39

// GPA0,1,2, GPB0,1,2,3,4
#define XU3_GPA_BASE	0x14010000

#define XU3_GPIO_A0_START	171
#define XU3_GPIO_A0_CON_OFFSET	0x0000
#define XU3_GPIO_A0_DAT_OFFSET	0x0004
#define XU3_GPIO_A0_PUD_OFFSET	0x0008
#define XU3_GPIO_A0_DRV_OFFSET	0x000C
#define XU3_GPIO_A0_END		178

#define XU3_GPIO_A2_START	185
#define XU3_GPIO_A2_CON_OFFSET	0x0040
#define XU3_GPIO_A2_DAT_OFFSET	0x0044
#define XU3_GPIO_A2_PUD_OFFSET	0x0048
#define XU3_GPIO_A2_DRV_OFFSET	0x004C
#define XU3_GPIO_A2_END		192

#define XU3_GPIO_B3_START	207
#define XU3_GPIO_B3_CON_OFFSET	0x00C0
#define XU3_GPIO_B3_DAT_OFFSET	0x00C4
#define XU3_GPIO_B3_PUD_OFFSET	0x00C8
#define XU3_GPIO_B3_DRV_OFFSET	0x00CC
#define XU3_GPIO_B3_END		214

#ifdef __cplusplus
extern "C" {
#endif

extern void init_odroidxu3 (struct libodroid *libwiring);

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------*/
#endif	/* __ODROID_XU3_H__ */
/*----------------------------------------------------------------------------*/
