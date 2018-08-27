#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xc1b3ede, "struct_module" },
	{ 0x115eacfd, "cpu_online_mask" },
	{ 0x87ed306e, "topmc_pmc_cnt_bitmap" },
	{ 0xc0a3d105, "find_next_bit" },
	{ 0x71822755, "topmc_bitmap_lock" },
	{ 0x167e7f9d, "__get_user_1" },
	{ 0x712aa29b, "_spin_lock_irqsave" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x6263e02d, "strncpy_from_user" },
	{ 0xfe7c4287, "nr_cpu_ids" },
	{ 0x9845e8db, "topmc_pmc_chg" },
	{ 0x8d3894f2, "_ctype" },
	{ 0xea147363, "printk" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xe997667b, "wrmsr_on_cpu" },
	{ 0x4b07e779, "_spin_unlock_irqrestore" },
	{ 0xfc2fc0de, "topmc_chg_lock" },
	{ 0xb1cfad22, "rdmsr_on_cpu" },
	{ 0xd6a78d08, "smp_call_function_single" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7D4A05540AA15D97570AD90");
