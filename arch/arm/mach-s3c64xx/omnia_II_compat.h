#define S3C_GPIO_SLP_OUT0       ((__force s3c_gpio_pull_t)0x00)
#define S3C_GPIO_SLP_OUT1       ((__force s3c_gpio_pull_t)0x01)
#define S3C_GPIO_SLP_INPUT      ((__force s3c_gpio_pull_t)0x02)
#define S3C_GPIO_SLP_PREV       ((__force s3c_gpio_pull_t)0x03)

#define s3c_uartcfg s3c2410_uartcfg
#define S3C_UCON_DEFAULT S3C2410_UCON_DEFAULT
#define S3C_LCON_CS8 S3C2410_LCON_CS8
#define S3C_LCON_PNONE S3C2410_LCON_PNONE
#define S3C_UFCON_RXTRIG8 S3C2410_UFCON_RXTRIG8
#define S3C_UFCON_FIFOMODE S3C2410_UFCON_FIFOMODE

#define set_irq_type irq_set_irq_type

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


#define S3C_VA_LCD	S3C_ADDR(0x00600000)	/* LCD */

#define S3C64XX_VA_LCD          S3C_VA_LCD
#define S3C64XX_PA_LCD	   	(0x77100000)
#define S3C64XX_SZ_LCD		SZ_1M

/* Host I/F Indirect & Direct */
#define S3C64XX_VA_HOSTIFA      S3C_ADDR(0x00B00000)                
#define S3C64XX_PA_HOSTIFA      (0x74000000) 
#define S3C64XX_SZ_HOSTIFA      SZ_1M

#define S3C64XX_VA_HOSTIFB      S3C_ADDR(0x00C00000)
#define S3C64XX_PA_HOSTIFB      (0x74100000)
#define S3C64XX_SZ_HOSTIFB      SZ_1M

/* USB OTG */
#define S3C64XX_VA_OTG          S3C_ADDR(0x03900000)
#define S3C64XX_PA_OTG          (0x7C000000)
#define S3C64XX_SZ_OTG          SZ_1M

/* USB OTG SFR */
#define S3C64XX_VA_OTGSFR       S3C_ADDR(0x03a00000)
#define S3C64XX_PA_OTGSFR       (0x7C100000)
#define S3C64XX_SZ_OTGSFR       SZ_1M              

#define S3C6410_PA_AXI_SYS        (0x7E003000)

/* Watch dog */
#define S3C64XX_PA_WATCHDOG     (0x7E004000)
#define S3C64XX_SZ_WATCHDOG     SZ_4K

#define S3C_AHB_CON0            S3C_CLKREG(0x100)


extern struct platform_device s3c_device_camif;
extern struct platform_device s3c_device_keypad;
extern struct platform_device s3c_device_vpp;
extern struct platform_device s3c_device_mfc;
extern struct platform_device s3c_device_rotator;
extern struct platform_device s3c_device_jpeg;
extern struct platform_device s3c_device_2d;
extern struct platform_device s3c_device_g3d;
extern struct platform_device ram_console_device;

#define s3c_ts_mach_info s3c2410_ts_mach_info

extern int s3c64xx_gpiolib_init(void);

#define s3c_init_clocks s3c24xx_init_clocks
#define s3c_init_uarts s3c24xx_init_uarts

#define s3c6410_pm_init s3c_pm_init

#define S3C_RTCCON S3C2410_RTCCON
#define S3C_RTCCON_RTCEN S3C2410_RTCCON
#define S3C_RTCCON_CLKSEL S3C2410_RTCCON_CLKSEL
#define S3C_RTCCON_CNTSEL S3C2410_RTCCON_CNTSEL
#define S3C_RTCCON_CLKRST S3C2410_RTCCON_CLKRST
#define S3C_RTCCON_TICEN S3C64XX_RTCCON_TICEN
#define S3C_TICNT S3C2410_TICNT

#define S3C64XX_GPIO_ALIVE_PART_BASE		S3C64XX_GPK(0)
#define S3C64XX_GPIO_MEM_PART_BASE		S3C64XX_GPO(0)

