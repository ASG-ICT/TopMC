#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/fcntl.h>
#include <linux/sched.h>

#include <linux/mm.h>
#include <linux/kdev_t.h>
#include <linux/pci.h>
#include <asm/page.h>
#include <asm/uaccess.h>
#include <asm/msr.h>
#include <asm/delay.h>

#include <linux/spinlock.h>
#include <linux/init.h>
#include <linux/slab.h>	
#include <asm/io.h>       //for virt_to_phys
#include <asm/pgalloc.h>
#include <asm/proto.h>
#include <asm/pgtable.h>
#include <asm/tlb.h>
#include <asm/fixmap.h>
#include <linux/spinlock.h>

#include "topmc_trace.h"


#define TOPMC_TRACE_ORDER    0     /* one page at a time */

//#define TOPMC_TRACE_PAGENUM  256   //1Mbytes
//#define TOPMC_TRACE_PAGENUM  512   //2Mbytes
//#define TOPMC_TRACE_PAGENUM  2048  //8Mbytes
//#define TOPMC_TRACE_PAGENUM  4096 //16MBytes
//#define TOPMC_TRACE_PAGENUM  8192 //32MBytes
#define TOPMC_TRACE_PAGENUM    16384//64MBytes

#ifndef  TOPMC_TRACE_MAJOR
#define TOPMC_TRACE_MAJOR 0
#endif

#define  BUF_START_OFFSET                  (1<<20)//1M

#define USE_IOREMAP
#ifdef USE_IOREMAP
static char *ioremap_virt_addr = NULL;
#endif

extern void  (*printk_for_trace)(void *ptr, size_t size); 
//void  (*printk_for_trace)(void *ptr, size_t size); 
extern u64 topmc_value_read_callable(unsigned short cpu, unsigned short counter);

#define USE_TOPMC
#ifdef USE_TOPMC

/*
extern int topmc_start_trace(void);
extern int topmc_stop_trace(void);
extern int topmc_stop_and_clear_trace(void);
*/
extern int topmc_schd_start_trace(void);
extern int topmc_schd_stop_trace(void);
extern int topmc_schd_stop_and_clear_trace(void);
extern int topmc_sys_usr_start_trace(void);
extern int topmc_sys_usr_stop_trace(void);
/*
int topmc_start_trace(void)
{
	int ret = -1;
	printk("topmc_start_trace..\n");
	ret = 0;
	
	return ret;
}

int topmc_stop_trace(void)
{
	int ret = -1;
	printk("topmc_stop_trace...\n");
	ret = 0;
	
	return ret;
}
int topmc_stop_and_clear_trace(void)
{
	int ret = -1;
	printk("topmc_stop_and_clear_trace...\n");
	ret = 0;
	
	return ret;
}
*/
#endif



//struct semaphore my_printk_sem;    /* Mutual exclusion for topmc_trace_printk*/
unsigned int                rand_off = 0;
unsigned long long hmtt_sync_cnt = 0;
//------------------------------------------------------------------//
struct topmc_trace_dev 
{
#ifdef USE_IOREMAP
    char   *buffer;
#else
    void   **buffer;  /* Pointer to first quantum set */
#endif
    int    vmas;      /* active mappings */
    int    order;
    int    pagenum;   /* amount of pages stored here */
    int    size;
    wait_queue_head_t   readq,writeq;
    int    readptr,writeptr;
    int    readsum,writesum;
    int    mode;      /*0 means "override",1 means "stop write"*/
    struct semaphore sem;    /* Mutual exclusion for mmap */
    struct semaphore  semq;  /*Mutual exclusion for mapq */
    struct cdev cdev;	     /* Char device structure*/
};

extern int  topmc_trace_major;
extern int  topmc_trace_minor;
extern int  topmc_trace_pagenum;
extern int  topmc_trace_order;

//------------------------------------------------------------------//
struct topmc_trace_dev *topmc_trace_device;

int topmc_trace_major   = TOPMC_TRACE_MAJOR;
int topmc_trace_minor   = 0;
int topmc_trace_pagenum = TOPMC_TRACE_PAGENUM;
int topmc_trace_buf_size  = (TOPMC_TRACE_PAGENUM << 12);
int topmc_trace_order   = TOPMC_TRACE_ORDER;

