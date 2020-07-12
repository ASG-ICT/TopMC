#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <linux/unistd.h>

#include "topmc.h"
#include "probe.h"

static FILE* fd_log = NULL;

static uint64_t nCount_L3_Ref_Start, nCount_L3_Ref_End;
static uint64_t nCount_L3_Miss_Start, nCount_L3_Miss_End;
static uint64_t nCount_L2_Ref_Start, nCount_L2_Ref_End;
static uint64_t nCount_L2_Miss_Start, nCount_L2_Miss_End;

struct topmc_stats begin, end, sum;

static void openConn1(void) {
    int ret = -1;

    //printf("openconn1.\n");
    fd_log = open("data.log", O_CREAT | O_RDWR);
    if ((fd_log = fopen("data.log", "w+")) == NULL) {
	printf("open data log failed.\n");
	exit(-1);
    }
}

static void closeConn1(void) {
    char buf[256];

    tprof(0, nCount_L3_Ref_End);
    tprof(1, nCount_L3_Miss_End);
    tprof(2, nCount_L2_Ref_End);
    tprof(3, nCount_L2_Miss_End);
    topmc_prof_end(&begin, &end, &sum);
    printf("Cycles: %llu\n", nCount_L3_Ref_End - nCount_L3_Ref_Start);
    printf("L3_Ref: %llu\n", nCount_L3_Miss_End - nCount_L3_Miss_Start);
    printf("L2_Ref: %llu\n", nCount_L2_Ref_End - nCount_L2_Ref_Start);
    printf("L2_Miss: %llu\n", nCount_L2_Miss_End - nCount_L2_Miss_Start);
    sprintf(buf, "Cycles: %llu\n", nCount_L3_Ref_End - nCount_L3_Ref_Start);
    fwrite(buf, strlen(buf), 1, fd_log);
    sprintf(buf, "L3_Ref: %llu\n", nCount_L3_Miss_End - nCount_L3_Miss_Start);
    fwrite(buf, strlen(buf), 1, fd_log);
    sprintf(buf, "L2_Ref: %llu\n", nCount_L2_Ref_End - nCount_L2_Ref_Start);
    fwrite(buf, strlen(buf), 1, fd_log);
    sprintf(buf, "L2_Miss: %llu\n", nCount_L2_Miss_End - nCount_L2_Miss_Start);
    fwrite(buf, strlen(buf), 1, fd_log);

    //free(out_pointer);
    fclose(fd_log);
    //printf("lock_count: %llu\n", lock_count);
    //printf("lock_access_count: %llu\n", lock_access_count);
    //printf("closecomm1.\n");
}

static void __attribute__ ((constructor)) probe_init(void) {
    tprof_init(4, 7);
    topmc_prof_begin(&begin);
    tprof(0, nCount_L3_Ref_Start);
    tprof(1, nCount_L3_Miss_Start);
    tprof(2, nCount_L2_Ref_Start);
    tprof(3, nCount_L2_Miss_Start);
    openConn1();

}

static void __attribute__ ((destructor)) probe_fini(void) {
    closeConn1();
    tprof_close();
}




