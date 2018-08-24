#coding: UTF8
"""
Prints out a table, padded to make it pretty.

call pprint_table with an output (e.g. sys.stdout, cStringIO, file)
and table as a list of lists. Make sure table is "rectangular" -- each
row has the same number of columns.

MIT License
"""

__version__ = "0.1"
__author__ = "Ryan Ginstrom"

import locale
#locale.setlocale(locale.LC_NUMERIC, "")

def format_num(num):
    """Format a number according to given places.
    Adds commas, etc.
    
    Will truncate floats into ints!"""

    try:
        inum = int(num)
        return locale.format("%.*f", (0, inum), True)

    except (ValueError, TypeError):
        return str(num)

def get_max_width(table, index):
    """Get the maximum width of the given column index
    """
    
    return max([len(format_num(row[index])) for row in table])

def pprint_table(out, table):
    """Prints out a table of data, padded for alignment
    
    @param out: Output stream ("file-like object")
    @param table: The table to print. A list of lists. Each row must have the same
    number of columns.
    
    """

    col_paddings = []
    
    for i in range(len(table[0])):
        col_paddings.append(get_max_width(table, i))

    for row in table:
        # left col
        print >> out, row[0].ljust(col_paddings[0] + 1),
        # rest of the cols
        for i in range(1, len(row)):
            col = format_num(row[i]).rjust(col_paddings[i] + 2)
            print >> out, col,
        print >> out
"""
table = [["", "taste", "land speed", "life"],
["spam", 300101, 4, 1003],
["eggs", 105, 13, 42],
["lumberjacks", 13, 105, 10]]
"""
if __name__ == "__main__":

	import os,time,sys

	topmc_dir	= '/proc/topmc'
	full_dir_items	= []
	for cpu_dir in os.listdir(topmc_dir):
		if not os.path.isdir(topmc_dir+'/'+cpu_dir):
			continue
		for counter_dir in os.listdir(topmc_dir+'/'+cpu_dir):
			for item in os.listdir(topmc_dir+'/'+cpu_dir+'/'+counter_dir):
				full_dir	= topmc_dir+'/'+cpu_dir+'/'+counter_dir+'/'+item
				full_dir_items.append(full_dir)

	value_buffer = {}
	event_buffer = {}
	aval_counter = []
	enable_flag = {}

	enable_all = '0'

	# find the avaiable counters & mark them
	for dir in full_dir_items:
		enable_flag0 = '0'
		cpu = int(dir[dir.index('core')+4:dir.index('core')+6])
		if cpu==0:
			if 'incore_counter' in dir:
				incore_counter	= int(dir[dir.index('incore_counter')+14:dir.index('incore_counter')+15])
				counter = incore_counter
			if 'uncore_counter' in dir:
				uncore_counter = int(dir[dir.index('uncore_counter')+14:dir.index('uncore_counter')+15])
				counter = int(uncore_counter) + 4 ## 4 is the total number of incore counters
			enable_flag[counter] = enable_flag0
			if 'enable' in dir:
				f = open(dir,'r')
				enable_flag0 = f.readline().strip()
				enable_flag[counter] = enable_flag0
				if enable_all=='0' and enable_flag0=='1':
					enable_all = '1'
				f.close()
	if enable_all == '0':
		print "All the counters are disabled, return!"
		sys.exit(1)

	for dir in full_dir_items:
		cpu	= int(dir[dir.index('core')+4:dir.index('core')+6])
		if 'incore_counter' in dir:
			incore_counter	= int(dir[dir.index('incore_counter')+14:dir.index('incore_counter')+15])
			counter = incore_counter
		if 'uncore_counter' in dir:
			uncore_counter = int(dir[dir.index('uncore_counter')+14:dir.index('uncore_counter')+15])
			counter = int(uncore_counter) + 4 ## 4 is the total number of incore counters
		if enable_flag[counter]=='1':
			if 'value' in dir:
				f	= open(dir,'r')
				if cpu in value_buffer:
					value_buffer[cpu][counter] = f.readline().strip()
				else:
					buf = {}
					buf[counter] = f.readline().strip()
					value_buffer[cpu]	= buf
				f.close()

			if 'event' in dir:
				f	= open(dir,'r')

				if cpu in event_buffer:
					event_buffer[cpu][counter] = f.readline().strip()
				else:
					buf = {}
					buf[counter] = f.readline().strip()
					event_buffer[cpu]	= buf
				f.close()
			if counter not in aval_counter:
				aval_counter.append(counter)
	#event
	table	= []
	table_menu_name = []  ##incore_counter0
	table_event_counter = []  ##0x3C
	table_mask_counter = []	##ff
	table_menu_name.append("")
	for cnt in aval_counter:
		if cnt < 4:
			table_menu_name.append('incore'+str(cnt))
		else:
			table_menu_name.append('uncore'+str(cnt - 4))
		#counter_event = '0x' + "%02X" % ((int(event_buffer[0][cnt])&0xFFF000)>>12)
		counter_event = '0x' + event_buffer[0][cnt][2:4]
		#counter_event = ((int(event_buffer[0][cnt])&0xFFF000)>>12)
		#counter_mask = "%02X" %((int(event_buffer[0][cnt])&0xFF0)>>4)
		counter_mask = event_buffer[0][cnt][4:6] 
		table_event_counter.append(counter_event)
		table_mask_counter.append(counter_mask)
	table.append(table_menu_name)
	
	f	= open("./events",'r')
	table_item = [""]
	f.seek(0)
	for counter_event in table_event_counter:
		for event in f:
			if counter_event in event:
				table_item.append(event[event.index(':')+2:event.index(';')-2].strip())
				break
		f.seek(0)
	table.append(table_item)
	f.close()	

	#unit mask
	table_item = [""]
	for counter_mask in table_mask_counter:
		table_item.append("UMask: 0x"+counter_mask)
	table.append(table_item)

	split = [""]
	i = 0
	while i < aval_counter.__len__():
		i = i+1
		split.append('-')
	table.append(split)
	table.append(split)
		
#	table.append(["","-","-","-","-","-","-","-","-","-","-"])
#	table.append(["","-","-","-","-","-","-","-","-","-","-"])
	for cpu in value_buffer:
		table_item = []
		table_item.append("cpu"+str(cpu))
		for cnt in aval_counter:
			table_item.append(value_buffer[cpu][cnt])
		table.append(table_item)

	#print table
	out = sys.stdout
	print str(time.ctime()) + "   " + str(time.time())

	pprint_table(out, table)