struct file* trace_fp = NULL;

module_param(topmc_trace_major, int, 0);
module_param(topmc_trace_minor, int, 0);
module_param(topmc_trace_pagenum, int, 0);
module_param(topmc_trace_order, int, 0);

MODULE_AUTHOR("Bingo");
MODULE_LICENSE("Dual BSD/GPL");

/*for ioremap test */
static unsigned long long ioremap_mem_start = 7200;
static unsigned long long ioremap_mem_size  = 63;
/*end test */
static unsigned long long ioremap_buf_start = 7300;
static unsigned long long ioremap_buf_size  = 65;



void  topmc_trace_printk_no_lock(void *ptr, size_t size);
inline void  topmc_trace_printk(void *ptr, size_t size)
{
	topmc_trace_printk_no_lock(ptr,size);
}

#ifdef USE_IOREMAP
void ioremap_write_test(void)
{
	int i;
	int *buf_readptr =  (int*)(topmc_trace_device->buffer + 4);
	int *buf_writeptr = (int*)(topmc_trace_device->buffer);

	printk("ioremap_write_test\n");

	if(ioremap_virt_addr)
	{
		printk("remap_virt_addr not NULL\n");
		//        for(i=0x100000; i<(63<<20); i++)
		//            ioremap_virt_addr[i] = i % 256;

		printk("readptr: %d\n",topmc_trace_device->readptr);
		printk("writeptr: %d\n",topmc_trace_device->writeptr);
		printk("buf_readptr: %d\n",(*buf_readptr));
		printk("buf_writeptr: %d\n",(*buf_writeptr));

		for(i=10; i<(32<<20); i++)
		{
			//tmp_glb = ioremap_virt_addr[0x100000+i];
			topmc_trace_device->buffer[i] = i % 256;
			topmc_trace_device->writeptr = topmc_trace_device->writeptr +1;
		}
		(*buf_writeptr) = topmc_trace_device->writeptr;
		printk("readptr: %d\n",topmc_trace_device->readptr);
		printk("writeptr: %d\n",topmc_trace_device->writeptr);
		printk("buf_readptr: %d\n",(*buf_readptr));
		printk("buf_writeptr: %d\n",(*buf_writeptr));
	}
}
#endif
//-------------------------write trace to file-----------------------//
void write_trace_to_buffer(void)
{
	char trace_buffer[5];
//	unsigned int i=0;
	unsigned long i=0;
	unsigned long j =0;
	unsigned long k =0;

	while(i++ < 1000000000)
	{
		if(i%200000000 == 0)
			printk("write trace: i=%ld\n",i);
		while(j++ <1000000000)
			while(k++ < 1000000000)
			{
				trace_buffer[0] = 0x55;
				trace_buffer[1] = 0x44;
				trace_buffer[2] = 0x33;
				trace_buffer[3] = 0x22;
				trace_buffer[4] = 0x11;
				printk_for_trace(trace_buffer,5);
			}
	}
}

void write_trace_to_file(void)
{
	mm_segment_t oldfs;
	int len;
	int item;
	int rest;
	//int i;

	printk("write_trace_to_file\n");
	printk("Write_ptr = %x\n", topmc_trace_device->writeptr);

	item=(topmc_trace_device->writeptr) / (int)(PAGE_SIZE);
	rest=(topmc_trace_device->writeptr) % (int)(PAGE_SIZE);
	if(rest > 0)
		item ++;

	oldfs = get_fs();
	set_fs(get_ds());
#ifdef USE_IOREMAP
	len = trace_fp->f_op->write(trace_fp,topmc_trace_device->buffer,topmc_trace_device->size, &trace_fp->f_pos);
	if(len < 0)
		printk("write file failure!\n");
#else
	for(i=0; i<item; i++){
		len = trace_fp->f_op->write(trace_fp,(unsigned char *)(topmc_trace_device->buffer[i]),(int)PAGE_SIZE,&trace_fp->f_pos);
		if(len < 0)
			printk("write file failure!\n");
	}
#endif //USE_IOREMAP
	set_fs(oldfs);

	filp_close(trace_fp, NULL);
}