int s3c_gpio_slp_setpull_updown(unsigned int pin, unsigned int config)
{
        struct s3c_gpio_chip *chip = s3c_gpiolib_getchip(pin);
        void __iomem *reg;
        unsigned long flags;
        int offset;
        u32 con;
        int shift;

        if (!chip)
                return -EINVAL;
        if((chip->base == (S3C64XX_GPK_BASE + 0x4)) ||
                (chip->base == (S3C64XX_GPL_BASE + 0x4)) ||
                (chip->base == S3C64XX_GPM_BASE) ||
                (chip->base == S3C64XX_GPN_BASE))
        {
                return -EINVAL;
        }
        if(config > 3)
        {
                return -EINVAL;
        }
        reg = chip->base + 0x10;

        offset = pin - chip->chip.base;
        shift = offset * 2;

        local_irq_save(flags);
        
        con = __raw_readl(reg);
        con &= ~(3 << shift);
        con |= config << shift;
        __raw_writel(con, reg);

        con = __raw_readl(reg);
        
        local_irq_restore(flags);

        return 0;
}

#define S3C_EINT_MASK S3C64XX_EINT_MASK
#define S3C_PWR_CFG S3C64XX_PWR_CFG

#define S3C64XX_PA_G2D          (0x76100000)
#define S3C64XX_SZ_G2D          SZ_1M

#define S3C64XX_PA_G3D          (0x72000000)
#define S3C64XX_SZ_G3D          SZ_16M

#define S3C64XX_PA_FIMC         (0x78000000)
#define S3C64XX_SZ_FIMC         SZ_1M

/* Keypad IF  */
#define S3C64XX_PA_KEYPAD   (0x7E00A000)
#define S3C64XX_SZ_KEYPAD   SZ_4K

#define S3C64XX_PA_ROTATOR  (0x77200000)
#define S3C_SZ_ROTATOR      SZ_1M

/* JPEG */
#define S3C64XX_PA_JPEG     (0x78800000)
#define S3C_SZ_JPEG     SZ_4M

/* CAM IF */
#define S3C64XX_PA_FIMC (0x78000000)
#define S3C64XX_SZ_FIMC SZ_1M

/* VPP */
#define S3C64XX_PA_VPP      (0x77000000)
#define S3C_SZ_VPP      SZ_1M

/* MFC */
#define S3C64XX_PA_MFC      (0x7E002000)
#define S3C_SZ_MFC      SZ_4K

#define RAM_CONSOLE_SIZE        (SZ_2M)
#define RAM_CONSOLE_START       (RESERVED_PMEM_END_ADDR \
                                - RAM_CONSOLE_SIZE)

static struct resource ram_console_resource[] = {
        {
                .start  = RAM_CONSOLE_START,
                .end    = RAM_CONSOLE_START + SZ_1M - 1,
                .flags  = IORESOURCE_MEM,
        }
};

struct platform_device ram_console_device = {
        .name           = "ram_console",
        .id             = -1,
        .num_resources  = ARRAY_SIZE(ram_console_resource),
        .resource       = ram_console_resource,
};

EXPORT_SYMBOL(ram_console_device);

