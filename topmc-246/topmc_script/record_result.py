#coding: UTF8

"""
Prints out the counters per milliseconds

"""

import time,sys,os

time_curr = time.time()

if __name__ == "__main__":
	
	if len(sys.argv) == 1:
		result_file = "result" + str(int(time_curr)) + ".log"
	elif len(sys.argv) >= 2:
		result_file = "result_" + sys.argv[1] + "_" +  str(int(time_curr)) + ".log"
	if os.path.exists(result_file):
		os.system("unlink result.log") 
	while True:
		time_pre = time.time()
		
		cmd = "echo " + str(time_pre) + "  " + time.ctime() +  " >> " + result_file
		os.system(cmd)
		cmd = "python display_topmc.py >> " + result_file
		os.system(cmd)
		time_done = time.time()
		eclapsed_time = (time_done - time_pre) * 1000
		cmd = "echo eclapsed time:" + str(eclapsed_time) + "ms >> " + result_file
		os.system(cmd) 
		time.sleep(1)
