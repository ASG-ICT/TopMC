#include <stdio.h>
#include <stdlib.h>
#include <topmc.h>

int main()
{

	struct topmc_stats test_begin, test_end, test_sum;
	topmc_init(4,2);
	topmc_prof_begin(&test_begin);

/*
	uint64_t start1, end1;
	uint64_t start2, end2;
	uint64_t start3, end3;
	
	tprof_init(8,4);
	tprof(0, start1);
	tprof(1, start2);
	tprof(2, start3);
*/
	
	long i = 0, size = 0x200000000;
	char *buf;
	buf = (char*)malloc(size *sizeof(char));
	for(i = 0; i< size; i++)
		buf[i] = i*100;
/*
	tprofd(0, end1, start1);
	tprofd(1, end2, start2);
	tprofd(2, end3, start3);
	printf("tprof start: start1-> %7lu\n", start1);
	printf("tprof start: start2-> %7lu\n", start2);
	printf("tprof start: start3-> %7lu\n", start3);
	printf("tprof result: end1->%7lu\n", end1);
	printf("tprof result: end2->%7lu\n", end2);
	printf("tprof result: end3->%7lu\n", end3);
*/

	topmc_prof_end(&test_begin, &test_end, &test_sum);

//	topmc_prof_display(&test_sum);
	return 1;
}
