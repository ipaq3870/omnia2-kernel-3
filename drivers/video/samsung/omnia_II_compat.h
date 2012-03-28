#define S3C_VA_LCD	S3C_ADDR(0x00600000)	/* LCD */
#define S3C64XX_VA_HOSTIFB	S3C_ADDR(0x00C00000)

#define S3C64XX_SPC_BASE	(S3C64XX_VA_GPIO + 0x01A0)
#define S3C64XX_GPICON			(S3C64XX_GPI_BASE + 0x00)
#define S3C64XX_GPIDAT			(S3C64XX_GPI_BASE + 0x04)
#define S3C64XX_GPIPUD			(S3C64XX_GPI_BASE + 0x08)
#define S3C64XX_GPJCON			(S3C64XX_GPJ_BASE + 0x00)
#define S3C64XX_GPJDAT			(S3C64XX_GPJ_BASE + 0x04)
#define S3C64XX_GPJPUD			(S3C64XX_GPJ_BASE + 0x08)

#define s3c6410_pm_do_save s3c_pm_do_save
#define s3c6410_pm_do_restore s3c_pm_do_restore

#define S3C_GPIO_LAVEL(x)       ((x >= S3C64XX_GPIO_Q_START) ? "GPQ" : \
                                                                ((x >= S3C64XX_GPIO_P_START) ? "GPP" : \
                                                                ((x >= S3C64XX_GPIO_O_START) ? "GPO" : \
                                                                ((x >= S3C64XX_GPIO_N_START) ? "GPN" : \
                                                                ((x >= S3C64XX_GPIO_M_START) ? "GPM" : \
                                                                ((x >= S3C64XX_GPIO_L_START) ? "GPL" : \
                                                                ((x >= S3C64XX_GPIO_K_START) ? "GPK" : \
                                                                ((x >= S3C64XX_GPIO_J_START) ? "GPJ" : \
                                                                ((x >= S3C64XX_GPIO_I_START) ? "GPI" : \
                                                                ((x >= S3C64XX_GPIO_H_START) ? "GPH" : \
                                                                ((x >= S3C64XX_GPIO_G_START) ? "GPG" : \
                                                                ((x >= S3C64XX_GPIO_F_START) ? "GPF" : \
                                                                ((x >= S3C64XX_GPIO_E_START) ? "GPE" : \
                                                                ((x >= S3C64XX_GPIO_D_START) ? "GPD" : \
                                                                ((x >= S3C64XX_GPIO_C_START) ? "GPC" : \
                                                                ((x >= S3C64XX_GPIO_B_START) ? "GPB" : \
                                                                ((x >= S3C64XX_GPIO_A_START) ? "GPA" : NULL))))))))))))))))) \




