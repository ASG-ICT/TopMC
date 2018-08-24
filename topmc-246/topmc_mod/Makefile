obj-m := topmc_module.o
#topmc_module-objs :=  topmc_model_skylake_sp.o topmc_mod.o topmc_mod_lib.o topmc_msr.o topmc_cr4pce.o
#topmc_module-objs := topmc_model_ivybridge_e.o topmc_mod.o topmc_mod_lib.o topmc_msr.o topmc_cr4pce.o
topmc_module-objs := topmc_model_broadwell.o topmc_mod.o topmc_mod_lib.o topmc_msr.o topmc_cr4pce.o
#topmc_model_nehelam.o topmc_model_amd.o 
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	rm -f *.ko *.o Module.markers modules.order Module.symvers
