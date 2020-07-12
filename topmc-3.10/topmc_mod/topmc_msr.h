#define TOPMC_RDMSRL(msraddr, val, cpu) \
do {                                            \
        u32 vall, valh; \
        rdmsr_on_cpu(cpu, msraddr, &vall, &valh);       \
        val = (u64)(vall | ((u64)valh) << 32);  \
}while(0)


#define TOPMC_WRMSRL(msraddr, val, cpu)                 \
do{                                             \
        wrmsr_on_cpu(cpu, msraddr, (u32)((u64)(val)), (u32)((u64)(val) >> 32)); \
}while(0)

void topmc_rdmsr(int cpu, u32 reg, u32 *low, u32 *high);
void topmc_wrmsr(int cpu, u32 reg, u32 eax, u32 edx);

#define RDMSR(msraddr, val, cpu)                        \
    do {                                                \
        u32 low, high;                                  \
        topmc_rdmsr(cpu, msraddr, &low, &high);         \
        val = (u64)(low | ((u64)high) << 32);           \
    } while(0)

#define WRMSR(msraddr, val, cpu)                        \
    do {                                                \
        u32 low, high;                                  \
        low = (u32)((u64)(val));                        \
        high = (u32)((u64)(val) >> 32);                 \
        topmc_wrmsr(cpu, msraddr, low, high);           \
    } while(0)

