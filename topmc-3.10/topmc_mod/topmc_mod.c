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



//performance monitoring counter like top : yuanbor@2009-2-24   modified by huangy@2010-3-24

//#include <asm/Msr.h>

#include "topmc_x86_model.h"
#include "topmc_mod_lib.h"
#include "topmc_cr4pce.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TOP Perf Counter Kernel Module");

//#define TOPMC_MAX_COUNTER 32
#define TOPMC_MAX_NAMELEN 16

static struct topmc_x86_model *model;


struct topmc_proc_entry topmc_procs[NR_CPUS][TOPMC_MAX_COUNTER];
static struct proc_dir_entry *enable_all_cr4_pce_entry;

static struct proc_dir_entry * root_dir, * core_dir[NR_CPUS], * counter_dir[NR_CPUS][TOPMC_MAX_COUNTER];
static struct proc_dir_entry *enable_entry, * entry[NR_CPUS][TOPMC_MAX_COUNTER][3];

unsigned int enable_all_cr4_pce;
unsigned int mix_cpu_counter[NR_CPUS][TOPMC_MAX_COUNTER];

//#define TOPMC_PER_SECOND
#ifdef TOPMC_PER_SECOND
/*
unsigned long topmc_pmc_cnt_flags;
unsigned long topmc_pmc_chg_flags;

extern spinlock_t topmc_bitmap_lock;
extern spinlock_t topmc_chg_lock;
extern unsigned short topmc_pmc_cnt_bitmap;
extern unsigned int topmc_pmc_chg;
*/
extern u64 (*topmc_value_read_callable)(unsigned short cpu, unsigned short counter);

#endif
/*
EXPORT_SYMBOL(topmc_bitmap_lock);
EXPORT_SYMBOL(topmc_chg_lock);
EXPORT_SYMBOL(topmc_pmc_cnt_bitmap);
EXPORT_SYMBOL(topmc_pmc_chg);
*/

//int topmc_cr4_pce_read(char *page, char **start, off_t off, int count, int *eof, void *data)
int topmc_cr4_pce_read(struct file *filp,char *buffer,size_t count,loff_t *offp ) 
{
    int cpu;
    int pce;
    int is_set=1;

    for_each_online_cpu(cpu) {
        TOPMC_READ_CR4_PCE(cpu, pce);
        is_set &= pce;
    }
    //count = sprintf(page, "%d\n", is_set);
    count = sprintf(buffer, "%d\n", is_set);
    //count = sprintf(data, "%d\n", is_set);

    return count;
}

//int topmc_cr4_pce_write(struct file *file, const char __user *buffer, unsigned long count, void *data)
int topmc_cr4_pce_write(struct file *filp, const char *buffer,size_t count,loff_t *offp ) 
{
    int i;
    int cpu;
    unsigned int sum = 0;
    unsigned int pce;
    //char* str = (char*) data;
	char* str;
    long ret;

	//char *data;
	str=PDE_DATA(file_inode(filp));
	if(!(str)){
		printk(KERN_INFO "Null data");
		return 0;
	}

    ret = strncpy_from_user(str, buffer, count);
    if(ret < 0)
        return -EFAULT;
    if(ret ==0 || ret > count)
        return -EINVAL;

    for(i=0; i<count-1; i++) {
        sum = sum*10+ str[i] - '0';
    }
    if( sum>0 ) {
        pce = 1;
    } else {
        pce = 0;
    }

    for_each_online_cpu(cpu) {
        TOPMC_WRITE_CR4_PCE(cpu, pce);
    }

    return count;
}

static struct file_operations topmc_cr4_pce_fops = 
{
	//.owner = THIS_MODULE,
	.read = topmc_cr4_pce_read,
	.write = topmc_cr4_pce_write,
};

//int topmc_enable_all_read(char *page, char **start, off_t off, int count, int *eof, void *data)
int topmc_enable_all_read(struct file *filp,char *buffer,size_t count,loff_t *offp ) 
{
	if(model->topmc_enable_all_read != NULL)
		//return model->topmc_enable_all_read(page, start, off, count, eof, data);
		return model->topmc_enable_all_read(filp, buffer, count, offp);
	else
		return 0;
}

//int topmc_enable_all_write(struct file *file, const char __user * buffer, unsigned long count, void * data)
int topmc_enable_all_write(struct file *filp, const char *buffer,size_t count,loff_t *offp ) 
{
	if(model->topmc_enable_all_write != NULL) 
		return model->topmc_enable_all_write(filp, buffer, count, offp);
	else
		return 0;
}

static struct file_operations topmc_enable_all_fops = 
{
	//.owner = THIS_MODULE,
	.read = topmc_enable_all_read,
	.write = topmc_enable_all_write,
};

