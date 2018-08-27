# TopMC : Performance Counter Monitor Tool 

## Overview of the TopMC

TopMC is a performance counter monitor tool which can easily support newest CPU architectures under linux. Currently, most of performance counter monitor tools cannot fully support newest Intel architecture, such as Nehalem. The performance counter events in Nehalem are splitted into core events and uncore events. And tools such as PAPI, Oprofile, pfmon, perfctr only support core events, excluding uncore events such as L3 misses, memory operations. 

TopMC contains a kernel module to interact with linux kernel which eliminates the supports by native linux kerneli(Oprofile) or kernel patch(pfmon). 

TopMC is a lightweight performance counter monitor and trace collector: 

* Easy to use: TopMC is consisted of a kernel module and some scripts. It is convenient to install, easy to understand, and efficienct to modify. Linux kernel is no longer to be recompiled, and scripts are free to modify.

* Lightweight: Most performance counter monitor tools make use of system call to set the performance counter events in linux kernel. However, TopMC achieves this by procfs file system which occurs less overhead.

* Per-thread counting: TopMC's kernel trace mode can detect thread switching which distinguishs performance counters of different threads, no matter whether thread migration happens.

* User level RDPMC instruction: TopMC provides API using RDPMC instruction to monitor code fragements of applications. RDPMC instruction costs only tens of cycles.Thus, applications can obtain more accurate performance counters. 

* Support uncore events in Nehalem,ivybridge_e,broadwell,skylake_sp: The Intel architecture splits the performance counter events into two parts: core events and uncore events. Each part has its own performance counter registers. Most performance counter monitor tools can only support core events, but not uncore events related with L3 cache and memory controller.

## Features of the TopMC

Besides providing low overhead performance counters at specific time, TopMC can collect performance counter traces which are helpful to analysis periodical behaviors of applications. 

## Installation 

### Operating environment

   linux kernel 3.10.X

### Compile and Install 

  * Change to 'topmc_mod' direcotry, and compile the module: 
  
  ```shell
       make -C /lib/modules/$(shell uname -r) M=`pwd` modules 
  ```
  
  * Install the kernel module: 

  ```shell
       insmod topmc_module.ko 
  ```
### Interface with Performance Counter Units 
  
  * Change to '/proc/topmc' directory: 
  
    If 'topmc_module' is successfully loaded, all the performance counter registers of each CPU have      their corresponding file under the '/proc/topmc' directory.
    
## Usage

TopMC provides two ways to use performance counters. One is performance counter trace of an entire application. The other is performance counter value of a piece of code. 

### Collect Performance Counter Trace

* Set the performance counter event to counters: 

    ```shell
    cd topmc_script/
    vim set_event_nehelam.sh (intel) or
    vim set_event_amd.sh (amd)           
    ```

      After change the value of "incore_counter0_event" to what you are interested.

    ```shell
    ./set_event_nehelam.sh (intel) or
    ./set_event_amd.sh (amd)
    ```

* Run your application immediately: 

    ```shell
    python display_topmc.py
    ```
    
    ![results](https://github.com/ASG-ICT/TopMC/blob/master/picture/topmc-shell.jpg)

* Gather the performance counters: 

    ```shell
    python record_result.py
    ```
    
      The interval time of collecting counters can be varied in record_result.py by changing the sleeping time.

### Monitor Piece of Codes

* Set the performance counter event to counters: 

  ```shell
    cd topmc_script/
    vim set_event_nehelam.sh (intel) or
    vim set_event_amd.sh (amd)     
    
    ```

      After change the value of "incore_counter0_event" to what you are interested.

    ```shell
    ./set_event_nehelam.sh (intel) or
    ./set_event_amd.sh (amd)
    ```

* Insert corresponding macros to monitored codes and rebuild the application: 

    Samples can be found in the source codes.

### Implementation Mechanism

The implementation of performance counter monitor tools focus on the interaction with linux kernel. TopMC registers a procs file system using linux kernel module. The framework also contains how to collect kernel trace: 

![architecture](https://github.com/ASG-ICT/TopMC/blob/master/picture/topmc.jpg)

    

