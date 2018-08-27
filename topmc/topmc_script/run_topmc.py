#coding: UTF8

"""
Automatic run the application and topmc
"""

import sys,os,time
import thread

def run_app1(name):
	print "in: run_appl"
	os.system("sh set_event.sh")
	cmd = "python record_result.py " + name
	os.system(cmd)

def run_app2():
	print "in: run_app2"
	#os.system("df -h > /home/bingo/topmc/dflog")
	#os.system("taskset -c 1 /home/asl/clc/produce_bandwidth/bandwidth64 1024 0")
	os.system("taskset -c 1,2,3,4 /home/asl/clc/STREAM/stream_c 4")
	#os.system("taskset -c 1 /usr/local/CUDA_SDK/C/bin/linux/release/bandwidthTest --memory=pinned --mode=range --start=512000000 --end=1024000000 --increment=102400000 --htod --ssplit=0 --MEM_ITERATIONS=100")

def run_app3():
	print "in: run_app3"
	#os.system("cd /home/asl/benchmarks/SPECcpu2006 | taskset -c 4 runspec --config this --action run --noreportable --size=ref 459")
#	os.system("cd /home/bingo/topmc")
	#os.system("taskset -c 4 /home/asl/clc/bebop-spmvbench-1.0.0/hpcc_spmv_benchmark/hpcc_spmv_benchmark 20 4096 1")
	#os.system("/home/asl/clc/produce_bandwidth/bandwidth64 1024 0")
	#os.system("export OMP_NUM_THREADS=4 | taskset -c 4,5,6,7 /home/asl/clc/STREAM/stream_c")
	#os.system("taskset -c 4,5,6,7 /home/asl/benchmarks/PARSEC/parsec-2.1/bin/parsecmgmt -a run -c gcc-hooks -p x264 -n 4 -i native")
	os.system("taskset -c 4,5,6,7 /home/asl/clc/bebop-spmvbench-1.0.0/hpcc_spmv_benchmark/hpcc_spmv_benchmark 20 4096 1")
	#os.system("taskset -c 1 /home/bingo/computer/csr")

def run_speccpu(cpunum,id):
	print "in: run_speccpu"
	cmd = "cd /home/asl/clc | taskset -c " + cpunum + " runspec --config this --action run --noreportable --size=ref " + id
	os.system(cmd)

def kill_app1():
	print time.time()
	print "in: kill_app1"
	thread_id = '0'
        os.system("ps -ef | grep record_result > tmp.log")
        fd = open("tmp.log", 'r')
        lines = fd.readlines()
        for line in lines:
                tmpline = line.split(" ")
                if "python" in tmpline:
			index = 1
			for tmp in tmpline[1:]:
				if tmp!='':
					break
				index = index + 1
			thread_id =  tmpline[index]
			break
	fd.close()
	os.system("rm -f tmp.log")
	cmd = "kill -9 " + thread_id
	print cmd
	os.system(cmd)
	print time.time()
	
def kill_app2():
	print "in: kill_app2"
	thread_id = '0'
        os.system("ps -ef | grep  bandwidthTest > tmp.log")
        fd = open("tmp.log", 'r')
        lines = fd.readlines()
        for line in lines:
                tmpline = line.split(" ")
                if "--memory=pinned" in tmpline:
			index = 1
			for tmp in tmpline[1:]:
				if tmp!='':
					break
				index = index + 1
			thread_id =  tmpline[index]
			break
	fd.close()
	os.system("rm -f tmp.log")
	cmd = "kill -9 " + thread_id
	print cmd
	os.system(cmd)

def run_profile(name):
	print time.time()
	cpuname =  "cpu" + name
	print "Start " + cpuname
	thread.start_new_thread(run_app1,(cpuname,))
	#thread.start_new_thread(run_speccpu,("4","470",))
	#thread.start_new_thread(run_speccpu,("1","437",))
	run_speccpu("2", name)
	#run_app1(cpuname)
	#run_app3()
	#run_app2()
	kill_app1()
	#kill_app2()
	os.system("echo '3' > /proc/sys/vm/drop_caches")
	time.sleep(180)
	print "End " + cpuname


if __name__ == "__main__":
	
	print "Start profiling"

	run_profile("470")
	run_profile("482")
	run_profile("459")
	run_profile("450")
	run_profile("437")
	run_profile("471")
        run_profile("462")
        run_profile("403")
	
	print "End profiling"
