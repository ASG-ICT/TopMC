#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>

#include "topmc_trace.h"

void begin_topmc_trace(int fd)
{
	int command;
	int wr_cnt;

	command = TOPMC_SCHD_START_TRACE;
	//command = CMD_IOREMAP_WRITE_TEST;
	wr_cnt = write(fd, &command, sizeof(int));

	printf("begin_topmc_trace(): command:%d\n", command);	
	if(wr_cnt != sizeof(int))
		printf("Begin begin_topmc_trace: write 0 failure!\n");
	else
		printf("Begin begin_topmc_trace: write 0 success!\n");
/*	command = TOPMC_STOP_TRACE;
	wr_cnt = write(fd, &command, sizeof(int));
	command = TOPMC_STOP_AND_CLEAR_TRACE;
	wr_cnt = write(fd, &command, sizeof(int));
*/	
}

int main(int argc, char **argv)
{
	int fd;
	int cmd;
	char buf[4];
	char *ioremap_buf;
	int i,j,k;
	char ch;
	char* buffer;

	if(argc != 2)
	{
		printf("Usage: ./begin_trace num\n");
		printf("\n");
		printf("num = 0  topmc_trace_begin \n");
		printf("\n");

		return 0;
	}

	fd = open("/dev/topmc_trace",O_RDWR);
	if(fd < 0)
	{
		printf("can not open /dev/topmc_trace, errno = %d!\n", errno);
		return 0;
	} 

	read(fd,buf,4);
	cmd = atoi(argv[1]);

	//start trace
	if(cmd == 0)//sata_dma
		begin_topmc_trace(fd);
	else
		printf("param error!\n");

	close(fd);

	return 0;
}
