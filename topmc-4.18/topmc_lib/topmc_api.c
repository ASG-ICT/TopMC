/*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "include/topmc.h"
#include "include/rdpmc.h"

static uint8_t incore_pmc;
static uint8_t uncore_pmc;
static int topmc_prof(struct topmc_stats* stats);

void tprof_init(int8_t incore_num, int8_t uncore_num)
{
	return topmc_init(incore_num, uncore_num);
}

void topmc_init(int8_t incore_num, int8_t uncore_num)
{
	char* cInfo[] = {"sh", "/home/huangyb/topmc/topmc-1.3/topmc_script/set_event_nehalem.sh", 0};

	if((incore_num > MAX_INCORE_PMCS) || (incore_num < 0))
		incore_pmc = MAX_INCORE_PMCS;
	else
		incore_pmc = incore_num;

	if((uncore_num > MAX_UNCORE_PMCS) || (uncore_num < 0))
		uncore_pmc = MAX_UNCORE_PMCS;
	else
		uncore_pmc = uncore_num;

//	execvp("sh", cInfo);
}

void tprof_close(void)
{
	topmc_close();
}
void topmc_close(void)
{
	char* cInfo[] = {"sh", "/home/bingo/topmc-1.3/topmc_script/end_profile.sh", 0};

//	execvp("sh", cInfo);
}

static int topmc_prof(struct topmc_stats* stats)
{
	char fileIter[255];
	int nCpu;
	int nCounter;

	FILE* fd_value;
	uint64_t nValue;

	for(nCpu = 0; nCpu < CPU_NUM; nCpu++)
	{
		sprintf(fileIter, "/proc/topmc/core0%d\n", nCpu);
		for(nCounter = 0; nCounter < incore_pmc; nCounter++)
		{
			sprintf(fileIter, "/proc/topmc/core0%d/incore_counter%d/value", nCpu, nCounter);
	//		DPRINTF("fileIter: %s\n", fileIter);
			if ((fd_value = fopen(fileIter, "r")) < 0)
			{
				DPRINTF("fd_value: %d\n", fd_value);
				DPRINTF("Error open file: %s\n", fileIter);
				return -1;
			}
			fscanf(fd_value, "%llu\n", &nValue);
			stats->last[nCpu][nCounter] = nValue;
	//		DPRINTF("CPU: %d, Counter: %d: Value(%llu)\n", nCpu, nCounter, stats->last[nCpu][nCounter]);
			fclose(fd_value);
		}

		for(nCounter = incore_pmc; nCounter < uncore_pmc + incore_pmc; nCounter++)
		{
			sprintf(fileIter, "/proc/topmc/core0%d/uncore_counter%d/value", nCpu, nCounter - incore_pmc);
	//		DPRINTF("fileIter: %s\n", fileIter);
			if ((fd_value = fopen(fileIter, "r")) < 0)
			{
				DPRINTF("fd_value: %d\n", fd_value);
				DPRINTF("Error open file: %s\n", fileIter);
				return -1;
			}
			fscanf(fd_value, "%llu\n", &nValue);
			stats->last[nCpu][nCounter] = nValue;
	//		DPRINTF("CPU: %d, Counter: %d: Value(%llu)\n", nCpu, nCounter, stats->last[nCpu][nCounter]);
			fclose(fd_value);
		}
	}
	return 1;
	
}

int topmc_prof_begin(struct topmc_stats* begin)
{
	return topmc_prof(begin);
}
int topmc_prof_end(struct topmc_stats* begin, struct topmc_stats* end, struct topmc_stats* sum)
{
	int nCpu;
	int nCounter;
	int ret = -1;

	ret = topmc_prof(end);
	if(ret < 0)
		return ret;
	DPRINTF("*************************Sum***********************************\n");
	for(nCpu = 0; nCpu < CPU_NUM; nCpu++)
	{
		for(nCounter=0; nCounter < incore_pmc + uncore_pmc; nCounter++)
		{
			sum->last[nCpu][nCounter] = end->last[nCpu][nCounter] - begin->last[nCpu][nCounter];
			DPRINTF("CPU: %d, Counter: %d: Value(%llu)\n", nCpu, nCounter, sum->last[nCpu][nCounter]);
			//DPRINTF("CPU: %d, Counter: %d: Start Value(%llu)\n", nCpu, nCounter, begin->last[nCpu][nCounter]);
			//DPRINTF("CPU: %d, Counter: %d: End Value(%llu)\n", nCpu, nCounter, end->last[nCpu][nCounter]);
		}
	}
	DPRINTF("*************************Sum***********************************\n");
	return 1;
}