void reset_trace_buffer(void)
{
	int *buf_readptr =  (int*)(topmc_trace_device->buffer + 4);
	int *buf_writeptr = (int*)(topmc_trace_device->buffer);


	*buf_readptr = BUF_START_OFFSET;
	*buf_writeptr = BUF_START_OFFSET;
	topmc_trace_device->writeptr = BUF_START_OFFSET;
	topmc_trace_device->readptr = BUF_START_OFFSET;
}


ssize_t topmc_trace_read (struct file *filp, char __user *buf, size_t count, loff_t *pos)
{
	int *buf_readptr =  (int*)(topmc_trace_device->buffer + 4);
	int *buf_writeptr = (int*)(topmc_trace_device->buffer);

	printk_for_trace = &topmc_trace_printk;

#ifdef USE_IOREMAP
	trace_fp = filp_open("/topmc_trace",O_CREAT|O_WRONLY|O_TRUNC,0600);
	if(trace_fp == NULL){
		printk("open hmtt_topmc_trace failure!\n");
		return -1;
	}
#endif
	*buf_readptr = BUF_START_OFFSET;
	*buf_writeptr = BUF_START_OFFSET;
	topmc_trace_device->writeptr = BUF_START_OFFSET;
	topmc_trace_device->readptr = BUF_START_OFFSET;

	printk("**********************************************\n");
	printk("trace file opened!\n");
	printk("topmc_trace_read called!\n");
	printk("topmc_trace_printk installed!\n");
	printk("**********************************************\n\n");


	return 0; /* EOF */
}

ssize_t topmc_trace_write (struct file *filp, const char __user *buf, size_t count, loff_t *pos)
{
	int command;

	if(count !=4){
		printk("parameter error,please chech it!\n");
		return count;
	}

	if(copy_from_user(&command,buf,count)){
		printk("copy from user failure!\n");
		return count;
	}

	//printk("we get [%d] len[%d]\n",command,count);

	switch(command)
	{
		case TOPMC_END_AND_DUMP_TRACE:
#ifdef USE_IOREMAP
			write_trace_to_file();
#endif
			break;

		case TOPMC_WRITE_TRACE_TEST:
#ifdef USE_IOREMAP
			write_trace_to_buffer();
#endif
		case TOPMC_RESET_BUFFER:
			reset_trace_buffer();
			break;

#ifdef USE_TOPMC
		/*
		case TOPMC_START_TRACE:
			topmc_start_trace();
			break;
		case TOPMC_STOP_TRACE:
			topmc_stop_trace();
			break;
		case TOPMC_STOP_AND_CLEAR_TRACE:
			topmc_stop_and_clear_trace();
			break;
		*/
                case TOPMC_SCHD_START_TRACE:
                        topmc_schd_start_trace();
                        break;
                case TOPMC_SCHD_STOP_TRACE:
                        topmc_schd_stop_trace();
                        break;
                case TOPMC_SCHD_STOP_AND_CLEAR_TRACE:
                        topmc_schd_stop_and_clear_trace();
                        break;

                case TOPMC_SYS_USR_START_TRACE:
                        topmc_sys_usr_start_trace();
                        break;
                case TOPMC_SYS_USR_STOP_TRACE:
                        topmc_sys_usr_stop_trace();
                        break;
#endif

		case CMD_IOREMAP_WRITE_TEST:
			ioremap_write_test();
			break;
		default: 
			printk("bad parameter!\n");
			break;
	}
	return count; /* succeed, to avoid retrial */
}

int topmc_trace_open (struct inode *inode, struct file *filp)
{
	struct topmc_trace_dev *dev; /* device information */

	/*  Find the device */
	dev = container_of(inode->i_cdev, struct topmc_trace_dev, cdev);

	/* and use filp->private_data to point to the device data */
	filp->private_data = dev;

	return 0;
}

int topmc_trace_release (struct inode *inode, struct file *filp)
{
	//printk_for_trace=0;
	return 0;
}


int topmc_trace_mmap(struct file *filp, struct vm_area_struct *vma)
{
	/* don't do anything here: "nopage" will set up page table entries */

	unsigned long offset = (vma->vm_pgoff << PAGE_SHIFT);
	unsigned long size = vma->vm_end - vma->vm_start;

	printk("topmc_trace: in mmap()\n");
	printk("topmc_trace: size=%lx\n", size);

	if (size > topmc_trace_device->size){
		printk("Out of Device memory\n");
		return  - ENXIO;
	}

	offset += (ioremap_buf_start << 20);
	vma->vm_private_data = filp->private_data;
	vma->vm_flags |= /*VM_RESERVED*/VM_DONTDUMP;

	if(remap_pfn_range(vma, vma->vm_start, offset>>PAGE_SHIFT, size, vma->vm_page_prot)){
		printk("remap page range failed\n");
		return - ENXIO;
	}

	printk(" topmc_trace: mmap ok\n");
	return 0;
}

