/*
 *  linux/init/main.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  GK 2/5/95  -  Changed to support mounting root fs via NFS
 *  Added initrd & change_root: Werner Almesberger & Hans Lermen, Feb '96
 *  Moan early if gcc is old, avoiding bogus kernels - Paul Gortmaker, May '96
 *  Simplified starting of init:  Michael A. Griffith <grif@acm.org> 
 */



#include "topmc_x86_model.h"
#include "topmc_mod_lib.h"
#include "topmc_msr.h"
#include "topmc_pmc_config_intel_nehelam.h"




//#define TOPMC_PER_SECOND
#ifdef TOPMC_PER_SECOND
static unsigned long topmc_pmc_cnt_flags;
static unsigned long topmc_pmc_chg_flags;

extern spinlock_t topmc_bitmap_lock;
extern spinlock_t topmc_chg_lock;
extern unsigned short topmc_pmc_cnt_bitmap;
extern unsigned int topmc_pmc_chg;

#endif

/*
EXPORT_SYMBOL(topmc_bitmap_lock);
EXPORT_SYMBOL(topmc_chg_lock);
EXPORT_SYMBOL(topmc_pmc_cnt_bitmap);
EXPORT_SYMBOL(topmc_pmc_chg);
*/

extern struct topmc_proc_entry topmc_procs[NR_CPUS][TOPMC_MAX_COUNTER];

static int topmc_all_enabled = 0;

int topmc_enable_all_read_nehelam(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	unsigned int mix        = *(unsigned int *)data;
	unsigned short cpu,counter;

	topmc_split32to16(mix,&cpu,&counter);

	*page   = topmc_all_enabled==1?'1':'0';
	*(page+1) = '\n';
	return 2; //len of read
}

int topmc_enable_all_write_nehelam(struct file *file, const char __user * buffer, unsigned long count, void * data)
{
	char enable;
	int cpu, counter;
	//      unsigned short cpu,counter;
	//unsigned int low=0,high=0;
	int kernel=0,user=0,event;
	unsigned long long value;
	u64 val;

	get_user(enable,buffer);
	for_each_online_cpu(cpu){
		for(counter=0;counter < TOPMC_MSR_XEON55XX_PerfCtrNum;counter++){
			event   = topmc_procs[cpu][counter].event;
			switch((event&TOPMC_EVENT_MASK_KERNEL_USER)>>TOPMC_EVENT_BITS_KERNEL_USER){
				case 0:
					kernel=user=0;
					break;
				case 1:
					kernel=0;
					user=1;
					break;
				case 2:
					kernel=1;
					user=0;
					break;
				case 3:
					kernel=user=1;
					break;
				default:
					printk("+->topmc_enable_write():kernel_user error:%d\n",(event&TOPMC_EVENT_MASK_KERNEL_USER)>>TOPMC_EVENT_BITS_KERNEL_USER);
					break;
			}

			if(enable=='1'){
				if(topmc_procs[cpu][counter].enable==1){
					printk("+->topmc_enable_all_write(): already enabled, skip this!!!\n");
					goto out;
				}

				TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_PERFCTR0+counter, 0LL, cpu);
				TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+counter, val, cpu);
				val &= MSR_PPRO_EVENTSEL_RESERVED;
				//low = (unsigned int)(val & 0xffffffff);
				//high = (unsigned int)((val & 0xffffffff00000000) >> 32);
				TOPMC_CTRL_SET_ENABLE(val);
				TOPMC_CTRL_SET_USR(val, user);
				TOPMC_CTRL_SET_KERN(val, kernel);
				TOPMC_CTRL_SET_UM(val,(event&TOPMC_EVENT_MASK_UNIT)>>TOPMC_EVENT_BITS_UNIT);
				TOPMC_CTRL_SET_EVENT_LOW(val, (event&TOPMC_EVENT_MASK_LOW_EVENT)>>TOPMC_EVENT_BITS_LOW_EVENT);
				TOPMC_CTRL_SET_CM(val, (event&TOPMC_EVENT_MASK_CMASK)>>TOPMC_EVENT_BITS_CMASK);
                                TOPMC_CTRL_SET_INV(val, (event&TOPMC_EVENT_MASK_INV)>>TOPMC_EVENT_BITS_INV);
                                TOPMC_CTRL_SET_EDGE(val, (event&TOPMC_EVENT_MASK_EDGE)>>TOPMC_EVENT_BITS_EDGE);
				//TOPMC_CTRL_SET_EVENT_HIGH(high,(event&TOPMC_EVENT_MASK_HIGH_EVENT)>>TOPMC_EVENT_BITS_HIGH_EVENT);
				//TOPMC_CTRL_SET_HOST_ONLY(high, 0);
				//TOPMC_CTRL_SET_GUEST_ONLY(high, 0);

				TOPMC_CTRL_SET_ACTIVE(val);
				//val = (u64)( low | ((u64)(high) << 32));
				TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+counter, val, cpu);
				topmc_procs[cpu][counter].enable        = 1;
				//                              printk("+->topmc_enable_all_write(): abled [cpu:%2d,counter:%d,smp_processor_id:%d]high:0x%x,low:0x%x\n",cpu,counter,smp_processor_id(),high,low);
			}
			else{
				TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_PERFCTR0+counter, 0LL, cpu);
				TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+counter, val, cpu);
				val &= MSR_PPRO_EVENTSEL_RESERVED;
				TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+counter, val, cpu);
				TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_PERFCTR0+counter, val, cpu);
				value = (unsigned long long)val;
				topmc_procs[cpu][counter].value = value;
				TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_PERFCTR0+counter, 0LL, cpu);
				topmc_procs[cpu][counter].enable        = 0;
				//                              printk("+->topmc_enable_all_write(): disabled [cpu:%2d,counter:%d,smp_processor_id:%d]high:0x%x,low:0x%x\n",cpu,counter,smp_processor_id(),high,low);                                      
			}
		}
