/*****************************************************************
* Extract Topmc Trace and Convert it into text format
*
* @Date 2010-05-28
* @Author Yongbing Huang 
*****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

// Number of Performance Counters
#define PMC_CNT 10
// Length of each trace line
#define FINE_BUF_LENGTH 48

typedef struct topmc_trace {
	unsigned int pmc_counter[PMC_CNT];
	unsigned short pid;
//	unsigned long pc;
	char core;
	unsigned int timestamp;
	char end;
}topmc_trace_t;


void convert_binary_to_text(topmc_trace_t trace, FILE* fd_out)
{
	char text_buffer[64];
	unsigned int pmc_index = 0;

	while(pmc_index < PMC_CNT)
	{
		memset(text_buffer, 0, 64);
		sprintf(text_buffer, "%lu ", (unsigned long)trace.pmc_counter[pmc_index]);
		pmc_index++;
		fwrite(text_buffer, 1, strlen(text_buffer), fd_out);
	}
	memset(text_buffer, 0,64);
	sprintf(text_buffer, "%d ", trace.pid);
	fwrite(text_buffer, 1, strlen(text_buffer), fd_out);

	/*
	memset(text_buffer, 0,64);
	sprintf(text_buffer, "%d ", trace.pid);
	fwrite(text_buffer, 1, strlen(text_buffer), fd_out);
	*/

	memset(text_buffer, 0,64);
	sprintf(text_buffer, "core%d ", (unsigned int)trace.core);
	fwrite(text_buffer, 1, strlen(text_buffer), fd_out);

	memset(text_buffer, 0,64);
	sprintf(text_buffer, "%lu\n", (unsigned long)trace.timestamp);
	fwrite(text_buffer, 1, strlen(text_buffer), fd_out);
}

void display_usage(void)
{
	printf("Usage: analyze input_binary_trace_file output_text_trace_file\n");
}

int main(int argc, char** argv)
{
	int ret = -1;
//	char input_filename[64];
//	char output_filename[64];
	char* trace_buf;
	FILE* fd_in;
	FILE* fd_out;
	unsigned int* pmc_ptr;
	unsigned short* pid_ptr;
//	unsigned long* pc_ptr;
	char* core_ptr;
	unsigned int* timestamp_ptr;
	char* end_ptr;
	

	unsigned int len = 0;
	unsigned int ptr_index = 0;
	int pmc_index = 0;

	topmc_trace_t trace;

	if(argc < 3) {
		display_usage();
		return 0;
	}
	
//	strcpy(filename, argv[1]);
	
	if( (fd_in = fopen(argv[1], "r")) == NULL ){
		fprintf(stderr, "Open input file %s error!\n", argv[1]);
		return 0;
	}
	
	if( (fd_out = fopen(argv[2], "w")) == NULL ){
		fprintf(stderr, "Open output file %s error!\n", argv[2]);
		fclose(fd_in);
		return 0;
	}
	
	/*
	 Read data from input file, convert them into text format and store back to  output file
	*/
	while(1) {
		ptr_index = 0;
		pmc_index = 0;
		trace_buf = (char *)malloc(FINE_BUF_LENGTH);
		memset(trace_buf, 0, FINE_BUF_LENGTH);
		len = fread(trace_buf, sizeof(char), FINE_BUF_LENGTH, fd_in);

		if( len == 0)
		{
			return 0;
		}
		if (len < FINE_BUF_LENGTH) {
			printf("len: %d\n", len);
			fprintf(stderr, "Read trace from input file error!\n");
			return 0;
		}
		
		while(pmc_index < PMC_CNT)
		{
			pmc_ptr = (unsigned int*)(trace_buf + ptr_index);
			trace.pmc_counter[pmc_index] = *pmc_ptr;
			ptr_index += sizeof(unsigned int);
			pmc_index++;
		}
			
		pid_ptr = (unsigned short*)(trace_buf + ptr_index);
		trace.pid = *pid_ptr;
		ptr_index += sizeof(unsigned short);

	/*
		pc_ptr = (unsigned long*)(trace_buf + ptr_index);
		trace.pc = *pc_ptr;
		ptr_index += sizeof(unsigned long);
	*/

		core_ptr = (char*)(trace_buf + ptr_index);
		trace.core = *core_ptr;
		ptr_index += sizeof(char);

		timestamp_ptr = (unsigned int*)(trace_buf + ptr_index);
		trace.timestamp = *timestamp_ptr;
		ptr_index += sizeof(unsigned int);

		end_ptr = (char*)(trace_buf + ptr_index);
		trace.end = *end_ptr;

		if( trace.end != 'e')
		{
			fprintf(stderr, "Warning, trace file may be broken.\n");
		}

		convert_binary_to_text(trace, fd_out);
	}

	fclose(fd_out);
	fclose(fd_in);
	return 1;
}
