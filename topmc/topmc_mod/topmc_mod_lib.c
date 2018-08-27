#include <linux/ctype.h>
#include <linux/smp.h>
//#include <asm/system.h>	//2.6.32

#define TOLOWER(x) ((x) | 0x20)

unsigned int topmc_mix16to32(unsigned short high,unsigned short low)
{
        unsigned int mix;
        
        mix     = (unsigned int)high;
        mix     = mix<<16;
        mix     = mix | (unsigned int)low;

        return mix;
}
        

void topmc_split32to16(unsigned int mix,unsigned short *high,unsigned short *low)
{       
        *low    = (unsigned short)mix;
        *high   = (unsigned short)(mix>>16);
}

/**                     
 * topmc_str2int - convert a string to an int
 * @cp: The start of the string
 * @count: number of character, 0 stands for all of the string
 * @base: The number base to use
 */

unsigned int topmc_str2int(const char *cp,unsigned int count,unsigned int base)
{
        int i=0;
        unsigned int result = 0,value;
                        
        if (!base) {
                base = 10;
                if (*cp == '0') {
                        base = 8;
                        cp++;
                        if ((TOLOWER(*cp) == 'x') && isxdigit(cp[1])) {
                                cp++;
                                base = 16;
                        }
                }
        } else if (base == 16) {
                if (cp[0] == '0' && TOLOWER(cp[1]) == 'x')
                        cp += 2;
        }
        while (isxdigit(*cp) &&
                (value = isdigit(*cp) ? *cp-'0' : TOLOWER(*cp)-'a'+10) < base) {
                result = result*base + value;
                cp++;
                if((count==0)||(++i<count))
                        continue;
                else
                        break;
        }

        return result;
}

/*
struct topmc_cr4_cmd {
        int cpu;
        int data;
};
static inline void topmc_set_pce_in_cr4(void)
{
        unsigned long cr4;

        cr4 = read_cr4();
        cr4 |= 1<<8;
        write_cr4(cr4);
}
static inline void topmc_clr_pce_in_cr4(void)
{
        unsigned long cr4;

        cr4 = read_cr4();
        cr4 &= ~(1<<8);
        write_cr4(cr4);
}

static inline void __topmc_write_cr4_pce(void* cmd)
{
        struct topmc_cr4_cmd *cr4_cmd = (struct topmc_cr4_cmd *)cmd;

        if(cr4_cmd->cpu == smp_processor_id()) {
                if(cr4_cmd->data) {
                        topmc_set_pce_in_cr4();
                }
                else {
                        topmc_clr_pce_in_cr4();
                }
        }
}

int topmc_write_cr4_pce(int cpu)
{
        int err;
        struct topmc_cr4_cmd cr4_cmd;

        cr4_cmd.cpu = cpu;
        cr4_cmd.data = 1;
        err = smp_call_function_single(cpu, __topmc_write_cr4_pce, &cr4_cmd, 1);

        return err;
}
*/