//Zhang Jiutian: Fix Uncore bug
#if 1
		for (counter = 0; counter < TOPMC_MSR_XEON55XX_UNC_PerfCtrNum; counter++) {
			event = topmc_procs[cpu][TOPMC_MSR_XEON55XX_PerfCtrNum+counter].event;
			if (enable == '1') {
				if( topmc_procs[cpu][TOPMC_MSR_XEON55XX_PerfCtrNum+counter].enable == 1) {
					printk("+->topmc_enable_all_write(): already enabled, skip this!!!\n");
					goto out;
				}                                     
				TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_PERFCTR0+counter, 0LL, cpu);
				TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+counter, val, cpu);
				//val &= TOPMC_MSR_XEON55XX_UNC_EVENTSEL_RESERVED;
				val &= 0ULL;
				TOPMC_CTRL_SET_ENABLE(val);
				TOPMC_CTRL_SET_UM(val, (event & TOPMC_EVENT_MASK_UNIT) >> TOPMC_EVENT_BITS_UNIT);
				TOPMC_CTRL_SET_EVENT_LOW(val, (event & TOPMC_EVENT_MASK_LOW_EVENT) >> TOPMC_EVENT_BITS_LOW_EVENT);
	                        TOPMC_CTRL_SET_CM(val, (event&TOPMC_EVENT_MASK_CMASK)>>TOPMC_EVENT_BITS_CMASK);
        	                TOPMC_CTRL_SET_INV(val, (event&TOPMC_EVENT_MASK_INV)>>TOPMC_EVENT_BITS_INV);
                	        TOPMC_CTRL_SET_EDGE(val, (event&TOPMC_EVENT_MASK_EDGE)>>TOPMC_EVENT_BITS_EDGE);

				TOPMC_CTRL_SET_ACTIVE(val);
				TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+counter, val, cpu);
				topmc_procs[cpu][TOPMC_MSR_XEON55XX_PerfCtrNum+counter].enable = 1;
			}
			else {
				TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_PERFCTR0+counter, 0LL, cpu);
				TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+counter, val, cpu);
				//val &= TOPMC_MSR_XEON55XX_UNC_EVENTSEL_RESERVED;
				val &= 0ULL;
				TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+counter, val, cpu);
				TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_UNC_PERFCTR0+counter, val, cpu);
				value = (unsigned long long)val;
				topmc_procs[cpu][TOPMC_MSR_XEON55XX_PerfCtrNum+counter].value = value;
				TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_PERFCTR0+counter, 0LL, cpu);
				topmc_procs[cpu][TOPMC_MSR_XEON55XX_PerfCtrNum+counter].enable = 0;
			}
		}
