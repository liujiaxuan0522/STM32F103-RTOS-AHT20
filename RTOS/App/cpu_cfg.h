#ifndef CPU_CFG_MODULE_PRESENT
#define CPU_CFG_MODULE_PRESENT

/* CPU host name feature: not used. */
#define CPU_CFG_NAME_EN                 DEF_DISABLED
#define CPU_CFG_NAME_SIZE               16

/* CPU timestamps: not used. */
#define CPU_CFG_TS_32_EN                DEF_DISABLED
#define CPU_CFG_TS_64_EN                DEF_DISABLED
#define CPU_CFG_TS_TMR_SIZE             CPU_WORD_SIZE_32

/* Interrupt-disable time measurement: disabled (do not define the EN macro). */
#define CPU_CFG_INT_DIS_MEAS_OVRHD_NBR  1u

/* CPU count-leading-zeros assembly option is defined by cpu.h. */

/* No data cache on STM32F103. */
#define CPU_CFG_CACHE_MGMT_EN           DEF_DISABLED

/* Kernel-aware interrupt priority boundary.
   With 4 priority bits: external priorities 4..15 are kernel-aware,
   0..3 must not call RTOS APIs. */
#define CPU_CFG_KA_IPL_BOUNDARY         4u

/* STM32F103 implements 4 NVIC priority bits. */
#define CPU_CFG_NVIC_PRIO_BITS          4u

#endif
