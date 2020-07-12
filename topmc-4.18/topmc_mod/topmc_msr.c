
//#include <asm/thread_info.h>
//#include <thread_info.h>
#include <asm/processor.h>
//#include <asm/uaccess.h>
#include <linux/ctype.h>
#include <linux/smp.h>
#include <linux/percpu.h>	//3.12

// ------------------------------------------------------------------
struct topmc_msr_command {
    int cpu;
    int err;
    u32 reg;
    u32 low;
    u32 high;
};

static void topmc_rdmsr_smp(void *cmd_block)
{
    struct topmc_msr_command *cmd = (struct topmc_msr_command *)cmd_block;

    if (cmd->cpu == smp_processor_id()) {
        rdmsr(cmd->reg, cmd->low, cmd->high);
    }
} 

void topmc_rdmsr(int cpu, u32 reg, u32 *low, u32 *high)
{
    struct topmc_msr_command cmd;

    preempt_disable();
    if (cpu == smp_processor_id()) {
        rdmsr(reg, *low, *high);
    } else {
        cmd.cpu = cpu;
        cmd.reg = reg;

        smp_call_function(topmc_rdmsr_smp, &cmd, 1);

        *low = cmd.low;
        *high = cmd.high;
    }
    preempt_enable();
}

static void topmc_wrmsr_smp(void *cmd_block)
{
    struct topmc_msr_command *cmd = (struct topmc_msr_command *)cmd_block;

    if (cmd->cpu == smp_processor_id()) {
        wrmsr(cmd->reg, cmd->low, cmd->high);
    }
}

void topmc_wrmsr(int cpu, u32 reg, u32 low, u32 high)
{
    struct topmc_msr_command cmd;

    preempt_disable();
    if (cpu == smp_processor_id()) {
        wrmsr(reg, low, high);
    } else {
        cmd.cpu = cpu;
        cmd.reg = reg;
        cmd.low = low;
        cmd.high = high;

        smp_call_function(topmc_wrmsr_smp, &cmd, 1);
    }
    preempt_enable();
}
