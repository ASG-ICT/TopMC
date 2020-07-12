#ifndef _TOPMC_RDPMC_H_
#define _TOPMC_RDPMC_H_

//test overhead
//for READ_TSC: insn overhead 5, data store overhead 2
//for READ_PMC: insn overhead 6, data store overhead 2

// ----------------------------------------------------------------------------
#define SERIAL              do { __asm__ __volatile__ ("cpuid \n\t" ::: "ax", "bx", "cx", "dx"); } while(0) 
#define RDTSC(lo, hi)       do { __asm__ __volatile__ ("rdtsc \n\t" :"=a"(lo), "=d"(hi)); } while(0)
#define RDPMC(cnt, lo, hi)  do { __asm__ __volatile__ ("rdpmc \n\t" : "=a"(lo), "=d"(hi) : "c"(cnt)); } while(0) 

#define READ_TSC(l, h)      do { SERIAL; RDTSC(*l, *h);    SERIAL; } while(0)
#define READ_PMC(c, l, h)   do {  RDPMC(c, *l, *h); } while(0)
//#define READ_PMC(c, l, h)   do { SERIAL; RDPMC(c, *l, *h); SERIAL; } while(0)


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
	
// ----------------------------------------------------------------------------

#endif
