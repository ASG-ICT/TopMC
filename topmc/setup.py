#coding: UTF8

"""
Setup the topmc profiling 
"""

"""
Author: huangyongbing
Time: 2010.5.26
"""

import sys, os

if __name__ == "__main__":

	print "Setup Topmc Starting..."

	os.system("insmod ./topmc_trace/topmc_trace.ko")
	os.system("mknod /dev/topmc_trace c 250 0")
	os.system("insmod ./topmc_mod/topmc_module.ko")

	print "Setup Topmc Ending."
