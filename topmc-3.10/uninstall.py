#coding: UTF8

"""
Uninstall the topmc profiling 
"""

"""
Author: huangyongbing
Time: 2010.5.26
"""

import sys, os

if __name__ == "__main__":

	print "Uninsatll Topmc Starting..."

	os.system("rmmod topmc_module")
	os.system("rmmod topmc_trace")
	os.system("rm -f /dev/topmc_trace")

	print "Uninstall Topmc Ending."