//int topmc_enable_read(char *page, char **start, off_t off, int count, int *eof, void *data)
int topmc_enable_read(struct file *filp,char __user *buffer,size_t count,loff_t *offp ) 
{
//	printk("buffer address = 0x%lx, count = %d \n",buffer,count);
	return model->topmc_enable_read(filp, buffer, count, offp);
}


//int topmc_enable_write(struct file *file, const char __user * buffer, unsigned long count, void * data)
int topmc_enable_write(struct file *filp, const char *buffer,size_t count,loff_t *offp ) 
{
	return model->topmc_enable_write(filp, buffer, count, offp); 
}

static struct file_operations topmc_enable_fops = 
{
	//.owner = THIS_MODULE,
	.read = topmc_enable_read,
	.write = topmc_enable_write,
};

/*                      
event format:           
                        
[*][*][*]|[-][-]|[+]    
event    |unit  |kernel/user
                
all of the above values are hex value such as 0xa98d
event--MUST BE three numbers
unit---MUST BE two numbers
kernel/user---MUST BE one of the following number: 0-"neither",1-"only user",2-"only kernel",3-"both"

*/
//int topmc_event_read(char *page, char **start, off_t off, int count, int *eof, void *data)
int topmc_event_read(struct file *filp,char *buffer,size_t count,loff_t *offp )
{
	return model->topmc_event_read(filp, buffer, count, offp); 
}

//int topmc_event_write(struct file *file, const char __user * buffer, unsigned long count, void * data)
int topmc_event_write(struct file *filp, const char *buffer,size_t count,loff_t *offp ) 
{
	return model->topmc_event_write(filp, buffer, count, offp); 
}

static struct file_operations topmc_event_fops = 
{
	//.owner = THIS_MODULE,
	.read = topmc_event_read,
	.write = topmc_event_write,
};


#ifdef TOPMC_PER_SECOND
u64 topmc_value_read_callable_impl(unsigned short cpu, unsigned short counter)
{
	return model->topmc_value_read_callable_impl(cpu, counter); 
}

#endif

//int topmc_value_read(char *page, char **start, off_t off, int count, int *eof, void *data)
int topmc_value_read(struct file *filp,char *buffer,size_t count,loff_t *offp ) 
{
	return model->topmc_value_read(filp, buffer, count, offp); 
}

//int topmc_value_write(struct file *file, const char __user * buffer, unsigned long count, void * data)
int topmc_value_write(struct file *filp, const char *buffer,size_t count,loff_t *offp ) 
{
	return model->topmc_value_write(filp, buffer, count, offp); 
}

static struct file_operations topmc_value_fops = 
{
	//.owner = THIS_MODULE,
	.read = topmc_value_read,
	.write = topmc_value_write,
};

void topmc_msr_init(void)
{
	model->topmc_msr_init();
}

void topmc_core_global_ctrl_init(void)
{
	if(model->is_exist_topmc_core_global_ctrl_init)
		model->topmc_core_global_ctrl_init();
	return;
}

/* initialization uncore global msrs*/
void topmc_uncore_global_ctrl_init(void)
{
	if(model->is_exist_topmc_uncore_global_ctrl_init)
		model->topmc_uncore_global_ctrl_init();
	return;
}


void topmc_enable_rdpmc(void)
{
	int cpu;
    unsigned long cr4;
    int val = 0;

    val = 1;
	for_each_online_cpu(cpu) {
		topmc_write_cr4_pce(cpu, val);
        cr4 = read_cr4();
		printk("topmc_enable_rdpmc:cpu=%d, cr4:%lx\n",cpu,cr4);
	}

}

/* proc filesystem clean process: entry -> counter -> core -> topmc
 */

void topmc_proc_clean(void)
{

	//int i;
	int cpu,counter;
	char namebuf[TOPMC_MAX_NAMELEN];

	if(enable_entry) {
		remove_proc_entry("enable_all",root_dir);
		enable_entry = NULL;
	}

    if(enable_all_cr4_pce_entry) {
        remove_proc_entry("enable_cr4_pce", root_dir);
        enable_all_cr4_pce_entry = NULL;
    }

	for_each_online_cpu(cpu){
		if(core_dir[cpu]) {
			for(counter=0;counter<model->num_counters_core + model->num_counters_uncore;counter++){
				if(counter_dir[cpu][counter]) {
					if(entry[cpu][counter][0]) {
						remove_proc_entry("enable",counter_dir[cpu][counter]); 
						entry[cpu][counter][0]=NULL;
					}
					if(entry[cpu][counter][1]) {
						remove_proc_entry("event",counter_dir[cpu][counter]); 
						entry[cpu][counter][1]=NULL;
					}
					if(entry[cpu][counter][2]) {
						remove_proc_entry("value",counter_dir[cpu][counter]); 
						entry[cpu][counter][2]=NULL;
					}
					memset(namebuf,0,TOPMC_MAX_NAMELEN);
					if( counter < model->num_counters_core) {
						sprintf(namebuf,"incore_counter%d",counter);
					}
					if( counter >= model->num_counters_core) {
						sprintf(namebuf, "uncore_counter%d",counter- model->num_counters_core);
					}
					remove_proc_entry(namebuf,core_dir[cpu]);
					counter_dir[cpu][counter] = NULL;
				}
			}
			memset(namebuf,0,TOPMC_MAX_NAMELEN);	
			sprintf(namebuf,"core%02d",cpu);
			remove_proc_entry(namebuf,root_dir);
			core_dir[cpu]=NULL;
		} 
	}

	if(root_dir) {
		remove_proc_entry("topmc",NULL);
		root_dir = NULL;
	}

}