#endif
	}


#ifdef TOPMC_PER_SECOND
	spin_lock_irqsave(&topmc_bitmap_lock, topmc_pmc_cnt_flags);
#endif

	if(enable=='1')
	{
		topmc_all_enabled       = 1;

#ifdef TOPMC_PER_SECOND
		set_topmc_cnt_all(topmc_pmc_cnt_bitmap);
#endif

	}
	else
	{
		topmc_all_enabled       = 0;

#ifdef TOPMC_PER_SECOND
		clr_topmc_cnt_all(topmc_pmc_cnt_bitmap);
#endif

	}

#ifdef TOPMC_PER_SECOND
	spin_unlock_irqrestore(&topmc_bitmap_lock, topmc_pmc_cnt_flags);
	spin_lock_irqsave(&topmc_chg_lock, topmc_pmc_chg_flags);
//	printk("topmc_enable_all_write: before topmc_pmc_chg=%d\n",topmc_pmc_chg);
	topmc_pmc_chg = 1;
//	printk("topmc_enable_all_write: after topmc_pmc_chg=%d\n",topmc_pmc_chg);
	spin_unlock_irqrestore(&topmc_chg_lock, topmc_pmc_chg_flags);
#endif

out:
	return count;
}


int topmc_enable_read_nehelam(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	unsigned int mix        = *(unsigned int *)data;
	unsigned short cpu,counter;

	topmc_split32to16(mix,&cpu,&counter);

	*page   = topmc_procs[cpu][counter].enable==1?'1':'0';
	*(page+1) = '\n';
	return 2; //len of read
}


