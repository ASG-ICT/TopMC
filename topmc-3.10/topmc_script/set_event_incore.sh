#counter event format:'***--#'
#'***' stands for event
#'--' stands for unit mask
#'#' stands for usr/kernel:0-nothing,1-user,2-kernel,3-user and kernel

#counter0_event='0c0ff1'
#counter1_event='0c0ff2'
#counter2_event='041ff1'
#counter3_event='041ff2' 
counter0_event='03c001'
counter1_event='03c002'
counter2_event='03cff1'
counter3_event='03cff2' 

cpunum=`cat /proc/cpuinfo |grep processor|wc -l`
echo '0' > /proc/topmc/enable_all

cpuid=0
while [ $cpuid -lt $cpunum ]
do
	if [ $cpuid -lt 10 ]
	then
		event0="/proc/topmc/core0$cpuid/counter0/event"
		event1="/proc/topmc/core0$cpuid/counter1/event"
		event2="/proc/topmc/core0$cpuid/counter2/event"
		event3="/proc/topmc/core0$cpuid/counter3/event"
		enable0="/proc/topmc/core0$cpuid/counter0/enable"
		enable1="/proc/topmc/core0$cpuid/counter1/enable"
		enable2="/proc/topmc/core0$cpuid/counter2/enable"
		enable3="/proc/topmc/core0$cpuid/counter3/enable"
	else
		event0="/proc/topmc/core$cpuid/counter0/event"
		event1="/proc/topmc/core$cpuid/counter1/event"
		event2="/proc/topmc/core$cpuid/counter2/event"
		event3="/proc/topmc/core$cpuid/counter3/event"
		enable0="/proc/topmc/core$cpuid/counter0/enable"
		enable1="/proc/topmc/core$cpuid/counter1/enable"
		enable2="/proc/topmc/core$cpuid/counter2/enable"
		enable3="/proc/topmc/core$cpuid/counter3/enable"
	fi

	cpuid=`expr $cpuid + 1`
	echo $counter0_event > $event0
	echo $counter1_event > $event1
	echo $counter2_event > $event2
	echo $counter3_event > $event3
	echo "1" > $enable0
	echo "1" > $enable1
	echo "1" > $enable2
	echo "1" > $enable3
done

echo '1' > /proc/topmc/enable_all
