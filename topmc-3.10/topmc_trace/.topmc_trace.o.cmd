cmd_/home/zjt/topmc-process-switch-ban-UCUPT/topmc_trace/topmc_trace.o := gcc -Wp,-MD,/home/zjt/topmc-process-switch-ban-UCUPT/topmc_trace/.topmc_trace.o.d  -nostdinc -isystem /usr/lib/gcc/x86_64-redhat-linux/4.4.7/include -I/home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include -Iarch/x86/include/generated  -Iinclude -I/home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I/home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi -Iinclude/generated/uapi -include /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/linux/kconfig.h -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -m64 -mno-mmx -mno-sse -mtune=generic -mno-red-zone -mcmodel=kernel -funit-at-a-time -maccumulate-outgoing-args -fstack-protector -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_FXSAVEQ=1 -DCONFIG_AS_AVX=1 -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -Wframe-larger-than=2048 -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -pg -fno-inline-functions-called-once -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO  -DMODULE  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(topmc_trace)"  -D"KBUILD_MODNAME=KBUILD_STR(topmc_trace)" -c -o /home/zjt/topmc-process-switch-ban-UCUPT/topmc_trace/.tmp_topmc_trace.o /home/zjt/topmc-process-switch-ban-UCUPT/topmc_trace/topmc_trace.c

source_/home/zjt/topmc-process-switch-ban-UCUPT/topmc_trace/topmc_trace.o := /home/zjt/topmc-process-switch-ban-UCUPT/topmc_trace/topmc_trace.c

