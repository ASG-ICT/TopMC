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
locale.setlocale(locale.LC_NUMERIC, "")

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
	for dir in full_dir_items:
		if 'value' in dir:
			f	= open(dir,'r')
			cpu	= int(dir[dir.index('core')+4:dir.index('core')+6])
			counter	= int(dir[dir.index('counter')+7:dir.index('counter')+8])

			if cpu in value_buffer:
				value_buffer[cpu][counter] = f.readline().strip()
			else:
				buf = {}
				buf[counter] = f.readline().strip()
				value_buffer[cpu]	= buf
			f.close()

		if 'event' in dir:
			f	= open(dir,'r')
			cpu	= int(dir[dir.index('core')+4:dir.index('core')+6])
			counter	= int(dir[dir.index('counter')+7:dir.index('counter')+8])

			if cpu in event_buffer:
				event_buffer[cpu][counter] = f.readline().strip()
			else:
				buf = {}
				buf[counter] = f.readline().strip()
				event_buffer[cpu]	= buf
			f.close()
	#event
	table	= []
	table.append(["","counter0","counter1","counter2","counter3"])
	f	= open("./events",'r')
	#f	= open("./allevents.txt",'r')
	table_item = [""]
	counter0_event	= '0x' + "%02X" %((int(event_buffer[0][0])&0xFFF000)>>12)
	counter1_event	= '0x' + "%02X" %((int(event_buffer[0][1])&0xFFF000)>>12)
	counter2_event	= '0x' + "%02X" %((int(event_buffer[0][2])&0xFFF000)>>12)
	counter3_event	= '0x' + "%02X" %((int(event_buffer[0][3])&0xFFF000)>>12)
	'''
	counter0_event	=  "%02X" %((int(event_buffer[0][0])&0xFFF000)>>12)
	counter1_event	=  "%02X" %((int(event_buffer[0][1])&0xFFF000)>>12)
	counter2_event	=  "%02X" %((int(event_buffer[0][2])&0xFFF000)>>12)
	counter3_event	=  "%02X" %((int(event_buffer[0][3])&0xFFF000)>>12)
	'''
	f.seek(0)
	for event in f:
		if counter0_event in event:
			#table_item.append(event[event.index(':')+2:].strip())
			table_item.append(event[event.index(':')+2:event.index(';')-2].strip())
			break
	f.seek(0)
	for event in f:
		if counter1_event in event:
			#table_item.append(event[event.index(':')+2:].strip())
			table_item.append(event[event.index(':')+2:event.index(';')-2].strip())
			break
	f.seek(0)
	for event in f:
		if counter2_event in event:
			#table_item.append(event[event.index(':')+2:].strip())
			table_item.append(event[event.index(':')+2:event.index(';')-2].strip())
			break
	f.seek(0)
	for event in f:
		if counter3_event in event:
			#table_item.append(event[event.index(':')+2:].strip())
			table_item.append(event[event.index(':')+2:event.index(';')-2].strip())
			break
	table.append(table_item)
	f.close()	

	#unit mask
	table_item = [""]
	counter0_mask	= "%02X" %((int(event_buffer[0][0])&0xFF0)>>4)
	counter1_mask	= "%02X" %((int(event_buffer[0][1])&0xFF0)>>4)
	counter2_mask	= "%02X" %((int(event_buffer[0][2])&0xFF0)>>4)
	counter3_mask	= "%02X" %((int(event_buffer[0][3])&0xFF0)>>4)
	table_item.append("UnitMask: 0x"+counter0_mask)
	table_item.append("UnitMask: 0x"+counter1_mask)
	table_item.append("UnitMask: 0x"+counter2_mask)
	table_item.append("UnitMask: 0x"+counter3_mask)	
	table.append(table_item)

	#user or os
	mode_str	= ['neither user nor os','only user','only os','both user and os']
	table_item = [""]
	counter0_mode	= int(event_buffer[0][0])&0xF
	counter1_mode	= int(event_buffer[0][1])&0xF
	counter2_mode	= int(event_buffer[0][2])&0xF
	counter3_mode	= int(event_buffer[0][3])&0xF
	table_item.append(mode_str[counter0_mode])
	table_item.append(mode_str[counter1_mode])
	table_item.append(mode_str[counter2_mode])
	table_item.append(mode_str[counter3_mode])	
	table.append(table_item)

	
	table.append(["","-","-","-","-"])
	table.append(["","-","-","-","-"])
	for cpu in value_buffer:
		table_item	= ["cpu"+str(cpu),value_buffer[cpu][0],value_buffer[cpu][1],value_buffer[cpu][2],value_buffer[cpu][3]]
		table.append(table_item)

	out = sys.stdout
	pprint_table(out, table)
