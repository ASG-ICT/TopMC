#ifndef _TOPMC_MOD_LIB_H
#define _TOPMC_MOD_LIB_H

#include <linux/types.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/smp.h>

#include <asm/smp.h>
#include <asm/uaccess.h>
#include <asm/special_insns.h>
#include <asm/cpufeature.h>



#define set_topmc_cnt(bitmap, k) (bitmap |= (1<<k) )
#define clr_topmc_cnt(bitmap, k) (bitmap &= (0<<k) )
#define set_topmc_cnt_all(bitmap) (bitmap |= ((1<<12) -1)) //marks 4 incore counters and 8 uncore counters which incore counters in the lower bit
#define clr_topmc_cnt_all(bitmap) (bitmap &= 0ULL)


extern unsigned int topmc_mix16to32(unsigned short high, unsigned short low);
extern void topmc_split32to16(unsigned int mix, unsigned short *high, unsigned short *low);
extern unsigned int topmc_str2int(const char *cp, unsigned int count, unsigned int base);

struct topmc_proc_entry{
	unsigned int enable;
	unsigned int event;
	unsigned long long value;
};
extern struct topmc_proc_entry topmc_procs[NR_CPUS][TOPMC_MAX_COUNTER];

#endif