/* 3D interface */
static struct resource s3c_g3d_resource[] = {
        [0] = {
                .start = S3C64XX_PA_G3D,
                .end   = S3C64XX_PA_G3D + S3C64XX_SZ_G3D - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_S3C6410_G3D,
                .end   = IRQ_S3C6410_G3D,
                .flags = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_g3d = {
        .name             = "s3c-g3d",
        .id               = -1,
        .num_resources    = ARRAY_SIZE(s3c_g3d_resource),
        .resource         = s3c_g3d_resource
};

EXPORT_SYMBOL(s3c_device_g3d);

/* 2D interface */
static struct resource s3c_2d_resource[] = {
        [0] = {
                .start = S3C64XX_PA_G2D,
                .end   = S3C64XX_PA_G2D + S3C64XX_SZ_G2D - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_2D,
                .end   = IRQ_2D,
                .flags = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_2d = {
        .name             = "s3c-g2d",
        .id               = -1,
        .num_resources    = ARRAY_SIZE(s3c_2d_resource),
        .resource         = s3c_2d_resource
};

EXPORT_SYMBOL(s3c_device_2d);

/* rotator interface */
static struct resource s3c_rotator_resource[] = {
        [0] = {
                .start = S3C64XX_PA_ROTATOR,
                .end   = S3C64XX_PA_ROTATOR + S3C_SZ_ROTATOR - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_ROTATOR,
                .end   = IRQ_ROTATOR,
                .flags = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_rotator = {
        .name             = "s3c-rotator",
        .id               = -1,
        .num_resources    = ARRAY_SIZE(s3c_rotator_resource),
        .resource         = s3c_rotator_resource
};

EXPORT_SYMBOL(s3c_device_rotator);

/* LCD Controller */

static struct resource s3c_lcd_resource[] = {
        [0] = {
                .start = S3C64XX_PA_LCD,
                .end   = S3C64XX_PA_LCD + SZ_1M - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_LCD_VSYNC,
                .end   = IRQ_LCD_SYSTEM,
                .flags = IORESOURCE_IRQ,
        }
};

static u64 s3c_device_lcd_dmamask = 0xffffffffUL;

struct platform_device s3c_device_lcd = {
        .name             = "s3c-lcd",
        .id               = -1,
        .num_resources    = ARRAY_SIZE(s3c_lcd_resource),
        .resource         = s3c_lcd_resource,
        .dev              = {
                .dma_mask               = &s3c_device_lcd_dmamask,
                .coherent_dma_mask      = 0xffffffffUL
        }
};


/* Camif controller */
static struct resource s3c_camif_resource[] = {
        [0] = {
                .start = S3C64XX_PA_FIMC,
                .end   = S3C64XX_PA_FIMC + S3C64XX_SZ_FIMC - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_CAMIF_C,
                .end   = IRQ_CAMIF_C,
                .flags = IORESOURCE_IRQ,
        },
        [2] = {
                .start = IRQ_CAMIF_P,
                .end   = IRQ_CAMIF_P,
                .flags = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_camif = {
        .name           = "s3c-camif",
        .id             = -1,
        .num_resources  = ARRAY_SIZE(s3c_camif_resource),
        .resource       = s3c_camif_resource,
};

EXPORT_SYMBOL(s3c_device_camif);

/* Keypad interface */
static struct resource s3c_keypad_resource[] = {
        [0] = {
                .start = S3C64XX_PA_KEYPAD,
                .end   = S3C64XX_PA_KEYPAD+ S3C64XX_SZ_KEYPAD - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_KEYPAD,
                .end   = IRQ_KEYPAD,
                .flags = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_keypad = {
        .name           = "s3c-keypad",
        .id             = -1,
        .num_resources  = ARRAY_SIZE(s3c_keypad_resource),
        .resource       = s3c_keypad_resource,
};
EXPORT_SYMBOL(s3c_device_keypad);

/* JPEG controller */
static struct resource s3c_jpeg_resource[] = {
        [0] = {
                .start = S3C64XX_PA_JPEG,
                .end   = S3C64XX_PA_JPEG + S3C_SZ_JPEG - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_JPEG,
                .end   = IRQ_JPEG,
                .flags = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_jpeg = {
        .name           = "s3c-jpeg",
        .id             = -1,
        .num_resources  = ARRAY_SIZE(s3c_jpeg_resource),
        .resource       = s3c_jpeg_resource,
};

EXPORT_SYMBOL(s3c_device_jpeg);

/* MFC controller */
static struct resource s3c_mfc_resource[] = {
        [0] = {
                .start = S3C64XX_PA_MFC,
                .end   = S3C64XX_PA_MFC + SZ_4K - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_MFC,
                .end   = IRQ_MFC,
                .flags = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_mfc = {
        .name             = "s3c-mfc",
        .id               = -1,
        .num_resources    = ARRAY_SIZE(s3c_mfc_resource),
        .resource         = s3c_mfc_resource
};

EXPORT_SYMBOL(s3c_device_mfc);
/* VPP controller */
static struct resource s3c_vpp_resource[] = {
        [0] = {
                .start = S3C64XX_PA_VPP,
                .end   = S3C64XX_PA_VPP + S3C_SZ_VPP - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_POST0,
                .end   = IRQ_POST0,
                .flags = IORESOURCE_IRQ,
        }
};

struct platform_device s3c_device_vpp = {
        .name           = "s3c-vpp",
        .id             = -1,
        .num_resources  = ARRAY_SIZE(s3c_vpp_resource),
        .resource       = s3c_vpp_resource,
};

EXPORT_SYMBOL(s3c_device_vpp);


static struct android_pmem_platform_data pmem_pdata = {
        .name           = "pmem",
	.allocator_type = PMEM_ALLOCATORTYPE_ALLORNOTHING,
        .cached         = 1,
        .buffered       = 1,    //09.12.01 hoony: surfaceflinger optimize
};
 
static struct android_pmem_platform_data pmem_render_pdata = {
        .name           = "pmem_render",
	.allocator_type = PMEM_ALLOCATORTYPE_ALLORNOTHING,
        .cached         = 0,
};

static struct android_pmem_platform_data pmem_stream_pdata = {
        .name           = "pmem_stream",
	.allocator_type = PMEM_ALLOCATORTYPE_ALLORNOTHING,
        .cached         = 0,
};

static struct android_pmem_platform_data pmem_stream2_pdata = {
        .name           = "pmem_stream2",
	.allocator_type = PMEM_ALLOCATORTYPE_ALLORNOTHING,
        .cached         = 0,
};

static struct android_pmem_platform_data pmem_preview_pdata = {
        .name           = "pmem_preview",
	.allocator_type = PMEM_ALLOCATORTYPE_ALLORNOTHING,
        .cached         = 0,
};

static struct android_pmem_platform_data pmem_picture_pdata = {
        .name           = "pmem_picture",
	.allocator_type = PMEM_ALLOCATORTYPE_ALLORNOTHING,
        .cached         = 0,
};

static struct android_pmem_platform_data pmem_jpeg_pdata = {
        .name           = "pmem_jpeg",
	.allocator_type = PMEM_ALLOCATORTYPE_ALLORNOTHING,
        .cached         = 0,
};

static struct platform_device pmem_device = {
        .name           = "android_pmem",
        .id             = 0,
        .dev            = { .platform_data = &pmem_pdata },
};
 
static struct platform_device pmem_render_device = {
        .name           = "android_pmem",
        .id             = 1,
        .dev            = { .platform_data = &pmem_render_pdata },
};

static struct platform_device pmem_stream_device = {
        .name           = "android_pmem",
        .id             = 2,
        .dev            = { .platform_data = &pmem_stream_pdata },
};

static struct platform_device pmem_stream2_device = {
        .name           = "android_pmem",
        .id             = 3,
        .dev            = { .platform_data = &pmem_stream2_pdata },
};

static struct platform_device pmem_preview_device = {
        .name           = "android_pmem",
        .id             = 4,
        .dev            = { .platform_data = &pmem_preview_pdata },
};

static struct platform_device pmem_picture_device = {
        .name           = "android_pmem",
        .id             = 5,
        .dev            = { .platform_data = &pmem_picture_pdata },
};

static struct platform_device pmem_jpeg_device = {
        .name           = "android_pmem",
        .id             = 6,
        .dev            = { .platform_data = &pmem_jpeg_pdata },
};

void __init s3c6410_add_mem_devices(struct s3c6410_pmem_setting *setting)
{
        if (setting->pmem_size) {
//                pmem_pdata.start = setting->pmem_start;
                pmem_pdata.size = setting->pmem_size;
                platform_device_register(&pmem_device);
        }

        if (setting->pmem_render_size) {
//                pmem_render_pdata.start = setting->pmem_render_start;
                pmem_render_pdata.size = setting->pmem_render_size;
                platform_device_register(&pmem_render_device);
        }

        if (setting->pmem_stream_size) {
//                pmem_stream_pdata.start = setting->pmem_stream_start;
                pmem_stream_pdata.size = setting->pmem_stream_size;
                platform_device_register(&pmem_stream_device);
        }

        if (setting->pmem_stream_size) {
//                pmem_stream2_pdata.start = setting->pmem_stream_start;
                pmem_stream2_pdata.size = setting->pmem_stream_size;
                platform_device_register(&pmem_stream2_device);
        }

        if (setting->pmem_preview_size) {
//                pmem_preview_pdata.start = setting->pmem_preview_start;
                pmem_preview_pdata.size = setting->pmem_preview_size;
                platform_device_register(&pmem_preview_device);
        }

        if (setting->pmem_picture_size) {
//                pmem_picture_pdata.start = setting->pmem_picture_start;
                pmem_picture_pdata.size = setting->pmem_picture_size;
                platform_device_register(&pmem_picture_device);
        }

        if (setting->pmem_jpeg_size) {
//                pmem_jpeg_pdata.start = setting->pmem_jpeg_start;
                pmem_jpeg_pdata.size = setting->pmem_jpeg_size;
                platform_device_register(&pmem_jpeg_device);
        }
}


