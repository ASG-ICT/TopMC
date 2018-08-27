#ifndef TOPMC_X86_MODEL_H
#define TOPMC_X86_MODEL_H


#include <linux/types.h>
#include <linux/fs.h>

//#define TOPMC_PER_SECOND
#define TOPMC_MAX_COUNTER 32

struct topmc_x86_model {
	void (*topmc_msr_init)(void);
	char is_exist_topmc_core_global_ctrl_init;
	void (*topmc_core_global_ctrl_init)(void);
	char is_exist_topmc_uncore_global_ctrl_init;
	void (*topmc_uncore_global_ctrl_init)(void);
	int num_counters_core;
	int num_counters_uncore;
#if 0
	int (*topmc_enable_all_read)(char *page, char **start, off_t off, int count, int *eof, void *data);
	int (*topmc_enable_all_write)(struct file *file, const char __user *buffer, unsigned long count, void *data);
	int (*topmc_enable_read)(char *page, char **start, off_t off, int count, int *eof, void *data);
	int (*topmc_enable_write)(struct file *file, const char __user *buffer, unsigned long count, void *data);
	int (*topmc_event_read)(char *page, char **start, off_t off, int count, int *eof, void *data);
	int (*topmc_event_write)(struct file *file, const char __user *buffer, unsigned long count, void *data);
//	#define TOPMC_PER_SECOND
	#ifdef TOPMC_PER_SECOND
	u64 (*topmc_value_read_callable_impl)(unsigned short cpu, unsigned short counter);
	#endif
	int (*topmc_value_read)(char *page, char **start, off_t off, int count, int *eof, void *data);
	int (*topmc_value_write)(struct file *file, const char __user *buffer, unsigned long count, void *data);
#endif
	int (*topmc_enable_all_read)(struct file *filp,char *buffer,size_t count,loff_t *offp );
	int (*topmc_enable_all_write)(struct file *filp,const char *buffer,size_t count,loff_t *offp );
	int (*topmc_enable_read)(struct file *filp,char *buffer,size_t count,loff_t *offp );
	int (*topmc_enable_write)(struct file *filp,const char *buffer,size_t count,loff_t *offp ) ;
	int (*topmc_event_read)(struct file *filp,char *buffer,size_t count,loff_t *offp );
	int (*topmc_event_write)(struct file *filp,const char *buffer,size_t count,loff_t *offp ) ;
//	#define TOPMC_PER_SECOND
	#ifdef TOPMC_PER_SECOND
	u64 (*topmc_value_read_callable_impl)(unsigned short cpu, unsigned short counter);
	#endif
	int (*topmc_value_read)(struct file *filp,char *buffer,size_t count,loff_t *offp );
	int (*topmc_value_write)(struct file *filp,const char *buffer,size_t count,loff_t *offp ) ;
};

extern struct topmc_x86_model topmc_op_amd;
extern struct topmc_x86_model topmc_op_intel_nehelam;
extern struct topmc_x86_model topmc_op_intel_ivybridge_e;
extern struct topmc_x86_model topmc_op_intel_skylake_sp;
extern struct topmc_x86_model topmc_op_intel_broadwell;



#endif