int topmc_enable_write_nehelam(struct file *file, const char __user * buffer, unsigned long count, void * data)
{
	char enable;
	unsigned int mix        = *(unsigned int *)data;
	unsigned short cpu,counter;
	//unsigned int low = 0,high =0;
	int kernel=0,user=0,event;
	unsigned long long value;
	u64 val = 0;

	topmc_split32to16(mix,&cpu,&counter);
	get_user(enable,buffer);

	event   = topmc_procs[cpu][counter].event;
	if (counter < TOPMC_MSR_XEON55XX_PerfCtrNum) {
		switch((event&TOPMC_EVENT_MASK_KERNEL_USER)>>TOPMC_EVENT_BITS_KERNEL_USER){
			case 0:
				kernel=user=0;
				break;
			case 1:
				kernel=0;
				user=1;
				break;
			case 2:
				kernel=1;
				user=0;
				break;
			case 3:
				kernel=user=1;
				break;
			default:
				printk("+->topmc_enable_write():kernel_user error:%d\n",(event&TOPMC_EVENT_MASK_KERNEL_USER)>>TOPMC_EVENT_BITS_KERNEL_USER);
				break;
		}
		if(enable=='1'){
			if(topmc_procs[cpu][counter].enable==1){
				printk("+->topmc_enable_write():already enabled, skip this!!!\n");
				goto out;
			}
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_PERFCTR0+counter, 0LL, cpu);
			TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+counter, val, cpu);
			val &= MSR_PPRO_EVENTSEL_RESERVED;
			//low = (unsigned int)(val & 0xffff);
			//high = (unsigned int)((val & 0xffff0000) >> 32);
			TOPMC_CTRL_SET_ENABLE(val);
			TOPMC_CTRL_SET_USR(val, user);
			TOPMC_CTRL_SET_KERN(val, kernel);
			TOPMC_CTRL_SET_UM(val,(event&TOPMC_EVENT_MASK_UNIT)>>TOPMC_EVENT_BITS_UNIT);
			TOPMC_CTRL_SET_EVENT_LOW(val, (event&TOPMC_EVENT_MASK_LOW_EVENT)>>TOPMC_EVENT_BITS_LOW_EVENT);
			TOPMC_CTRL_SET_CM(val, (event&TOPMC_EVENT_MASK_CMASK)>>TOPMC_EVENT_BITS_CMASK);
			TOPMC_CTRL_SET_INV(val, (event&TOPMC_EVENT_MASK_INV)>>TOPMC_EVENT_BITS_INV);
			TOPMC_CTRL_SET_EDGE(val, (event&TOPMC_EVENT_MASK_EDGE)>>TOPMC_EVENT_BITS_EDGE);
			//TOPMC_CTRL_SET_EVENT_HIGH(high,(event&TOPMC_EVENT_MASK_HIGH_EVENT)>>TOPMC_EVENT_BITS_HIGH_EVENT);
			//TOPMC_CTRL_SET_HOST_ONLY(high, 0);
			//TOPMC_CTRL_SET_GUEST_ONLY(high, 0);

			TOPMC_CTRL_SET_ACTIVE(val);
			//val = (u64)( low | ((u64)(high) << 32));
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+counter, val, cpu);
			topmc_procs[cpu][counter].enable        = 1;
		}
		else{
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_PERFCTR0+counter, 0LL, cpu);
			TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+counter, val, cpu);
			val &= MSR_PPRO_EVENTSEL_RESERVED;
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+counter, val, cpu);
			TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_PERFCTR0+counter, val, cpu);
			value = (unsigned long long)val;
			topmc_procs[cpu][counter].value = value;
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_PERFCTR0+counter, 0LL, cpu);
			topmc_procs[cpu][counter].enable        = 0;
		}
	}
//Zhang Jiutian: Fix Uncore bug
#if 1
	else if ((counter >= TOPMC_MSR_XEON55XX_PerfCtrNum) && (counter < TOPMC_MSR_XEON55XX_PerfCtrNum + TOPMC_MSR_XEON55XX_UNC_PerfCtrNum)) {
		event = topmc_procs[cpu][counter].event;
		if (enable == '1') {
			if( topmc_procs[cpu][counter].enable == 1) {
				printk("+->topmc_enable_write(): already enabled, skip this!!!\n");
				goto out;
			}
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_PERFCTR0+counter- TOPMC_MSR_XEON55XX_PerfCtrNum, 0LL, cpu);
			TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+counter- TOPMC_MSR_XEON55XX_PerfCtrNum, val, cpu);
			//val &= TOPMC_MSR_XEON55XX_UNC_EVENTSEL_RESERVED;
			val &= 0ULL;
			TOPMC_CTRL_SET_ENABLE(val);
			//printk("+->topmc_enable_write(): event: %d\n", event);
			TOPMC_CTRL_SET_UM(val, (event & TOPMC_EVENT_MASK_UNIT) >> TOPMC_EVENT_BITS_UNIT);
			//printk("+->topmc_enable_wirte(): val:%llu event_mask:%d\n",val, event & TOPMC_EVENT_MASK_UNIT);
			TOPMC_CTRL_SET_EVENT_LOW(val, (event & TOPMC_EVENT_MASK_LOW_EVENT) >> TOPMC_EVENT_BITS_LOW_EVENT);
                        TOPMC_CTRL_SET_CM(val, (event&TOPMC_EVENT_MASK_CMASK)>>TOPMC_EVENT_BITS_CMASK);
                        TOPMC_CTRL_SET_INV(val, (event&TOPMC_EVENT_MASK_INV)>>TOPMC_EVENT_BITS_INV);
                        TOPMC_CTRL_SET_EDGE(val, (event&TOPMC_EVENT_MASK_EDGE)>>TOPMC_EVENT_BITS_EDGE);
			//printk("+->topmc_enable_wirte(): val:%llu event_mask_mask:%d\n",val, event & TOPMC_EVENT_MASK_LOW_EVENT);

			TOPMC_CTRL_SET_ACTIVE(val);
			//printk("+->topmc_enable_wirte(): val:%llu\n",val);
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+counter- TOPMC_MSR_XEON55XX_PerfCtrNum, val, cpu);
			topmc_procs[cpu][counter].enable = 1;
			//printk("+->topmc_enable_write() enabled [cpu:%2d,counter:%d,smp_processor_id:%d]mask:%llu\n",cpu,counter,smp_processor_id(),val);
		}
		else {
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_PERFCTR0+counter- TOPMC_MSR_XEON55XX_PerfCtrNum, 0LL, cpu);
			TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+counter- TOPMC_MSR_XEON55XX_PerfCtrNum, val, cpu);
			//val &= TOPMC_MSR_XEON55XX_UNC_EVENTSEL_RESERVED;
			val &= 0ULL;
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+counter- TOPMC_MSR_XEON55XX_PerfCtrNum, val, cpu);
			TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_UNC_PERFCTR0+counter- TOPMC_MSR_XEON55XX_PerfCtrNum, val, cpu);
			value = (unsigned long long)val;
			topmc_procs[cpu][counter].value = value;
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_PERFCTR0+counter- TOPMC_MSR_XEON55XX_PerfCtrNum, 0LL, cpu);
			topmc_procs[cpu][counter].enable = 0;
			//printk("+->topmc_enable_write() disenabled[cpu:%2d,counter:%d,smp_processor_id:%d]mask:%llu\n",cpu,counter,smp_processor_id(),val);
		}
	}
