// -----------------------------------------------------------------
#define PMC_NUM                      4

// msr address
#define EVNT_SEL0                    0xC0010000
#define EVNT_SEL1                    0xC0010001
#define EVNT_SEL2                    0xC0010002
#define EVNT_SEL3                    0xC0010003

// msr initial
#define EVNT_SEL_RESERVED            ((0xFFFFFCF0ULL<<32)|(0xFFFF82FFULL))

#define SET_ENABLE(val)              (val |=  (1<<22))
#define SET_DISABLE(val)             (val &= ~(1<<22))

#define SET_INT_ENABLE(val)          (val |=  (1<<20))
#define SET_INT_DISABLE(val)         (val &= ~(1<<20))

#define SET_KERN(val, k)             (val |=  ((k & 1) << 17))
#define SET_USR(val, u)              (val |=  ((u & 1) << 16))

#define SET_UNIT_MASK(val, e)        (val |=  ((e & 0x000ff0 ) << 4))
#define SET_EVENT_SELECT(val, e)     (val |= (((e & 0xf00000) << 16) | (e & 0x0ff000) >> 12)) 

// msr address
#define PMC0                         0xC0010004
#define PMC1                         0xC0010005
#define PMC2                         0xC0010006
#define PMC3                         0xC0010007
