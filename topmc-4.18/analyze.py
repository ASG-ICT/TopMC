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

	print "Setup Analysis Starting..."

	if sys.argv[2] == None:
		print "Usage: python analyze.py filenam keyword"
		sys.exit()

	input_file = sys.argv[1]
	keyword = sys.argv[2]
	print input_file
	f = open(input_file,'r')
	output_file = input_file + "_" + keyword
	g = open(output_file, 'w')
	for event in f:
		if keyword in event:
			g.write(event)
	g.close()
	f.close()

	print "Setup Analysis Ending."