#endif
	//display some useful information
	// printk("+->topmc_enable_write() [cpu:%2d,counter:%d,smp_processor_id:%d]mask:%llu\n",cpu,counter,smp_processor_id(),val);
	
#ifdef TOPMC_PER_SECOND
	spin_lock_irqsave(&topmc_bitmap_lock, topmc_pmc_cnt_flags);
	if(enable == '1')
	{
		set_topmc_cnt(topmc_pmc_cnt_bitmap, counter);
	}
	else
	{
		clr_topmc_cnt(topmc_pmc_cnt_bitmap, counter);
	}
	spin_unlock_irqrestore(&topmc_bitmap_lock, topmc_pmc_cnt_flags);
	spin_lock_irqsave(&topmc_chg_lock, topmc_pmc_chg_flags);
//	printk("topmc_enable_write: before topmc_pmc_chg=%d\n",topmc_pmc_chg);
	topmc_pmc_chg = 1;
//	printk("topmc_enable_write: after topmc_pmc_chg=%d\n",topmc_pmc_chg);
	spin_unlock_irqrestore(&topmc_chg_lock, topmc_pmc_chg_flags);
#endif

out:
	return count;
}


/*                      
event format:           
                        
[*][*][*]|[-][-]|[+]    
event    |unit  |kernel/user
                
all of the above values are hex value such as 0xa98d
event--MUST BE three numbers
unit---MUST BE two numbers
kernel/user---MUST BE one of the following number: 0-"neither",1-"only user",2-"only kernel",3-"both"

*/
int topmc_event_read_nehelam(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	unsigned int mix        = *(unsigned int *)data;
	unsigned short cpu,counter;

	topmc_split32to16(mix,&cpu,&counter);

	sprintf(page,"0x%08x\n",topmc_procs[cpu][counter].event);

	return strlen(page); //len of read, event must between 01~99
}

