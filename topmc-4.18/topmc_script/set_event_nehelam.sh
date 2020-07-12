#counter event format:'***--#'
#'***' stands for event
#'--' stands for unit mask
#'#' stands for usr/kernel:0-nothing,1-user,2-kernel,3-user and kernel

#counter0_event='0c0ff1'
#counter1_event='0c0ff2'
#counter2_event='041ff1'
#counter3_event='041ff2' 
###
#incore_counter0_event='03c003'
#incore_counter1_event='0c0013'
#incore_counter2_event='02E413'
#uncore_counter0_event='02c070'
#uncore_counter1_event='02f070'
#uncore_counter2_event='020010'
#uncore_counter3_event='020020'
#uncore_counter4_event='020040' 
#uncore_counter5_event='020100' 
#uncore_counter6_event='009030' 
#uncore_counter7_event='009040' 

#counter event format:'**--xyz#'
#'**' stands for event
#'--' stands for unit mask
#'x' stands for cmask (only 4-bit value)
#'y' stands for inv 
#'z' stands for edge
#'#' stands for usr/kernel:0-nothing,1-user,2-kernel,3-user and kernel
incore_counter0_event='2E4F0003'
incore_counter1_event='2E410003'
uncore_counter0_event='2c070000'
uncore_counter1_event='2f070000'
uncore_counter2_event='20010000'
uncore_counter3_event='20020000'
uncore_counter4_event='20040000' 
uncore_counter5_event='20100000' 
uncore_counter6_event='09030000' 
uncore_counter7_event='09040000' 

cpunum=`cat /proc/cpuinfo |grep processor|wc -l`
#echo '0' > /proc/topmc/enable_all

cpuid=0
while [ $cpuid -lt $cpunum ]
do
	if [ $cpuid -lt 10 ]
	then
		incore_event0="/proc/topmc/core0$cpuid/incore_counter0/event"
		incore_event1="/proc/topmc/core0$cpuid/incore_counter1/event"
#		incore_event2="/proc/topmc/core0$cpuid/incore_counter2/event"
		uncore_event0="/proc/topmc/core0$cpuid/uncore_counter0/event"
		uncore_event1="/proc/topmc/core0$cpuid/uncore_counter1/event"
		uncore_event2="/proc/topmc/core0$cpuid/uncore_counter2/event"
		uncore_event3="/proc/topmc/core0$cpuid/uncore_counter3/event"
		uncore_event4="/proc/topmc/core0$cpuid/uncore_counter4/event"
		uncore_event5="/proc/topmc/core0$cpuid/uncore_counter5/event"
		uncore_event6="/proc/topmc/core0$cpuid/uncore_counter6/event"
		uncore_event7="/proc/topmc/core0$cpuid/uncore_counter7/event"
		incore_enable0="/proc/topmc/core0$cpuid/incore_counter0/enable"
		incore_enable1="/proc/topmc/core0$cpuid/incore_counter1/enable"
#		incore_enable2="/proc/topmc/core0$cpuid/incore_counter2/enable"
		uncore_enable0="/proc/topmc/core0$cpuid/uncore_counter0/enable"
		uncore_enable1="/proc/topmc/core0$cpuid/uncore_counter1/enable"
		uncore_enable2="/proc/topmc/core0$cpuid/uncore_counter2/enable"
		uncore_enable3="/proc/topmc/core0$cpuid/uncore_counter3/enable"
		uncore_enable4="/proc/topmc/core0$cpuid/uncore_counter4/enable"
		uncore_enable5="/proc/topmc/core0$cpuid/uncore_counter5/enable"
		uncore_enable6="/proc/topmc/core0$cpuid/uncore_counter6/enable"
		uncore_enable7="/proc/topmc/core0$cpuid/uncore_counter7/enable"
	else 
		incore_event0="/proc/topmc/core$cpuid/incore_counter0/event"
		incore_event1="/proc/topmc/core$cpuid/incore_counter1/event"
#		incore_event2="/proc/topmc/core$cpuid/incore_counter2/event"
		uncore_event0="/proc/topmc/core$cpuid/uncore_counter0/event"
		uncore_event1="/proc/topmc/core$cpuid/uncore_counter1/event"
		uncore_event2="/proc/topmc/core$cpuid/uncore_counter2/event"
		uncore_event3="/proc/topmc/core$cpuid/uncore_counter3/event"
		uncore_event4="/proc/topmc/core$cpuid/uncore_counter4/event"
		uncore_event5="/proc/topmc/core$cpuid/uncore_counter5/event"
		uncore_event6="/proc/topmc/core$cpuid/uncore_counter6/event"
		uncore_event7="/proc/topmc/core$cpuid/uncore_counter7/event"
		incore_enable0="/proc/topmc/core$cpuid/incore_counter0/enable"
		incore_enable1="/proc/topmc/core$cpuid/incore_counter1/enable"
#		incore_enable2="/proc/topmc/core$cpuid/incore_counter2/enable"
		uncore_enable0="/proc/topmc/core$cpuid/uncore_counter0/enable"
		uncore_enable1="/proc/topmc/core$cpuid/uncore_counter1/enable"
		uncore_enable2="/proc/topmc/core$cpuid/uncore_counter2/enable"
		uncore_enable3="/proc/topmc/core$cpuid/uncore_counter3/enable"
		uncore_enable4="/proc/topmc/core$cpuid/uncore_counter4/enable"
		uncore_enable5="/proc/topmc/core$cpuid/uncore_counter5/enable"
		uncore_enable6="/proc/topmc/core$cpuid/uncore_counter6/enable"
		uncore_enable7="/proc/topmc/core$cpuid/uncore_counter7/enable"

	fi

	cpuid=`expr $cpuid + 1`
	echo "0" > $incore_enable0
	echo "0" > $incore_enable1
#	echo "0" > $incore_enable2
	echo "0" > $uncore_enable0
	echo "0" > $uncore_enable1
	echo "0" > $uncore_enable2
	echo "0" > $uncore_enable3
	echo "0" > $uncore_enable4
	echo "0" > $uncore_enable5
	echo "0" > $uncore_enable6
	echo "0" > $uncore_enable7
	echo $incore_counter0_event > $incore_event0
	echo $incore_counter1_event > $incore_event1
#	echo $incore_counter2_event > $incore_event2
	echo $uncore_counter0_event > $uncore_event0
	echo $uncore_counter1_event > $uncore_event1
	echo $uncore_counter2_event > $uncore_event2
	echo $uncore_counter3_event > $uncore_event3
	echo $uncore_counter4_event > $uncore_event4
	echo $uncore_counter5_event > $uncore_event5
	echo $uncore_counter6_event > $uncore_event6
	echo $uncore_counter7_event > $uncore_event7
	echo "1" > $incore_enable0
	echo "1" > $incore_enable1
#	echo "1" > $incore_enable2
	echo "1" > $uncore_enable0
	echo "1" > $uncore_enable1
	echo "1" > $uncore_enable2
	echo "1" > $uncore_enable3
	echo "1" > $uncore_enable4
	echo "1" > $uncore_enable5
	echo "1" > $uncore_enable6
	echo "1" > $uncore_enable7
done

#echo '1' > /proc/topmc/enable_all
