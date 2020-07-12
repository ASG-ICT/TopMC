void topmc_read_cr4_pce(int cpu, int *val);
void topmc_write_cr4_pce(int cpu, int val);

#define TOPMC_READ_CR4_PCE(cpu, v) do { topmc_read_cr4_pce(cpu, &v); } while (0)
#define TOPMC_WRITE_CR4_PCE(cpu, v) do {topmc_write_cr4_pce(cpu, v); } while (0) 