int topmc_event_write_nehelam(struct file *file, const char __user * buffer, unsigned long count, void * data)
{
	char event[TOPMC_EVENT_LENGTH];
	unsigned int mix        = *(unsigned int *)data;
	unsigned short cpu,counter;
	int i;
	long ret;

	topmc_split32to16(mix,&cpu,&counter);

	ret     = strncpy_from_user(event,buffer,TOPMC_EVENT_LENGTH);
	if (ret < 0)
		return -EFAULT;
	if (ret == 0 || ret > TOPMC_EVENT_LENGTH)
		return -EINVAL;

	for(i=0;i<TOPMC_EVENT_LENGTH;i++){
		if(!isxdigit(event[i])){
			topmc_procs[cpu][counter].event = 0;
			printk("+->topmc_event_write():event error:%s!!!\n",event);
			goto out;
		}
	}

	topmc_procs[cpu][counter].event = topmc_str2int(event,8,16);
out:
	return count;
}


#ifdef TOPMC_PER_SECOND
u64 topmc_value_read_callable_impl_nehelam(unsigned short cpu, unsigned short counter)
{
	u64 val;
	u32 lo,hi;
	unsigned int perfctr;

	if(counter>=TOPMC_MSR_XEON55XX_PerfCtrNum + TOPMC_MSR_XEON55XX_UNC_PerfCtrNum){
		printk("+->topmc: topmc_value_read(): counter err : %d!!!\n",counter);

		return 0;
	}

	if(counter < TOPMC_MSR_XEON55XX_PerfCtrNum) {
		perfctr = TOPMC_MSR_XEON55XX_PERFCTR0 + counter;
		//      perfctrl = TOPMC_MSR_XEON55XX_EVNTSEL0 + counter;
	}
	else {  
		perfctr =  TOPMC_MSR_XEON55XX_UNC_PERFCTR0 + counter - TOPMC_MSR_XEON55XX_PerfCtrNum;
		//      perfctrl = TOPMC_MSR_XEON55XX_UNC_EVNTSEL0 + counter - TOPMC_MSR_XEON55XX_PerfCtrNum;
	}
	/*      

		printk("+->topmc_value_read(): read performance counter:%x\n",perfctr);
		TOPMC_RDMSRL(perfctrl, val_ctrl, cpu);
		printk("+->topmc_value_read(): eventselect: %llu\n", val_ctrl);
	 */
	/*
	   if(topmc_procs[cpu][counter].enable == 1){
	//      printk("+->topmc_value_read() : enable ==1   \n");
	TOPMC_RDMSRL(perfctr, val, cpu);
	}else{
	//      printk("+->topmc_value_read() : enable == 0\n");
	val = topmc_procs[cpu][counter].value;
	}
	 */
//	printk("topmc_value_read_callable:perfctr= %x\n", perfctr);
	//if(counter < TOPMC_MSR_XEON55XX_PerfCtrNum) //Zhang Jiutian: Fix Uncore bug
	__asm__ __volatile__ ("rdmsr" : "=a" (lo), "=d" (hi) : "c" (perfctr));
	val = (u64)hi<<32 | lo;
//	val = counter + cpu;
//	printk("topmc_value_read_callable: %llu\n", val);
	return val;
}

#endif
//EXPORT_SYMBOL(topmc_value_read_callable);

int topmc_value_read_nehelam(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	unsigned int perfctr;
	//unsigned int perfctrl;
	unsigned int mix        = *(unsigned int *)data;
	unsigned short cpu,counter;
	u64 val;
	//u64 val_ctrl;

	topmc_split32to16(mix,&cpu,&counter);

	if(counter>=TOPMC_MSR_XEON55XX_PerfCtrNum + TOPMC_MSR_XEON55XX_UNC_PerfCtrNum){
		printk("+->topmc: topmc_value_read(): counter err : %d!!!\n",counter);

		return 0;
	}

	if(counter < TOPMC_MSR_XEON55XX_PerfCtrNum) {
		perfctr = TOPMC_MSR_XEON55XX_PERFCTR0 + counter;
	}
	else {
		perfctr =  TOPMC_MSR_XEON55XX_UNC_PERFCTR0 + counter - TOPMC_MSR_XEON55XX_PerfCtrNum;
	}
	if(topmc_procs[cpu][counter].enable == 1){
		//      printk("+->topmc_value_read() : enable ==1   \n");
		//if(counter < TOPMC_MSR_XEON55XX_PerfCtrNum) //Zhang Jiutian: Fix Uncore bug
		TOPMC_RDMSRL(perfctr, val, cpu);
		sprintf(page, "%llu\n", val);

	}else{
		//      printk("+->topmc_value_read() : enable == 0\n");
		sprintf(page,"%llu\n",topmc_procs[cpu][counter].value);
	}

	return strlen(page); //len of read
}