struct file_operations topmc_trace_fops = 
{
	.owner = THIS_MODULE,
	.open  = topmc_trace_open,	
	.read  = topmc_trace_read,
	.write = topmc_trace_write,
	.mmap  = topmc_trace_mmap,
	.release = topmc_trace_release,
};

#ifdef USE_IOREMAP
void copy_trace_to_buffer(void *ptr, size_t size)
{
	int data_part1, data_part2, rest_space, offset;
	int *buf_readptr =  (int*)(topmc_trace_device->buffer + 4);
	int *buf_writeptr = (int*)(topmc_trace_device->buffer);

	//printk("ioremap: input copy_trace_to_buffer!\n"); 
	//printk("buffer_size: %d\n",topmc_trace_device->size);
	//printk("trace size: %d\n", size);
	offset = *buf_writeptr; //topmc_trace_device->writeptr;
	rest_space = topmc_trace_device->size - offset; //topmc_trace_device->writeptr;
	data_part1 = (size <= rest_space) ? size: rest_space;
	data_part2 = size - data_part1;

	//copy data part 1
	//printk("copy data_part1\n");
	if(data_part1 > 0) {
		memcpy(topmc_trace_device->buffer + offset, ptr, data_part1);

		if((offset < *buf_readptr) && (offset+data_part1) >= *buf_readptr)
			printk("Buffer Overflow\n");

		offset += data_part1;
		ptr += data_part1;

		if(offset == topmc_trace_device->size){
			printk("Buffer Full\n");
			offset = BUF_START_OFFSET;
		}
	}
	//printk("copy data_part2\n");
	if(data_part2 > 0) { 
		memcpy(topmc_trace_device->buffer + offset, ptr, data_part2);

		if((offset < *buf_readptr) && (offset+data_part1) >= *buf_readptr)
			printk("Buffer Overflow\n");

		offset += data_part2;
	}

	(*buf_writeptr) = offset;
	topmc_trace_device->writeptr = (*buf_writeptr);
}

#else
void copy_trace_to_buffer(void *ptr,size_t size)
{
	//    int i;
	int page_num,page_used,page_rest;
	int data_part1,data_part2,data_part3;
	int *buf_readptr =  (int*)(topmc_trace_device->buffer[0] + 4);
	int *buf_writeptr = (int*)(topmc_trace_device->buffer[0]);

	page_num  = (topmc_trace_device->writeptr) / (int)(PAGE_SIZE); 
	page_used = (topmc_trace_device->writeptr) % (int)(PAGE_SIZE); 
	page_rest = (int)(PAGE_SIZE) - page_used;

	data_part1 = (size >= page_rest) ? page_rest : size; 
	data_part2 = (size - data_part1) / (int)(PAGE_SIZE);
	data_part3 = (size - data_part1) % (int)(PAGE_SIZE);

	printk("copy data part1\n");
	//copy data part 1
	if(data_part1 > 0) {
		memcpy(topmc_trace_device->buffer[page_num]+page_used,ptr,data_part1);
		topmc_trace_device->writeptr += data_part1;
		if(topmc_trace_device->writeptr >= *buf_readptr)
			printk("Buffer Overflow\n");
		ptr += data_part1;
		if(size >= page_rest) {
			page_num ++;
			//check overflow
			if(topmc_trace_device->writeptr == topmc_trace_buf_size){
				printk("Buffer Full\n");
				topmc_trace_device->writeptr = BUF_START_OFFSET;
				page_num = 0;
			}
		}
	}

	 printk("copy data part2\n");
	//copy data part 2, each one page
	for(i=0; i<data_part2; i++) {
		memcpy(topmc_trace_device->buffer[page_num],ptr,(int)(PAGE_SIZE));
		topmc_trace_device->writeptr += (int)(PAGE_SIZE);
		if(topmc_trace_device->writeptr >= *buf_readptr)
			printk("Buffer Overflow\n");
		ptr += (int)(PAGE_SIZE);
		page_num ++;
		//check overflow
		if(topmc_trace_device->writeptr == topmc_trace_buf_size){
			printk("Buffer Full\n");
			topmc_trace_device->writeptr = BUF_START_OFFSET;
			page_num = 0;
		}
	}

	//copy data part3
	if(data_part3 > 0) { 
		memcpy(topmc_trace_device->buffer[page_num],ptr,data_part3);
		topmc_trace_device->writeptr += data_part3;
		if(topmc_trace_device->writeptr >= *buf_readptr)
			printk("Buffer Overflow\n");
		//check overflow
		if(topmc_trace_device->writeptr == topmc_trace_buf_size){
			printk("Buffer Full\n");
			topmc_trace_device->writeptr = BUF_START_OFFSET;
			page_num = 0;
		}
	}

	*buf_writeptr = topmc_trace_device->writeptr;
}
#endif //USE_IOREMAP

