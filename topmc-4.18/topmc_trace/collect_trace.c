#include <asm/unistd.h> 
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sched.h>
#include <signal.h>
#include <dirent.h>
#include "topmc_trace.h"	
#include <errno.h>

extern int errno;

//global variable
int ff, dev_size, buffer_size;  
char *buffer;
char filename[64];
FILE *fp, *fpid, *pp;
int   topmc_trace_offset;
int   trace_size;

int *dev_writeptr;
int *dev_readptr;

void kill_op(int signo);
void ctrl_c_op(int signo);

void kill_op(int signo)
{
	printf("[Topmc_Trace]  Entering kill -15 Handler\n");
	ctrl_c_op(signo);
}
/*
 * hanlde the Ctrl-C signal while kill the process
 */
void ctrl_c_op(int signo)
{
	int command, wr_cnt;

	printf("[Topmc_Trace]  Entering Ctrl-C Handler\n");

	//printf("readptr = %x, writeptr = %x\n", *dev_readptr - topmc_trace_offset, *dev_writeptr-topmc_trace_offset);

	if(*dev_readptr == topmc_trace_offset){
		fwrite(buffer + *dev_readptr, *dev_writeptr - topmc_trace_offset, 1, fp);
	} else if(*dev_readptr == topmc_trace_offset + buffer_size/2){
		if(*dev_writeptr < topmc_trace_offset + buffer_size/2){
			fwrite(buffer + *dev_readptr, buffer_size/2, 1, fp);
			fwrite(buffer + topmc_trace_offset, *dev_writeptr - topmc_trace_offset, 1, fp);
		} else {
			fwrite(buffer + *dev_readptr, *dev_writeptr - *dev_readptr, 1, fp);
		}
	} else {
		printf("Write File Error\n");
	}

	printf("readptr = %x, writeptr = %x\n", *dev_readptr - topmc_trace_offset, *dev_writeptr-topmc_trace_offset);

	command = TOPMC_RESET_BUFFER;
	wr_cnt = write(ff,&command,sizeof(int));

	if(wr_cnt != sizeof(int))
		printf("Reset Buffer Error\n");
	else
		printf("Reset Buffer OK\n");

	munmap(buffer,dev_size);
	close(ff);

	fclose(fp);
	printf("[Topmc_Trace]  Collect Topmc Trace OK.\n");

	exit(0);
}
	
int main(int argc, char **argv, char **env)
{
    int i;
    int m=0;
    int scount=0;
    unsigned int *pidbuf_num;
    char         *pidbuf;
    int          pid;
    int          sleep_time;
    int          trace_bw;
    int          last_writeptr;
    int          write_sum;
   
     if(argc != 3)
     {
         printf("Usage:./ page_table_dump filename time_interval\n");
         return 0;
     }
     memset(filename, 0, 64);
     strcpy(filename, argv[1]);
     strcat(filename, ".kt");
     if((fp = fopen(filename, "w+")) == NULL){
          printf("Open file %s error\n", filename);
          return 0;
     }
 
     sleep_time = atoi(argv[2]);
     if(sleep_time == 0)
         sleep_time = 80;

    /* 
     * Step.0 register sigaction to reponse Ctrl+C and kill
     */
    struct sigaction s;

    s.sa_handler = (void*)ctrl_c_op;
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;
    if(sigaction(SIGINT, &s, (struct sigaction*)NULL)){
        printf("register sigaction error\n");
        exit(0);
    }
    
    struct sigaction t;

    t.sa_handler = (void*)kill_op;
    sigemptyset(&t.sa_mask);
    t.sa_flags = 0;
    if(sigaction(SIGTERM, &t, (struct sigaction*)NULL)) {
	printf("register t sigaction error\n");
	exit(0);
    } 
    /*
     *  Step.1 Init pro device and malloc buffers to store traces
     */	

    ff = open("/dev/topmc_trace", O_RDWR);
    if( ff < 0 ){
        printf("open /dev/topmc_trace failed");
        return 0;
    }

    dev_size = 65 << 20; //16384*4096;//ioctl(ff,PRO_IOCQ_PAGENUM) * 4096;	  //get pro's buffer size

   
    buffer= mmap(0, dev_size, PROT_READ|PROT_WRITE, MAP_SHARED,ff,0);
    if ((long long)buffer < 0){
	printf("error in mmap\n");
        switch(errno){
            case EACCES: printf("EACCES\n"); break;
            case EAGAIN: printf("EAGAIN\n"); break;
            case EBADF: printf("EBADF\n"); break;
            case EINVAL: printf("EINVAL\n"); break;
            case ENFILE: printf("ENFILE\n"); break;
            case ENODEV: printf("ENODEV\n"); break;
            case ENOMEM: printf("ENOMEM\n"); break;
            case EPERM: printf("EPERM\n"); break;
            //case ETXTBSY: printf("ETXTBSY\n"); break;
            //case SIGSEGV: printf("SIGSEGV\n"); break;
            //case SIGBUS: printf("SIGBUS\n"); break;
        }

        return -1;
    }

    // dump existing page table of system
    buffer_size = dev_size - 0x100000; //16384*4096;//ioctl(ff,PRO_IOCQ_PAGENUM) * 4096;	  //get pro's buffer size
    topmc_trace_offset = 0x100000;
 
    /*
     *  Step.2 read trace from pro's buffer
     */	

    write_sum = 0;
    dev_writeptr = (int*)buffer;
    dev_readptr = (int*)(buffer + 4);
    last_writeptr = *dev_writeptr;
    while(1){     

        if(last_writeptr <= *dev_writeptr)
             trace_bw = ((*dev_writeptr - last_writeptr) / sleep_time) >> 10 ;
        else trace_bw = ((buffer_size - last_writeptr + *dev_writeptr) / sleep_time) >> 10;
        last_writeptr = *dev_writeptr;

        printf("readptr = %x, writeptr = %x\n", *dev_readptr - topmc_trace_offset, *dev_writeptr-topmc_trace_offset);
        if(*dev_readptr == topmc_trace_offset){
            if(*dev_writeptr >= topmc_trace_offset + buffer_size/2){
                fwrite(buffer + *dev_readptr, buffer_size/2, 1, fp);
                *dev_readptr = topmc_trace_offset + buffer_size/2;
                write_sum += buffer_size/2;
            }
        } else if(*dev_readptr == topmc_trace_offset + buffer_size/2){
            if(*dev_writeptr < topmc_trace_offset + buffer_size/2){
                fwrite(buffer + *dev_readptr, buffer_size/2, 1, fp);
                *dev_readptr = topmc_trace_offset;
                write_sum += buffer_size/2;
            }
        } else {
            printf("Write File Error\n");
        }

        printf("readptr = %x, writeptr = %x, bw=%d\n", *dev_readptr - topmc_trace_offset, *dev_writeptr-topmc_trace_offset, trace_bw);
        sleep(sleep_time);

   /*     if(write_sum >= buffer_size && trace_bw <= 512){
            sleep_time = 80;
        }
*/

    }//endof 	while(1)

 }
