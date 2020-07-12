#coding: UTF8

"""
Automatic run the application and topmc profiling 
"""

"""
Author: huangyongbing
Time: 2010.5.26
"""

import sys, os, time
import thread

def run_topmc(name, interval):
	print time.time()
	print "in: run_topmc"
	
	time_curr = time.time()
	kt_name = name + str(int(time_curr))
	os.system("sh ./topmc_script/set_event.sh")
	os.system("./topmc_trace/begin_trace 0")
	cmd = "./topmc_trace/collect_trace " + kt_name + " " + interval
	os.system(cmd)

	print "out: run_topmc"

def stop_topmc():
	print time.time()
	print "in: stop_topmc"

	kill_collect_trace()
	os.system("./topmc_trace/stop_trace 0")
	os.system("sh ./topmc_script/stop_profile.sh")

	print "out: stop_topmc"

def kill_collect_trace():
	print time.time()
	print "in: kill_collect_trace"
	thread_id = '0'
	os.system("ps -ef | grep collect > tmp.log")
	fd = open("tmp.log", 'r')
	lines = fd.readlines()
	for line in lines:
		tmpline = line.split(" ")
		if "./topmc_trace/collect_trace" in tmpline:
			index = 1
			for tmp in tmpline[1:]:
				if tmp!='':
					break
				index = index + 1
			thread_id =  tmpline[index]
			break
	fd.close()
	os.system("rm -f tmp.log")
	cmd = "kill -15 " + thread_id
#	cmd = "kill -s SIGTERM " + thread_id
#	print cmd
	os.system(cmd)

def run_app1():
	print time.time()
	print "in: run_app1"
	#os.system("/home/asl/clc/STREAM/stream_c")
	os.system("/opt/pressure_test/CUDA/fermi_hpl/run_16nodes_ib_gpu")
	print "out: run_app1"	

def run_app2():
        print time.time()
        print "in: run_app2"
        #os.system("/home/asl/clc/STREAM/stream_c")
        os.system("/opt/pressure_test/CUDA/fermi_hpl/run_16nodes_ib_nogpu")
        print "out: run_app2"

def run_app3():
        print time.time()
        print "in: run_app3"
        #os.system("/home/asl/clc/STREAM/stream_c")
        os.system("/opt/pressure_test/CUDA/fermi_hpl/run_16nodes_ib_gpu")
        print "out: run_app3"

def run_app4():
        print time.time()
        print "in: run_app4"
        #os.system("/home/asl/clc/STREAM/stream_c")
        os.system("/opt/pressure_test/CUDA/fermi_hpl/run_16nodes_ib_nogpu")
        print "out: run_app4"

def run_profile1(name,time_log):
        print time.time()
        print "Start: run_profile"
 
        thread.start_new_thread(run_topmc,(name,"2",))

	time_log.write("*********")
	time_log.write(name + "*********\n")
	prev_time = time.time()
	time_log.write("start time: " + str(prev_time) + '\n')

        run_app1()

	end_time = time.time()
	time_log.write("end time: " + str(end_time) + '\n')
	run_time = end_time - prev_time
	show_log = "run_time(s): " + str(run_time) + '\n'
	time_log.write(show_log)
	time_log.write("*******************")
 
        stop_topmc()
        os.system("echo '3' >/proc/sys/vm/drop_caches")
        time.sleep(180)
 
        print "Stop: run_profile"

def run_profile2(name,time_log):
        print time.time()
        print "Start: run_profile"
 
        thread.start_new_thread(run_topmc,(name,"2",))

	time_log.write("*********")
	time_log.write(name + "*********\n")
	prev_time = time.time()
	time_log.write("start time: " + str(prev_time) + '\n')

        run_app2()

	end_time = time.time()
	time_log.write("end time: " + str(end_time) + '\n')
	run_time = end_time - prev_time
	show_log = "run_time(s): " + str(run_time) + '\n'
	time_log.write(show_log)
	time_log.write("*******************")
 
        stop_topmc()
        os.system("echo '3' >/proc/sys/vm/drop_caches")
        time.sleep(180)
 
        print "Stop: run_profile"

def run_profile3(name,time_log):
        print time.time()
        print "Start: run_profile"
 
        #thread.start_new_thread(run_topmc,(name,"2",))

	time_log.write("*********")
	time_log.write(name + "*********\n")
	prev_time = time.time()
	time_log.write("start time: " + str(prev_time) + '\n')

        run_app3()

	end_time = time.time()
	time_log.write("end time: " + str(end_time) + '\n')
	run_time = end_time - prev_time
	show_log = "run_time(s): " + str(run_time) + '\n'
	time_log.write(show_log)
	time_log.write("*******************")
 
        #stop_topmc()
        os.system("echo '3' >/proc/sys/vm/drop_caches")
        time.sleep(180)
 
        print "Stop: run_profile"

def run_profile4(name,time_log):
        print time.time()
        print "Start: run_profile"
 
        #thread.start_new_thread(run_topmc,(name,"2",))

	time_log.write("*********")
	time_log.write(name + "*********\n")
	prev_time = time.time()
	time_log.write("start time: " + str(prev_time) + '\n')

        run_app4()

	end_time = time.time()
	time_log.write("end time: " + str(end_time) + '\n')
	run_time = end_time - prev_time
	show_log = "run_time(s): " + str(run_time) + '\n'
	time_log.write(show_log)
	time_log.write("*******************")
 
        #stop_topmc()
        os.system("echo '3' >/proc/sys/vm/drop_caches")
        time.sleep(180)
 
        print "Stop: run_profile"

if __name__ == "__main__":

	print "Topmc Profiling Starting..."

	time_log = "time_" + str(time.time()) + ".log"

	f = open(time_log,'w')

	#run_profile3("16nodes_ib_gpu_alone_100000",f)
	#run_profile4("16nodes_ib_nogpu_alone_100000",f)
	run_profile1("16nodes_ib_gpu_withtopmc_100000",f)
	#run_profile2("16nodes_ib_nogpu_withtopmc_100000",f)
	#kill_collect_trace()
	f.close()

	print "Topmc Profiling Ending."