int in_dma_processing = 0;

void  topmc_trace_printk_no_lock(void *ptr, size_t size)
{
	copy_trace_to_buffer(ptr, size);
}

/*
inline void topmc_trace_printk(void *ptr, size_t size)
{
    topmc_trace_printk_no_lock(ptr,size);
}
*/

/*
 * Set up the char_dev structure for this device.
 */
static void topmc_trace_setup_char_dev(struct topmc_trace_dev *dev)
{
	int err; 
	int devno;

	devno = MKDEV(topmc_trace_major, topmc_trace_minor );
	cdev_init(&dev->cdev, &topmc_trace_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &topmc_trace_fops;
	err = cdev_add (&dev->cdev, devno, 1);
	/* Fail gracefully if need be */
	if (err)
		printk("Error adding topmc_trace to char device!\n");
}

int topmc_trace_buf_init(void)
{
	//int i;
	int result;
	//unsigned long buff_virt_addr;
	//unsigned long buff_phys_addr;

	topmc_trace_device = kmalloc(sizeof(struct topmc_trace_dev), GFP_KERNEL);
	if (!topmc_trace_device){
		result = -ENOMEM;
		printk("Can't allocate memory for topmc_trace_device");
		goto fail;  
	}
	memset(topmc_trace_device, 0, sizeof(struct topmc_trace_dev));

	sema_init (&topmc_trace_device->sem, 1);	
	init_waitqueue_head(&topmc_trace_device->readq);
	init_waitqueue_head(&topmc_trace_device->writeq);
	//init_MUTEX(&topmc_trace_device->semq);
	sema_init (&topmc_trace_device->semq, 1);
	topmc_trace_device->readptr = BUF_START_OFFSET;
	topmc_trace_device->writeptr = BUF_START_OFFSET;
	topmc_trace_device->readsum = 0;
	topmc_trace_device->writesum = 0;
	topmc_trace_device->mode = 0;

#ifdef USE_IOREMAP
	topmc_trace_device->order = topmc_trace_order;
	topmc_trace_device->size = ioremap_buf_size << 20;
	topmc_trace_device->pagenum = (topmc_trace_device->size >> PAGE_SHIFT);
	printk("**********************************************\n");
	printk("ioremap:topmc_trace_buffer size is %d Mbytes\n",topmc_trace_device->size >> 20);

	topmc_trace_device->buffer = (char*) ioremap_cache(ioremap_buf_start << 20,ioremap_buf_size << 20);
	if(!topmc_trace_device->buffer)
	{
		printk("ioremap_cache: failed\n");
		goto fail;
	}
	memset(topmc_trace_device->buffer, 0, topmc_trace_device->size);

	memcpy(topmc_trace_device->buffer,     &topmc_trace_device->writeptr, sizeof(int));
	memcpy(topmc_trace_device->buffer + 4, &topmc_trace_device->readptr, sizeof(int));
	printk("ioremap_cache: topmc_trace_buffer ok\n");;
#else
	topmc_trace_device->order = topmc_trace_order;
	topmc_trace_device->pagenum = topmc_trace_pagenum;
	topmc_trace_device->size = topmc_trace_pagenum*PAGE_SIZE;
	printk("**********************************************\n");
	printk("kmalloc:topmc_trace_buffer size is %d Mbytes\n",topmc_trace_device->size >> 20);

	topmc_trace_device->buffer = kmalloc(topmc_trace_device->pagenum * sizeof(void *), GFP_KERNEL);
	if (!topmc_trace_device->buffer){
		result = -ENOMEM;	
		printk(KERN_ALERT "Can't allocate buffer for topmc_trace_device"); 
		goto fail;
	}
	memset(topmc_trace_device->buffer, 0, topmc_trace_device->pagenum * sizeof(void *));
	for(i=0; i<topmc_trace_device->pagenum; i++)
	{
		topmc_trace_device->buffer[i] =(void *)__get_free_pages(GFP_KERNEL, topmc_trace_device->order);
		if (!topmc_trace_device->buffer[i])
		{
			result = -ENOMEM;	
			printk(KERN_ALERT "Can't allocate buffer[%d] for topmc_trace_device",i); 
			goto fail;
		}
		//memset(topmc_trace_device->buffer[i], 0, PAGE_SIZE << topmc_trace_device->order);
		memset(topmc_trace_device->buffer[i], '0'+i%10, PAGE_SIZE << topmc_trace_device->order);
		printk("get_free_pages: topmc_trace_buffer ok\n");;
	}
#endif //USE_IOREMAP    


#ifdef USE_IOREMAP
	ioremap_virt_addr = ioremap(ioremap_mem_start << 20,ioremap_mem_size << 20);
	if(ioremap_virt_addr){
		printk("ioremap: ioremap_virt_addr = 0x%llx\n", (unsigned long long)ioremap_virt_addr);
	} else goto fail;
#endif

	return 1;
fail:
	return 0;
}

void topmc_trace_cleanup_module(void)
{
	//int i;
	dev_t devno = MKDEV(topmc_trace_major, topmc_trace_minor);
	printk("**********************************************\n");
	printk("topmc_trace module uninstall\n");
	printk("**********************************************\n\n");

#ifdef USE_IOREMAP
	if(ioremap_virt_addr) 
	{
		iounmap(ioremap_virt_addr);
		printk("iounmap ioremap_virt_addr!\n");
	}
#endif

	if (topmc_trace_device) 
	{
		cdev_del(&topmc_trace_device->cdev);
#ifdef USE_IOREMAP
		if(topmc_trace_device->buffer){
			iounmap(topmc_trace_device->buffer);
			printk("iounmap topmc_trace_device->buffer!\n");
		}
#else
		if(topmc_trace_device->buffer)
		{
			for(i=0;i<topmc_trace_device->pagenum;i++)
				if(topmc_trace_device->buffer[i])
					free_pages((unsigned long)(topmc_trace_device->buffer[i]),topmc_trace_device->order);
			kfree(topmc_trace_device->buffer);
		}
#endif //USE_IOREMAP
		kfree(topmc_trace_device);
	}

	unregister_chrdev_region(devno, 1);
}

int topmc_trace_init_module(void)
{
	int result;
	dev_t dev = 0;

	printk("\n\n\n++++++++++++++++++++++++++++++++++++\n");    
	printk("Init Kernel_Trace Module\n");    
	if (topmc_trace_major){
		dev = MKDEV(topmc_trace_major, topmc_trace_minor);
		result = register_chrdev_region(dev, 1, "topmc_trace");
	} 
	else{
		result = alloc_chrdev_region(&dev, topmc_trace_minor,1,"topmc_trace");
		topmc_trace_major = MAJOR(dev);
	}

	if (result < 0) {
		printk(KERN_WARNING "topmc_trace: can't get major %d\n", topmc_trace_major);
		return result;
	}

	//initial topmc_trace device buffer
	if(!topmc_trace_buf_init())
		goto fail;

	topmc_trace_setup_char_dev(topmc_trace_device);		 

	printk("topmc_trace_major=%d\n",topmc_trace_major);
	printk("topmc_trace_minor=%d\n",topmc_trace_minor);
	printk("topmc_trace_dev=%d\n",dev);
	printk("**********************************************\n\n");

	return 0; /* succeed */

fail:
	topmc_trace_cleanup_module();
	return result;
}

module_init(topmc_trace_init_module);
module_exit(topmc_trace_cleanup_module);

