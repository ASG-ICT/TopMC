#include "topmc_x86_model.h"
#include "topmc_mod_lib.h"

#include "topmc_pmc_config_amd.h"
#include "topmc_msr.h"



extern struct topmc_proc_entry topmc_procs[NR_CPUS][TOPMC_MAX_COUNTER];

// -----------------------------------------------------------------
int topmc_enable_read_amd(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    unsigned int mix = *(unsigned int *)data;
    unsigned short cpu, counter;

    topmc_split32to16(mix, &cpu, &counter);
    count = sprintf(page, "%u\n", topmc_procs[cpu][counter].enable);

    printk("enable read ==> cpu %d, counter %d : %u\n", cpu, counter, topmc_procs[cpu][counter].enable);

    return count;
} 

int topmc_enable_write_amd(struct file *file, const char __user *buffer, unsigned long count, void *data)
{
    unsigned int mix = *(unsigned int *)data;
    unsigned short cpu, counter;

    char enable;
    u64 val = 0;

    topmc_split32to16(mix, &cpu, &counter);

    printk("enable write before ==> cpu %d, counter %d : %u\n", cpu, counter, topmc_procs[cpu][counter].enable);

    get_user(enable, buffer);

    RDMSR(EVNT_SEL0+counter, val, cpu);
    if(enable == '1') {
        topmc_procs[cpu][counter].enable = 1;
        SET_ENABLE(val);
    } else {
        topmc_procs[cpu][counter].enable = 0;
        SET_DISABLE(val);
    }
    WRMSR(EVNT_SEL0+counter, val, cpu);

    printk("enable write after  ==> cpu %d, counter %d : %u\n", cpu, counter, topmc_procs[cpu][counter].enable);
    return count;
}

// -----------------------------------------------------------------
int topmc_event_read_amd(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    unsigned int mix = *(unsigned int *)data;
    unsigned short cpu, counter;

    topmc_split32to16(mix, &cpu, &counter);
    count = sprintf(page, "0x%08x\n", topmc_procs[cpu][counter].event);
    printk("event read ==> cpu %d, counter %d : 0x%06x\n", cpu, counter, topmc_procs[cpu][counter].event);

    return count;
}

// -----------------------------------------------------------------
/*
 * counter event format:'***--#'
 * '***' stands for event
 * '--' stands for unit mask
 * '#' stands for usr/kernel:0-nothing,1-user,2-kernel,3-user and kernel
 * Example: '041ff1'
 */
int topmc_event_write_amd(struct file *file, const char __user *buffer, unsigned long count, void *data)
{
	unsigned int mix = *(unsigned int *)data;
	unsigned short cpu, counter;
	long ret;

	char str[6];
	int event;
	int kernel = 0, user = 0;
	u64 val = 0;                

	topmc_split32to16(mix, &cpu, &counter);
	printk("event write (before) ==> cpu %d, counter %d : 0x%06x\n", cpu, counter, topmc_procs[cpu][counter].event);

	//copy_from_user(str, buffer, count);
	ret = strncpy_from_user(str, buffer, count);
	if(ret <0) 
		return -EFAULT;
	if(ret ==0 || ret > count)
		return -EINVAL;

	event = topmc_str2int(str, 6, 16);
	topmc_procs[cpu][counter].event = event;

	switch(event & 0x00000f) {
		case 0: 
			kernel = 0; user = 0; break;
		case 1: 
			kernel = 0; user = 1; break;
		case 2: 
			kernel = 1; user = 0; break;
		case 3: 
			kernel = 1; user = 1; break;
		default: 
			printk("+->topmc_enable_write(): kernel_user error!\n"); break;
	}
	RDMSR(EVNT_SEL0+counter, val, cpu);
	val &=  EVNT_SEL_RESERVED;
	SET_USR(val, user);
	SET_KERN(val, kernel);
	SET_UNIT_MASK(val, event);
	SET_EVENT_SELECT(val, event);
	WRMSR(EVNT_SEL0+counter, val, cpu);

	WRMSR(PMC0+counter, 0LL, cpu);
	printk("event write (after)  ==> cpu %d, counter %d : 0x%06x\n", cpu, counter, topmc_procs[cpu][counter].event);

	return count;
} 

// -----------------------------------------------------------------
int topmc_value_read_amd(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    unsigned int mix = *(unsigned int *)data;
    unsigned short cpu, counter;

    u64 val;

    topmc_split32to16(mix, &cpu, &counter);

    if(topmc_procs[cpu][counter].enable == 1) {
        RDMSR(PMC0 + counter, val, cpu);
        count = sprintf(page, "%llu\n", val);
    } else {  
        count = sprintf(page, "%llu\n", 0LLU);
    }

    return count;
}       

int topmc_value_write_amd(struct file *file, const char __user *buffer, unsigned long count, void *data)
{
	unsigned int mix = *(unsigned int *)data;
	unsigned short cpu, counter;
	long ret;

	char str[20];
	u64 val;

	topmc_split32to16(mix, &cpu, &counter);

	//    copy_from_user(str, buffer, count);
	ret = strncpy_from_user(str, buffer, count);
	if(ret < 0)
		return -EFAULT;
	if(ret == 0 || ret > count)
		return -EINVAL;
	val = topmc_str2int(str, 6, 20);
	if(topmc_procs[cpu][counter].enable == 0) {
		WRMSR(PMC0 + counter, val, cpu);
	}

	return 0;
}
// ---------------------------------------------------------------- 
void topmc_msr_init_amd(void)
{
    unsigned short cpu, counter;
    u64 val;

    for_each_online_cpu(cpu) { 
        /* in core section */
        for (counter = 0 ; counter < PMC_NUM; ++counter) {
            //clear the event selectors
            RDMSR(EVNT_SEL0+counter, val, cpu);
            val &=  EVNT_SEL_RESERVED;
            WRMSR(EVNT_SEL0+counter, val, cpu);

            // clear the counter
            WRMSR(PMC0+counter, 0LL, cpu);
        } 
    }       
}               


struct topmc_x86_model topmc_op_amd = {
	.num_counters_core = PMC_NUM,
	.num_counters_uncore = 0,
	.is_exist_topmc_core_global_ctrl_init = 0,
	.is_exist_topmc_uncore_global_ctrl_init = 0,
	.topmc_msr_init = &topmc_msr_init_amd,
	.topmc_core_global_ctrl_init = NULL,
	.topmc_uncore_global_ctrl_init = NULL,
	.topmc_enable_all_read = NULL,
	.topmc_enable_all_write = NULL,
	.topmc_enable_read = &topmc_enable_read_amd,
	.topmc_enable_write = &topmc_enable_write_amd,
	.topmc_event_read = &topmc_event_read_amd,
	.topmc_event_write = &topmc_event_write_amd,
	#ifdef TOPMC_PER_SECOND
	.topmc_value_read_callable_impl = NULL,
	#endif
	.topmc_value_read = &topmc_value_read_amd,
	.topmc_value_write = &topmc_value_write_amd
};

