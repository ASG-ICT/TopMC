/*
	This file contains all the APIs that TOPMC can provide for programmers.
*/

#ifndef TOPMC_API_H
#define TOPMC_API_H

#include <stdint.h>

/*-----------------------Based on proc file system---------------------------*/
#define MAX_PMCS 8
#define MAX_INCORE_PMCS 4
#define MAX_UNCORE_PMCS 10

#define MAX_CPU 8
#define CPU_NUM 4

struct topmc_stats {
	uint64_t last[MAX_CPU][MAX_PMCS];
};


void topmc_init(int8_t incore_num, int8_t uncore_num);

void topmc_close(void);


int topmc_prof_begin(struct topmc_stats* begin);

//int topmc_prof_begin(int core, int uncore, int value...);

int topmc_prof_end(struct topmc_stats* begin, struct topmc_stats* end, struct topmc_stats* sum);
/*-------------------------------------------------------------------------*/
/*-----------------------Based on RDPMC------------------------------------*/
// ----------------------------------------------------------------------------
#define SERIAL              do { __asm__ __volatile__ ("cpuid \n\t" ::: "ax", "bx", "cx", "dx"); } while(0) 
#define RDTSC(lo, hi)       do { __asm__ __volatile__ ("rdtsc \n\t" :"=a"(lo), "=d"(hi)); } while(0)
#define RDPMC(cnt, lo, hi)  do { __asm__ __volatile__ ("rdpmc \n\t" : "=a"(lo), "=d"(hi) : "c"(cnt)); } while(0) 

#define READ_TSC(l, h)      do { SERIAL; RDTSC(*l, *h);    SERIAL; } while(0)
//#define READ_PMC(c, l, h)   do { SERIAL; RDPMC(c, *l, *h); SERIAL; } while(0)
#define READ_PMC(c, l, h)   do { RDPMC(c, *l, *h); } while(0)


#define CLFLUSH(addr) do {                  \
    SERIAL;                                 \
    __asm__ __volatile__ (                  \
            "mfence     \n\t"               \
            "clflush %0 \n\t"               \
            "mfence     \n\t"               \
            :                               \
            :"m"(addr)                      \
            );                              \
    SERIAL;                                 \
} while(0)


#define tprof(counter, value) do {		\
	uint32_t lo, hi;			\
	READ_PMC(counter, &lo, &hi);		\
	value = (uint64_t)(((uint64_t)hi << 32) | lo);	\
} while(0)

#define tprofd(counter, diff, last) do { 	\
	diff = last;				\
	tprof(counter, last);			\
	diff = last - diff;			\
} while(0)
	
void tprof_init(int8_t incore_num, int8_t uncore_num);
void tprof_close(void);

/*-------------------------------------------------------------------------*/
#define DEBUG
#if defined(DEBUG)
#define DPRINTF printf
#else
#define DPRINTF 
#endif

#endif
