#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xdadf715a, "module_layout" },
	{ 0x1ed8b599, "__x86_indirect_thunk_r8" },
	{ 0x91db9196, "boot_cpu_data" },
	{ 0xd0e5056d, "remove_proc_entry" },
	{ 0x167e7f9d, "__get_user_1" },
	{ 0x7a2af7b4, "cpu_number" },
	{ 0x91715312, "sprintf" },
	{ 0x6263e02d, "strncpy_from_user" },
	{ 0x60b40fd8, "copy_user_enhanced_fast_string" },
	{ 0xa792fd7f, "cpumask_next" },
	{ 0x7577d164, "PDE_DATA" },
	{ 0x17de3d5, "nr_cpu_ids" },
	{ 0x25e3c331, "proc_mkdir" },
	{ 0x11089ac7, "_ctype" },
	{ 0x27e1a049, "printk" },
	{ 0x31cd8869, "__cpu_online_mask" },
	{ 0xe5772d4a, "copy_user_generic_string" },
	{ 0x23d1b90, "wrmsr_on_cpu" },
	{ 0xdcc3a419, "copy_user_generic_unrolled" },
	{ 0xd75c79df, "smp_call_function" },
	{ 0xa916b694, "strnlen" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0x2ea2c95c, "__x86_indirect_thunk_rax" },
	{ 0xf34ad0c3, "pv_cpu_ops" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0xf654831f, "ex_handler_default" },
	{ 0x4d93fb2e, "proc_create_data" },
	{ 0x20ba4f3e, "rdmsr_on_cpu" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