int topmc_value_write_nehelam(struct file *file, const char __user * buffer, unsigned long count, void * data)
{
	unsigned int mix        = *(unsigned int *)data;
	unsigned short cpu,counter;
	u64 val;

	topmc_split32to16(mix,&cpu,&counter);

	if(counter>=TOPMC_MSR_XEON55XX_PerfCtrNum + TOPMC_MSR_XEON55XX_UNC_PerfCtrNum){
		printk("+->topmc: topmc_value_write(): counter err : %d!!!\n",counter);
		return 0;
	}

	//FIXME:just set counter to zero
	if(counter < TOPMC_MSR_XEON55XX_PerfCtrNum){
		//first: clear the event selector
		TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+counter, val, cpu);
		//        printk("+->incore event selector val: 0x%llu\n", val);
		val &= MSR_PPRO_EVENTSEL_RESERVED;
		TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+counter, val, cpu);

		//second: clear the counter
		TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_PERFCTR0+counter, 0LL, cpu);
	}
//Zhang Jiutian: Fix Uncore bug
#if 1
	else if (counter < TOPMC_MSR_XEON55XX_PerfCtrNum + TOPMC_MSR_XEON55XX_UNC_PerfCtrNum) {
		//first: clear the event selector
		TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+counter-TOPMC_MSR_XEON55XX_PerfCtrNum, val, cpu);
		//      printk("+->uncore event selector val: 0x%llu\n", val);
		//val &= TOPMC_MSR_XEON55XX_UNC_EVENTSEL_RESERVED;
		val &= 0ULL;
		TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+counter-TOPMC_MSR_XEON55XX_PerfCtrNum, val, cpu);

		//second: clear the counter
		TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_PERFCTR0+counter, 0LL, cpu);
	}
#endif

	return count;
}

void topmc_msr_init_nehelam(void)
{
	int i,cpu;
	u64 val;

	for_each_online_cpu(cpu){
		//      printk("+-> topmc_msr_init(): cpu:%d\n",cpu);

		/* in core section */
		//first: clear the event selectors
		for (i = 0 ; i < TOPMC_MSR_XEON55XX_PerfCtrNum; ++i) {
			if (unlikely(!TOPMC_MSR_XEON55XX_EVNTSEL0+i))
				continue;
			TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+i, val, cpu);
			val &= MSR_PPRO_EVENTSEL_RESERVED;
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_EVNTSEL0+i, val, cpu);
		}

		//second: clear the counter
		for (i = 0; i < TOPMC_MSR_XEON55XX_PerfCtrNum; ++i) {
			if (unlikely(!TOPMC_MSR_XEON55XX_PERFCTR0+i))
				continue;
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_PERFCTR0+i, 0LL, cpu);
		}

		/* uncore section */
//Zhang Jiutian: Fix Uncore bug
#if 1
		for (i = 0; i < TOPMC_MSR_XEON55XX_UNC_PerfCtrNum; ++i) {
			if (unlikely(!TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+i))
				continue;
			TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+i, val, cpu);
			val &= 0ULL;
			//val &= TOPMC_MSR_XEON55XX_UNC_EVENTSEL_RESERVED;
			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_EVNTSEL0+i, val, cpu);
		}

		for (i = 0; i < TOPMC_MSR_XEON55XX_UNC_PerfCtrNum; ++i) {
			if (unlikely(!TOPMC_MSR_XEON55XX_UNC_PERFCTR0+i))
				continue;

			TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_PERFCTR0+i, 0LL, cpu);
		}
#endif
	}
}