int topmc_model_detect(void)
{
	__u8 vendor = boot_cpu_data.x86_vendor;
	__u8 family = boot_cpu_data.x86;
	__u8 cpu_model = /*current_cpu_data*/boot_cpu_data.x86_model;

	if(!cpu_has_apic)
		return -ENODEV;
	printk("topmc->topmc_model_detect(): vendor:%d, family: %d.\n", vendor, family);
	switch(vendor) {
	case X86_VENDOR_AMD:
		switch(family) {
		case 16:
			//model = &topmc_op_amd;
			printk("topmc->topmc_model_detect(): family: amd/6.\n");
			break;
		default:
			//model = &topmc_op_amd;
			printk("topmc->topmc_model_detect(): family of amd %d not supported, use dafault AMD topmc_module.\n", family);
			break;
		}
		break;
	
	case X86_VENDOR_INTEL:
		switch(family) {
		case 6:
			switch(cpu_model)
			{
				case 10:
				case 26:
				//case 62:
					//model = &topmc_op_intel_nehelam;
					printk("topmc->topmc_model_detect(): family:intel nehelam.\n");
					break;
					//return 1;
					//return 0;
				case 62:
					//model = &topmc_op_intel_ivybridge_e;
					printk("topmc->topmc_model_detect(): family:intel ivybridge-e.\n");
					break;
				case 79:
					model = &topmc_op_intel_broadwell;
                                        printk("topmc->topmc_model_detect(): family:intel broadwell.\n");
                                        break;
				case 85:
					//model = &topmc_op_intel_skylake_sp;
                                        printk("topmc->topmc_model_detect(): family:intel Skylake-SP.\n");
                                        break;
			        default:
				    printk("cpu_model = %d\n",cpu_model);
			            printk("topmc->topmc_model_detect(): family of intel %d  model %d not supported.\n", family,cpu_model);
			            return 0;
			}
			break;
		default:
			printk("cpu_model = %d\n",cpu_model);
			printk("topmc->topmc_model_detect(): family of intel %d not supported.\n", family);
			return 0;
		}
		break;
	default:
		printk("topmc->topmc_model_detect(): vendor %d not supported.\n", vendor);
		return 0;
	}
	return 1;
}
/*                      
 *                      
 *topmc->core*->counter*->entry
 *
 **/