deps_/home/zjt/topmc-process-switch-ban-UCUPT/topmc_trace/topmc_trace.o := \
  include/linux/module.h \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/module/sig.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  include/uapi/linux/types.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/types.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/posix_types.h \
  include/linux/stddef.h \
  include/uapi/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/posix_types.h \
    $(wildcard include/config/x86/32.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/posix_types_64.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/asm-generic/posix_types.h \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/const.h \
  include/linux/stat.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/stat.h \
  include/uapi/linux/stat.h \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
  /usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stdarg.h \
  include/linux/linkage.h \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/linkage.h \
    $(wildcard include/config/x86/64.h) \
    $(wildcard include/config/x86/alignment/16.h) \
  include/linux/bitops.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/bitops.h \
    $(wildcard include/config/x86/cmov.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/alternative.h \
    $(wildcard include/config/paravirt.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/asm.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/ptrace.h \
    $(wildcard include/config/x86/debugctlmsr.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/segment.h \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/x86/32/lazy/gs.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/cache.h \
    $(wildcard include/config/x86/l1/cache/shift.h) \
    $(wildcard include/config/x86/internode/cache/shift.h) \
    $(wildcard include/config/x86/vsmp.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/page_types.h \
    $(wildcard include/config/physical/start.h) \
    $(wildcard include/config/physical/align.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/page_64_types.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/ptrace.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/ptrace-abi.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/processor-flags.h \
    $(wildcard include/config/vm86.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/processor-flags.h \
  include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
  include/asm-generic/ptrace.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/cpufeature.h \
    $(wildcard include/config/x86/debug/static/cpu/has.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/required-features.h \
    $(wildcard include/config/x86/minimum/cpu/family.h) \
    $(wildcard include/config/math/emulation.h) \
    $(wildcard include/config/x86/pae.h) \
    $(wildcard include/config/x86/cmpxchg64.h) \
    $(wildcard include/config/x86/use/3dnow.h) \
    $(wildcard include/config/x86/p6/nop.h) \
    $(wildcard include/config/matom.h) \
  include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  include/asm-generic/bitops/sched.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/le.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/uapi/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  include/uapi/linux/swab.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/swab.h \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/ext2-atomic-setbit.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/typecheck.h \
  include/linux/printk.h \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  include/linux/kern_levels.h \
  include/linux/dynamic_debug.h \
  include/uapi/linux/kernel.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/sysinfo.h \
  include/linux/seqlock.h \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/context/tracking.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
    $(wildcard include/config/debug/stack/usage.h) \
  include/linux/bug.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/thread_info.h \
    $(wildcard include/config/ia32/emulation.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/page.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/page_64.h \
    $(wildcard include/config/debug/virtual.h) \
    $(wildcard include/config/flatmem.h) \
  include/linux/range.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  include/asm-generic/getorder.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/processor.h \
    $(wildcard include/config/m486.h) \
    $(wildcard include/config/xen.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/vm86.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/vm86.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/math_emu.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/sigcontext.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/sigcontext.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/current.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/percpu.h \
    $(wildcard include/config/x86/64/smp.h) \
  include/asm-generic/percpu.h \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/pgtable_types.h \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/mem/soft/dirty.h) \
    $(wildcard include/config/compat/vdso.h) \
    $(wildcard include/config/proc/fs.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/pgtable_64_types.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/sparsemem.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/msr.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/msr.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/msr-index.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/ioctl.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/uapi/asm-generic/ioctl.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/errno.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/asm-generic/errno.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/asm-generic/errno-base.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/cpumask.h \
  include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  include/linux/bitmap.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  include/uapi/linux/string.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/string.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/string_64.h \
  include/linux/errno.h \
  include/uapi/linux/errno.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/desc_defs.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/nops.h \
    $(wildcard include/config/mk7.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/special_insns.h \
  include/linux/personality.h \
  include/uapi/linux/personality.h \
  include/linux/math64.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/div64.h \
  include/asm-generic/div64.h \
  include/linux/err.h \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/irqflags.h \
  include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/atomic.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/cmpxchg.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/cmpxchg_64.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/atomic64_64.h \
  include/asm-generic/atomic-long.h \
  include/linux/bottom_half.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/barrier.h \
    $(wildcard include/config/x86/ppro/fence.h) \
    $(wildcard include/config/x86/oostore.h) \
  include/linux/spinlock_types.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/spinlock_types.h \
    $(wildcard include/config/paravirt/spinlocks.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/rwlock.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  include/linux/rwlock_types.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/spinlock.h \
  include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/paravirt.h \
  include/linux/rwlock.h \
  include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
  include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  include/uapi/linux/time.h \
  include/linux/uidgid.h \
    $(wildcard include/config/uidgid/strict/type/checks.h) \
    $(wildcard include/config/user/ns.h) \
  include/linux/highuid.h \
  include/linux/kmod.h \
  include/linux/gfp.h \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/cma.h) \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  include/linux/wait.h \
  include/uapi/linux/wait.h \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/linux/nodemask.h \
    $(wildcard include/config/movable/node.h) \
  include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/linux/page-flags-layout.h \
  include/generated/bounds.h \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/have/bootmem/info/node.h) \
  include/linux/notifier.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/mutex/spin/on/owner.h) \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/rwsem.h \
  include/linux/srcu.h \
  include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/rcu/user/qs.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
    $(wildcard include/config/no/hz/full/sysidle.h) \
  include/linux/completion.h \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  include/linux/rcutree.h \
  include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/jiffies.h \
  include/linux/timex.h \
  include/uapi/linux/timex.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/param.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/param.h \
  include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  include/uapi/asm-generic/param.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/timex.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/tsc.h \
    $(wildcard include/config/x86/tsc.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/mmzone.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/mmzone_64.h \
  include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/smp.h \
    $(wildcard include/config/x86/local/apic.h) \
    $(wildcard include/config/x86/io/apic.h) \
    $(wildcard include/config/x86/32/smp.h) \
    $(wildcard include/config/debug/nmi/selftest.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/mpspec.h \
    $(wildcard include/config/x86/numaq.h) \
    $(wildcard include/config/eisa.h) \
    $(wildcard include/config/x86/mpparse.h) \
    $(wildcard include/config/acpi.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/mpspec_def.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/x86_init.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/bootparam.h \
  include/linux/screen_info.h \
  include/uapi/linux/screen_info.h \
  include/linux/apm_bios.h \
  include/uapi/linux/apm_bios.h \
  include/linux/edd.h \
  include/uapi/linux/edd.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/e820.h \
    $(wildcard include/config/efi.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/memtest.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/e820.h \
    $(wildcard include/config/intel/txt.h) \
  include/linux/ioport.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/ist.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/ist.h \
  include/video/edid.h \
    $(wildcard include/config/x86.h) \
  include/uapi/video/edid.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/apicdef.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/apic.h \
    $(wildcard include/config/x86/x2apic.h) \
  include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/fixmap.h \
    $(wildcard include/config/paravirt/clock.h) \
    $(wildcard include/config/provide/ohci1394/dma/init.h) \
    $(wildcard include/config/x86/visws/apic.h) \
    $(wildcard include/config/pci/mmconfig.h) \
    $(wildcard include/config/x86/intel/mid.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/acpi.h \
    $(wildcard include/config/acpi/numa.h) \
  include/acpi/pdc_intel.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/numa.h \
    $(wildcard include/config/numa/emu.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/topology.h \
    $(wildcard include/config/x86/ht.h) \
  include/asm-generic/topology.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/mmu.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/realmode.h \
    $(wildcard include/config/acpi/sleep.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/io.h \
    $(wildcard include/config/mtrr.h) \
  include/asm-generic/iomap.h \
    $(wildcard include/config/has/ioport.h) \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/generic/iomap.h) \
  include/asm-generic/pci_iomap.h \
    $(wildcard include/config/no/generic/pci/ioport/map.h) \
    $(wildcard include/config/generic/pci/iomap.h) \
  include/linux/vmalloc.h \
    $(wildcard include/config/mmu.h) \
  include/linux/rbtree.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/pvclock.h \
  include/linux/clocksource.h \
    $(wildcard include/config/arch/clocksource/data.h) \
    $(wildcard include/config/clocksource/watchdog.h) \
    $(wildcard include/config/clksrc/of.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/clocksource.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/pvclock-abi.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/vsyscall.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/vsyscall.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/vvar.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/idle.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/io_apic.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/irq_vectors.h \
    $(wildcard include/config/have/kvm.h) \
  include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
  include/linux/pfn.h \
  include/linux/sysctl.h \
    $(wildcard include/config/sysctl.h) \
  include/uapi/linux/sysctl.h \
  include/linux/elf.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/elf.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/user.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/user_64.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/auxvec.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/vdso.h \
  include/uapi/linux/elf.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/elf-em.h \
  include/linux/kobject.h \
    $(wildcard include/config/debug/kobject/release.h) \
  include/linux/sysfs.h \
  include/linux/kobject_ns.h \
  include/linux/kref.h \
  include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  include/linux/tracepoint.h \
  include/linux/static_key.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/module.h \
    $(wildcard include/config/m586.h) \
    $(wildcard include/config/m586tsc.h) \
    $(wildcard include/config/m586mmx.h) \
    $(wildcard include/config/mcore2.h) \
    $(wildcard include/config/m686.h) \
    $(wildcard include/config/mpentiumii.h) \
    $(wildcard include/config/mpentiumiii.h) \
    $(wildcard include/config/mpentiumm.h) \
    $(wildcard include/config/mpentium4.h) \
    $(wildcard include/config/mk6.h) \
    $(wildcard include/config/mk8.h) \
    $(wildcard include/config/melan.h) \
    $(wildcard include/config/mcrusoe.h) \
    $(wildcard include/config/mefficeon.h) \
    $(wildcard include/config/mwinchipc6.h) \
    $(wildcard include/config/mwinchip3d.h) \
    $(wildcard include/config/mcyrixiii.h) \
    $(wildcard include/config/mviac3/2.h) \
    $(wildcard include/config/mviac7.h) \
    $(wildcard include/config/mgeodegx1.h) \
    $(wildcard include/config/mgeode/lx.h) \
  include/asm-generic/module.h \
    $(wildcard include/config/have/mod/arch/specific.h) \
    $(wildcard include/config/modules/use/elf/rel.h) \
    $(wildcard include/config/modules/use/elf/rela.h) \
  include/linux/fs.h \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  include/linux/kdev_t.h \
  include/uapi/linux/kdev_t.h \
  include/linux/dcache.h \
  include/linux/rculist.h \
  include/linux/rculist_bl.h \
  include/linux/list_bl.h \
  include/linux/bit_spinlock.h \
  include/linux/lockref.h \
    $(wildcard include/config/cmpxchg/lockref.h) \
  include/linux/path.h \
  include/linux/list_lru.h \
  include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  include/linux/radix-tree.h \
  include/linux/pid.h \
  include/linux/capability.h \
  include/uapi/linux/capability.h \
  include/linux/semaphore.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/fiemap.h \
  include/linux/shrinker.h \
  include/linux/migrate_mode.h \
  include/linux/percpu-rwsem.h \
  include/linux/blk_types.h \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/blk/dev/integrity.h) \
  include/uapi/linux/fs.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/limits.h \
  include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  include/linux/percpu_counter.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/dqblk_xfs.h \
  include/linux/dqblk_v1.h \
  include/linux/dqblk_v2.h \
  include/linux/dqblk_qtree.h \
  include/linux/projid.h \
  include/uapi/linux/quota.h \
  include/linux/nfs_fs_i.h \
  include/linux/fcntl.h \
  include/uapi/linux/fcntl.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/fcntl.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/asm-generic/fcntl.h \
  include/linux/cdev.h \
  include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/no/hz/common.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/virt/cpu/accounting/native.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/virt/cpu/accounting/gen.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/uprobes.h) \
    $(wildcard include/config/bcache.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/no/hz/full.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/mm/owner.h) \
  include/uapi/linux/sched.h \
  include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/have/cmpxchg/double.h) \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/transparent/hugepage.h) \
  include/linux/auxvec.h \
  include/uapi/linux/auxvec.h \
  include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/guard.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  include/linux/uprobes.h \
    $(wildcard include/config/arch/supports/uprobes.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/uprobes.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/cputime.h \
  include/asm-generic/cputime.h \
    $(wildcard include/config/virt/cpu/accounting.h) \
  include/asm-generic/cputime_jiffies.h \
  include/linux/sem.h \
  include/uapi/linux/sem.h \
  include/linux/ipc.h \
  include/uapi/linux/ipc.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/ipcbuf.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/asm-generic/ipcbuf.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/sembuf.h \
  include/linux/signal.h \
    $(wildcard include/config/old/sigaction.h) \
  include/uapi/linux/signal.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/signal.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/signal.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/asm-generic/signal-defs.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/siginfo.h \
  include/asm-generic/siginfo.h \
  include/uapi/asm-generic/siginfo.h \
  include/linux/proportions.h \
  include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
    $(wildcard include/config/seccomp/filter.h) \
  include/uapi/linux/seccomp.h \
  include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  include/linux/resource.h \
  include/uapi/linux/resource.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/resource.h \
  include/asm-generic/resource.h \
  include/uapi/asm-generic/resource.h \
  include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  include/linux/timerqueue.h \
  include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  include/linux/latencytop.h \
  include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
  include/linux/key.h \
  include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  include/linux/mm.h \
    $(wildcard include/config/ppc.h) \
    $(wildcard include/config/parisc.h) \
    $(wildcard include/config/metag.h) \
    $(wildcard include/config/ksm.h) \
    $(wildcard include/config/debug/vm/rb.h) \
    $(wildcard include/config/arch/uses/numa/prot/none.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/hugetlbfs.h) \
  include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/pgtable.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/pgtable_64.h \
  include/asm-generic/pgtable.h \
    $(wildcard include/config/have/arch/soft/dirty.h) \
  include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/swap.h) \
  include/linux/huge_mm.h \
  include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
  include/linux/vm_event_item.h \
  include/linux/pci.h \
    $(wildcard include/config/pci/iov.h) \
    $(wildcard include/config/pcieaspm.h) \
    $(wildcard include/config/pci/msi.h) \
    $(wildcard include/config/pci/ats.h) \
    $(wildcard include/config/pcieportbus.h) \
    $(wildcard include/config/pcieaer.h) \
    $(wildcard include/config/pcie/ecrc.h) \
    $(wildcard include/config/ht/irq.h) \
    $(wildcard include/config/pci/domains.h) \
    $(wildcard include/config/pci/quirks.h) \
    $(wildcard include/config/hibernate/callbacks.h) \
    $(wildcard include/config/hotplug/pci.h) \
    $(wildcard include/config/of.h) \
    $(wildcard include/config/eeh.h) \
  include/linux/mod_devicetable.h \
  include/linux/uuid.h \
  include/uapi/linux/uuid.h \
  include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/dma/cma.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  include/linux/klist.h \
  include/linux/pinctrl/devinfo.h \
  include/linux/ratelimit.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/device.h \
    $(wildcard include/config/x86/dev/dma/ops.h) \
    $(wildcard include/config/intel/iommu.h) \
    $(wildcard include/config/amd/iommu.h) \
  include/linux/pm_wakeup.h \
  include/linux/io.h \
  include/linux/irqreturn.h \
  include/uapi/linux/pci.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/pci_regs.h \
  include/linux/pci_ids.h \
  include/linux/pci-dma.h \
  include/linux/dmapool.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/scatterlist.h \
  include/asm-generic/scatterlist.h \
    $(wildcard include/config/debug/sg.h) \
    $(wildcard include/config/need/sg/dma/length.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/pci.h \
  include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/slab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/debug/slab.h) \
  include/linux/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  include/linux/slab_def.h \
    $(wildcard include/config/memcg/kmem.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/pci_64.h \
    $(wildcard include/config/calgary/iommu.h) \
  include/asm-generic/pci-dma-compat.h \
  include/linux/dma-mapping.h \
    $(wildcard include/config/has/dma.h) \
    $(wildcard include/config/arch/has/dma/set/coherent/mask.h) \
    $(wildcard include/config/have/dma/attrs.h) \
    $(wildcard include/config/need/dma/map/state.h) \
  include/linux/dma-attrs.h \
  include/linux/dma-direction.h \
  include/linux/scatterlist.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/dma-mapping.h \
    $(wildcard include/config/isa.h) \
    $(wildcard include/config/x86/dma/remap.h) \
  include/linux/kmemcheck.h \
  include/linux/dma-debug.h \
    $(wildcard include/config/dma/api/debug.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/swiotlb.h \
    $(wildcard include/config/swiotlb.h) \
  include/linux/swiotlb.h \
  include/asm-generic/dma-coherent.h \
    $(wildcard include/config/have/generic/dma/coherent.h) \
  include/linux/dma-contiguous.h \
    $(wildcard include/config/cma/areas.h) \
  include/asm-generic/dma-mapping-common.h \
  include/asm-generic/pci.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/uaccess.h \
    $(wildcard include/config/x86/intel/usercopy.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/smap.h \
    $(wildcard include/config/x86/smap.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/uaccess_64.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/delay.h \
  include/asm-generic/delay.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/pgalloc.h \
  include/linux/pagemap.h \
  include/linux/highmem.h \
    $(wildcard include/config/debug/highmem.h) \
  include/linux/uaccess.h \
  include/linux/hardirq.h \
  include/linux/preempt_mask.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/hardirq.h \
    $(wildcard include/config/x86/thermal/vector.h) \
    $(wildcard include/config/x86/mce/threshold.h) \
  include/linux/irq.h \
    $(wildcard include/config/generic/pending/irq.h) \
    $(wildcard include/config/hardirqs/sw/resend.h) \
  include/linux/irqnr.h \
  include/uapi/linux/irqnr.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/irq.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/irq_regs.h \
  include/linux/irqdesc.h \
    $(wildcard include/config/irq/preflow/fasteoi.h) \
    $(wildcard include/config/sparse/irq.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/hw_irq.h \
    $(wildcard include/config/irq/remap.h) \
  include/linux/profile.h \
    $(wildcard include/config/profiling.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/sections.h \
    $(wildcard include/config/debug/rodata.h) \
  include/asm-generic/sections.h \
  include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  include/linux/vtime.h \
  include/linux/context_tracking_state.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/cacheflush.h \
    $(wildcard include/config/x86/pat.h) \
    $(wildcard include/config/debug/rodata/test.h) \
  include/asm-generic/cacheflush.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/kmap_types.h \
  include/asm-generic/kmap_types.h \
  include/linux/hugetlb_inline.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/proto.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/uapi/asm/ldt.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/tlb.h \
  include/asm-generic/tlb.h \
    $(wildcard include/config/have/rcu/table/free.h) \
  include/linux/swap.h \
    $(wildcard include/config/frontswap.h) \
    $(wildcard include/config/memcg/swap.h) \
  include/linux/memcontrol.h \
    $(wildcard include/config/inet.h) \
  include/linux/cgroup.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/cgroupstats.h \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/include/uapi/linux/taskstats.h \
  include/linux/prio_heap.h \
  include/linux/idr.h \
  include/linux/xattr.h \
  include/uapi/linux/xattr.h \
  include/linux/percpu-refcount.h \
  include/linux/cgroup_subsys.h \
    $(wildcard include/config/cgroup/debug.h) \
    $(wildcard include/config/cgroup/cpuacct.h) \
    $(wildcard include/config/cgroup/device.h) \
    $(wildcard include/config/cgroup/freezer.h) \
    $(wildcard include/config/net/cls/cgroup.h) \
    $(wildcard include/config/cgroup/perf.h) \
    $(wildcard include/config/netprio/cgroup.h) \
    $(wildcard include/config/cgroup/hugetlb.h) \
  include/linux/node.h \
    $(wildcard include/config/memory/hotplug/sparse.h) \
  /home/zjt/linux-3.12.13-4GUC6G/linux-3.12.13/arch/x86/include/asm/tlbflush.h \
  /home/zjt/topmc-process-switch-ban-UCUPT/topmc_trace/topmc_trace.h \

/home/zjt/topmc-process-switch-ban-UCUPT/topmc_trace/topmc_trace.o: $(deps_/home/zjt/topmc-process-switch-ban-UCUPT/topmc_trace/topmc_trace.o)

$(deps_/home/zjt/topmc-process-switch-ban-UCUPT/topmc_trace/topmc_trace.o):