void topmc_core_global_ctrl_init_nehelam(void)
{
	u64 mask;
	int cpu;

	for_each_online_cpu(cpu) {
		TOPMC_RDMSRL(MSR_CORE_PERF_GLOBAL_CTRL, mask, cpu);
		mask &=0ULL;
		mask |= ((1ULL << MSR_CORE_PERF_NUM_PMC) -1) << MSR_CORE_PERF_IDX_PMC;
		mask |= ((1ULL << MSR_CORE_PERF_NUM_FIX) -1) << MSR_CORE_PERF_IDX_FIX;
		TOPMC_WRMSRL(MSR_CORE_PERF_GLOBAL_CTRL, mask, cpu);
		TOPMC_RDMSRL(MSR_CORE_PERF_GLOBAL_CTRL, mask, cpu);
		//      printk("+->topmc: topmc_core_global_ctrl_init(): global control mask -> %llu\n", mask);

		TOPMC_RDMSRL(MSR_CORE_PERF_GLOBAL_OVF_CTRL, mask, cpu);
		//      printk("+->topmc: topmc_core_global_ctrl_init(): global overflow control mask -> %llu\n", mask);
	}
}

/* initialization uncore global msrs*/
void topmc_uncore_global_ctrl_init_nehelam(void)
{
	u64 mask;
	int cpu;

	for_each_online_cpu(cpu) {
		// initialization global control msr
		TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_UNC_GLOBAL_CTRL, mask, cpu);
		mask &= 0ULL;
		mask |= ((1ULL << TOPMC_MSR_XEON55XX_UNC_BITS_NUM_PMC) - 1) << TOPMC_MSR_XEON55XX_UNC_IDX_PMC;
		mask |=  (1ULL << TOPMC_MSR_XEON55XX_UNC_IDX_FIXED);
		mask |= 1ULL <<( 48 + cpu%4);
		//mask |= 1ULL << ( 48 + cpu_data(smp_processor_id()).cpu_core_id);
		//      printk("+->topmc: topmc_uncore_global_ctrl_init(): global control mask-> %llu\n",mask);
		TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_GLOBAL_CTRL, mask, cpu);

		//initialization global global overflow control msr ----------not needed at the moment
		TOPMC_WRMSRL(TOPMC_MSR_XEON55XX_UNC_GLOBAL_OVF_CTRL, 0ULL, cpu);
		//    TOPMC_RDMSRL(TOPMC_MSR_XEON55XX_UNC_GLOBAL_OVF_CTRL, mask, cpu);
		//  printk("+->topmc: topmc_uncore_global_ctrl_init(): global overflowed control mask-> %llu\n",mask);
	}
}


struct topmc_x86_model topmc_op_intel_nehelam = {
	.num_counters_core = TOPMC_MSR_XEON55XX_PerfCtrNum,
	.num_counters_uncore = TOPMC_MSR_XEON55XX_UNC_PerfCtrNum,
	.is_exist_topmc_core_global_ctrl_init = 1,
	.is_exist_topmc_uncore_global_ctrl_init = 1,
	.topmc_msr_init = &topmc_msr_init_nehelam,
	.topmc_core_global_ctrl_init = &topmc_core_global_ctrl_init_nehelam,
	.topmc_uncore_global_ctrl_init = &topmc_uncore_global_ctrl_init_nehelam,
	.topmc_enable_all_read = &topmc_enable_all_read_nehelam,
	.topmc_enable_all_write = &topmc_enable_all_write_nehelam,
	.topmc_enable_read = &topmc_enable_read_nehelam,
	.topmc_enable_write = &topmc_enable_write_nehelam,
	.topmc_event_read = &topmc_event_read_nehelam,
	.topmc_event_write = &topmc_event_write_nehelam,
	#ifdef TOPMC_PER_SECOND
	.topmc_value_read_callable_impl = &topmc_value_read_callable_impl_nehelam,
	#endif
	.topmc_value_read = &topmc_value_read_nehelam,
	.topmc_value_write = &topmc_value_write_nehelam
};



