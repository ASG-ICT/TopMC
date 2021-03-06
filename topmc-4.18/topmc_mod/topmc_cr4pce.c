#include <asm/processor.h>
//#include <asm/uaccess.h>
#include <linux/ctype.h>
#include <linux/smp.h>
#include <linux/percpu.h>	//3.12

struct topmc_cr4_command {
    int cpu;
    int data;
    int err;
};

static inline void topmc_set_cr4_pce(void)
{
    unsigned long cr4;

    cr4 = __read_cr4();
    cr4 |= (1<<8);
    __write_cr4(cr4);
    printk("+->core%d: set cr4.pce (%lx)\n", smp_processor_id(), __read_cr4());
}

static inline void topmc_clear_cr4_pce(void) 
{ 
    unsigned long cr4;

    cr4 = __read_cr4();
    cr4 &= ~(1<<8);
    __write_cr4(cr4);
    printk("+->core%d: clear cr4.pce (%lx)\n", smp_processor_id(), __read_cr4());
}

static void topmc_read_cr4_pce_smp(void *cmd_block)
{
    struct topmc_cr4_command *cmd = (struct topmc_cr4_command *)cmd_block;
    unsigned long cr4;
    int pce;

    if (cmd->cpu == smp_processor_id()) {
        cr4 = __read_cr4();
        pce = (cr4 >> 8) & 0x1;
        cmd->data = pce;
    }
}

void topmc_read_cr4_pce(int cpu, int *val) 
{
    unsigned long cr4;
    int pce;
    struct topmc_cr4_command cmd;

    preempt_disable();
    if(cpu == smp_processor_id()) {
        cr4 = __read_cr4();
        pce = (cr4 >> 8) & 0x1;
    } else {
        cmd.cpu = cpu;
        smp_call_function(topmc_read_cr4_pce_smp, &cmd, 1);
        pce = cmd.data;
    }
    preempt_enable();

    *val = pce;
}

static void topmc_write_cr4_pce_smp(void *cmd_block)
{
    struct topmc_cr4_command *cmd = (struct topmc_cr4_command *)cmd_block;

    if(cmd->cpu == smp_processor_id()) {
        if(cmd->data) {
            topmc_set_cr4_pce();
        } else {
            topmc_clear_cr4_pce();
        }
    }
}    

void topmc_write_cr4_pce(int cpu, int val) 
{ 
    struct topmc_cr4_command cmd;

    preempt_disable();
    if(cpu == smp_processor_id()) {
        if(val) { //enable
            topmc_set_cr4_pce();
        } else {
            topmc_clear_cr4_pce();
        }
    } else {
        cmd.cpu = cpu;
        cmd.data = val;
        smp_call_function(topmc_write_cr4_pce_smp, &cmd, 1);
    }
    preempt_enable();
}