int topmc_init(void)
{
    int ret = 0;
    int cpu,counter;
    char namebuf[TOPMC_MAX_NAMELEN];

    printk("+->topmc_init() start...\n");

    topmc_model_detect();
    if(!model)
    {
        printk("The processor is not supported yet.\n");
        return ret;
    }
//    topmc_core_global_ctrl_init();
    topmc_uncore_global_ctrl_init();
//    topmc_msr_init();
#if 1
    memset(topmc_procs,0,sizeof(topmc_procs));

    root_dir        = proc_mkdir("topmc",NULL);
    if(!root_dir){
        printk("mkprocdir topmc error\n");
        ret = -ENOMEM;
        return ret;
    }


    enable_all_cr4_pce_entry = proc_create_data("enable_cr4_pce", 0, root_dir, &topmc_cr4_pce_fops, &enable_all_cr4_pce);
	//enable_all_cr4_pce_entry = create_proc_entry("enable_cr4_pce", 0666, root_dir);
    if(enable_all_cr4_pce_entry == NULL) {
        remove_proc_entry("topmc", NULL);
        ret = -ENOMEM;
        printk("topmc_mod: create enable_cr4_pce entry error\n");
        return ret;
    } 
#if 0
	else {
        enable_all_cr4_pce_entry->data       = &enable_all_cr4_pce;
        enable_all_cr4_pce_entry->read_proc  = topmc_cr4_pce_read;
        enable_all_cr4_pce_entry->write_proc = topmc_cr4_pce_write;
    }
#endif

    enable_entry   = proc_create_data("enable_all",0,root_dir, &topmc_enable_all_fops, NULL);
	//enable_entry   = create_proc_entry("enable_all",0666,root_dir);
    if(enable_entry == NULL){
        remove_proc_entry("topmc",NULL);
        ret = -ENOMEM;
        printk("topmc_mod: create enable_all entry error\n");
        return ret;
    }
#if 0
	else {
        enable_entry->read_proc        = topmc_enable_all_read;
        enable_entry->write_proc       = topmc_enable_all_write;
    }
#endif
    printk("num_counters_core = %d, num_counters_uncore = %d\n",model->num_counters_core,model->num_counters_uncore);
    for_each_online_cpu(cpu){
        printk("+->topmc_init(): cpu:%d\n",cpu);
        memset(namebuf,0,TOPMC_MAX_NAMELEN);
        sprintf(namebuf,"core%02d",cpu);
        core_dir[cpu]        = proc_mkdir(namebuf,root_dir);
        if(!core_dir[cpu]){
            printk("mkprocdir %s  error\n",namebuf);
            topmc_proc_clean();
            ret = -ENOMEM;
            return ret;
        }


        for(counter=0;counter<model->num_counters_core+model->num_counters_uncore;counter++){
            memset(namebuf,0,TOPMC_MAX_NAMELEN);
            if( counter < model->num_counters_core) {
                sprintf(namebuf,"incore_counter%d",counter);
            }
            if( counter >= model->num_counters_core) {
                sprintf(namebuf, "uncore_counter%d",counter- model->num_counters_core);
            }
            counter_dir[cpu][counter]        = proc_mkdir(namebuf,core_dir[cpu]);
            if(!counter_dir[cpu][counter]){
                printk("mkprocdir %s  error\n",namebuf);
                topmc_proc_clean();
                ret = -ENOMEM;
                return ret;
            }

            mix_cpu_counter[cpu][counter] = topmc_mix16to32((unsigned short)cpu, (unsigned short)counter);
            entry[cpu][counter][0]   = proc_create_data("enable",0,counter_dir[cpu][counter], &topmc_enable_fops, &mix_cpu_counter[cpu][counter]);
			//entry[cpu][counter][0]   = create_proc_entry("enable",0666,counter_dir[cpu][counter]);
            if(entry[cpu][counter][0]){
                //entry[cpu][counter][0]->data                     = &mix_cpu_counter[cpu][counter];
                //entry[cpu][counter][0]->read_proc        = topmc_enable_read;
                //entry[cpu][counter][0]->write_proc       = topmc_enable_write;
            }
            else {
                printk("topmc_mod: create procfile %s error\n",namebuf);
                topmc_proc_clean();
                ret = -ENOMEM;
                return ret;
            }

            entry[cpu][counter][1]   = proc_create_data("event",0,counter_dir[cpu][counter], &topmc_event_fops, &mix_cpu_counter[cpu][counter]);
			//entry[cpu][counter][1]   = create_proc_entry("event",0666,counter_dir[cpu][counter]);
            if(entry[cpu][counter][1]){
                //entry[cpu][counter][1]->data                     = &mix_cpu_counter[cpu][counter];
                //entry[cpu][counter][1]->read_proc        = topmc_event_read;
                //entry[cpu][counter][1]->write_proc       = topmc_event_write;
            }
            else {
                printk("topmc_mod: create procfile %s error\n",namebuf);
                topmc_proc_clean();
                ret = -ENOMEM;
                return ret;
            }
            entry[cpu][counter][2]   = proc_create_data("value",0,counter_dir[cpu][counter], &topmc_value_fops, &mix_cpu_counter[cpu][counter]);
            //entry[cpu][counter][2]   = create_proc_entry("value",0666,counter_dir[cpu][counter]);
            if(entry[cpu][counter][2]){
                //entry[cpu][counter][2]->data                     = &mix_cpu_counter[cpu][counter];
                //entry[cpu][counter][2]->read_proc        = topmc_value_read;
                //entry[cpu][counter][2]->write_proc       = topmc_value_write;
            }
            else {
                printk("topmc_mod: create procfile %s error\n",namebuf);
                topmc_proc_clean();
                ret = -ENOMEM;
                return ret;
            }
        }
    }

//    topmc_enable_rdpmc();
#ifdef TOPMC_PER_SECOND
    topmc_value_read_callable = &topmc_value_read_callable_impl;
#endif
#endif
    return ret;
}



void __exit topmc_cleanup(void )
{
	printk("+->topmc_mod: unloaded\n");
	topmc_proc_clean();


}

module_init( topmc_init );
module_exit( topmc_cleanup );


