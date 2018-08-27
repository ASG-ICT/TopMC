#define TOPMC_PERF_PMC_MASK 0LL
//#define TOPMC_PERF_PMC_MASK   0xffff800000000000
/* incore msrs*/

/* Intel Core-based CPU performance counters */
#define MSR_CORE_PERF_FIXED_CTR0        0x00000309
#define MSR_CORE_PERF_FIXED_CTR1        0x0000030a
#define MSR_CORE_PERF_FIXED_CTR2        0x0000030b
#define MSR_CORE_PERF_FIXED_CTR_CTRL    0x0000038d
#define MSR_CORE_PERF_GLOBAL_STATUS     0x0000038e
#define MSR_CORE_PERF_GLOBAL_CTRL       0x0000038f
#define MSR_CORE_PERF_GLOBAL_OVF_CTRL   0x00000390

#define MSR_CORE_PERF_NUM_PMC 4
#define MSR_CORE_PERF_IDX_PMC 0
#define MSR_CORE_PERF_IDX_FIX 32
#define MSR_CORE_PERF_NUM_FIX 3

#define TOPMC_MSR_XEON55XX_PERFCTR0                     0x000000c1
#define TOPMC_MSR_XEON55XX_PERFCTR1                     0x000000c2
#define TOPMC_MSR_XEON55XX_PERFCTR2                     0x000000c3
#define TOPMC_MSR_XEON55XX_PERFCTR3                     0x000000c4
#define TOPMC_MSR_XEON55XX_EVNTSEL0                     0x00000186
#define TOPMC_MSR_XEON55XX_EVNTSEL1                     0x00000187
#define TOPMC_MSR_XEON55XX_EVNTSEL2                     0x00000188
#define TOPMC_MSR_XEON55XX_EVNTSEL3                     0x00000189

#define TOPMC_MSR_XEON55XX_PerfCtrNum   (TOPMC_MSR_XEON55XX_PERFCTR3-TOPMC_MSR_XEON55XX_PERFCTR0 +1)
#define TOPMC_MAX_NAMELEN       16

//#counter event format:'**--xyz#'
//#'**' stands for event
//#'--' stands for unit mask
//#'x' stands for cmask (only 4-bit value)
//#'y' stands for inv 
//#'z' stands for edge
//#'#' stands for usr/kernel:0-nothing,1-user,2-kernel,3-user and kernel

/*
#define TOPMC_EVENT_LENGTH      6
#define TOPMC_EVENT_MASK_KERNEL_USER    0xf
#define TOPMC_EVENT_MASK_UNIT                   0xff0
#define TOPMC_EVENT_MASK_LOW_EVENT              0xff000
#define TOPMC_EVENT_MASK_HIGH_EVENT             0xf00000
#define TOPMC_EVENT_BITS_KERNEL_USER    0
#define TOPMC_EVENT_BITS_UNIT                   4
#define TOPMC_EVENT_BITS_LOW_EVENT              12
#define TOPMC_EVENT_BITS_HIGH_EVENT             20
*/
#define TOPMC_EVENT_LENGTH      8
#define TOPMC_EVENT_MASK_LOW_EVENT      0xff000000
#define TOPMC_EVENT_MASK_UNIT           0xff0000
#define TOPMC_EVENT_MASK_CMASK          0xf000
#define TOPMC_EVENT_MASK_INV            0x100
#define TOPMC_EVENT_MASK_EDGE           0x10
#define TOPMC_EVENT_MASK_KERNEL_USER    0xf
//#define TOPMC_EVENT_MASK_HIGH_EVENT             0xf00000
#define TOPMC_EVENT_BITS_LOW_EVENT              24
#define TOPMC_EVENT_BITS_UNIT                   16
#define TOPMC_EVENT_BITS_CMASK              12
#define TOPMC_EVENT_BITS_INV                8
#define TOPMC_EVENT_BITS_EDGE               4
#define TOPMC_EVENT_BITS_KERNEL_USER    0
//#define TOPMC_EVENT_BITS_HIGH_EVENT             20

#define MSR_PPRO_EVENTSEL_RESERVED      ((0xFFFFFFFFULL<<32)|(1ULL<<21))

/*offcore msrs */
#define TOPMC_MSR_XEON55XX_OFFCORE_RSP0    0x1a6

/*uncore msrs*/
#define TOPMC_MSR_XEON55XX_UNC_EVNTSEL0    0x3c0
#define TOPMC_MSR_XEON55XX_UNC_PERFCTR0    0x3b0
#define TOPMC_MSR_XEON55XX_UNC_FIXED_CTRL  0x395
#define TOPMC_MSR_XEON55XX_UNC_FIXED_CTR0  0x394
#define TOPMC_MSR_XEON55XX_UNC_ADDROP      0x396
#define TOPMC_MSR_XEON55XX_UNC_GLOBAL_CTRL 0x391
#define TOPMC_MSR_XEON55XX_UNC_GLOBAL_STAT 0x392
#define TOPMC_MSR_XEON55XX_UNC_GLOBAL_OVF_CTRL 0x393

#define TOPMC_MSR_XEON55XX_UNC_PerfCtrNum 8

#define TOPMC_MSR_XEON55XX_UNC_IDX_FIXED 32
#define TOPMC_MSR_XEON55XX_UNC_BITS_MAX_PMC 7
#define TOPMC_MSR_XEON55XX_UNC_BITS_MIN_PMC 0
#define TOPMC_MSR_XEON55XX_UNC_IDX_PMC TOPMC_MSR_XEON55XX_UNC_BITS_MIN_PMC
#define TOPMC_MSR_XEON55XX_UNC_BITS_NUM_PMC (TOPMC_MSR_XEON55XX_UNC_BITS_MAX_PMC - TOPMC_MSR_XEON55XX_UNC_BITS_MIN_PMC + 1)

#define TOPMC_MSR_XEON55XX_UNC_EVENTSEL_RESERVED ((0xFFFFFFFFULL << 32) | (1ULL << 21) | (1ULL << 19) | (1ULL << 16))


#define TOPMC_CTRL_SET_ACTIVE(n) (n |= (1<<22))
#define TOPMC_CTRL_SET_INACTIVE(n) (n &= ~(1<<22))
#define TOPMC_CTRL_CLEAR_LO(x) (x &= (1<<21))
#define TOPMC_CTRL_CLEAR_HI(x) (x &= 0xfffffcf0)
#define TOPMC_CTRL_SET_ENABLE(val) (val |= 1<<20)
#define TOPMC_CTRL_SET_USR(val,u) (val |= ((u & 1) << 16))
#define TOPMC_CTRL_SET_KERN(val,k) (val |= ((k & 1) << 17))
#define TOPMC_CTRL_SET_UM(val, m) (val |= (m << 8))
#define TOPMC_CTRL_SET_EVENT_LOW(val, e) (val |= (e & 0xff))
#define TOPMC_CTRL_SET_CM(val, m) (val |= (m&0xff << 24))
#define TOPMC_CTRL_SET_INV(val, m) (val |= ((m&0x1) << 23))
#define TOPMC_CTRL_SET_EDGE(val, m) (val |= ((m&0x1) << 18))
