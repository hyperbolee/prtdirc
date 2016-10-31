
#!/bin/bash

# lookuptable.sh
# 
#
# Written by Lee Allison, March 15, 2016

# default values for ALL THE THINGS
cores=4
lensid=3
lensnm=3CS
events=200000
lutreg=true
lutavg=true
lutcs=true
force=false

# print lut options to screen
showOpt ()
{
	printf "LUT generation options:
    lens\t${lensid} (${lensnm})
    events\t${events}
    LUT type\t${lutavg}\n\n"
}

# wait for  ${cores} cores at a time
statusline="LUT"
start_time=$(date +%s)
waitForMe ()
{
    while : 
    do 
		activth=$(ps aux | grep "root.exe.*[p]rocData\|[p]rtdirc" | wc -l)
		printf "\r$statusline [$activth threads running] ---- [$(($(date +%s) - start_time)) s] "
		sleep .1
		if [ "$activth" -lt "$1" ]; then 
			break  
 		fi
    done
}

showHelp ()
{
	help="simulation.sh - runs prtdirc simulation over a range of angles\n"
	printf "$help"
}

# read options and set variables
OPTS=`getopt -o l:e:acfh --long lens:,events:,averaged,charge,force,help -n 'simulation.sh' -- "$@"`
eval set -- "$OPTS"

while true; do
  case "$1" in
	  -h | --help) # huh?
		  showHelp;
		  exit 0;;

	  -l | --lens) # set lens number
		  lensid=$2;
		  case "$2" in # set lens name
			  0 ) lensnm=NON;;
			  1 ) lensnm=2CS;;
			  3 ) lensnm=3CS;;
			  4 ) lensnm=AGL;;
			  * ) echo "Wrong lens option";
				  showHelp;
				  exit 0;;
		  esac
		  shift 2;;

	  -e | --events) # set number of events
		  events=$2;
		  shift 2;;

	  -a | --averaged) # create averaged LUT
		  lutreg=false;
		  lutavg=true;
		  shift;;

	  -c | --charge) # create charge-sharing LUT, overrides -u
		  lutreg=false;
		  lutcs=true;
		  shift;;

	  -f | --force) # overwrite files if they exist
		  force=true;
		  shift;;

	  -- ) # break at end of arg string
		  shift; 
		  break;;

	  *  ) # that's not how this script works...
		  showHelp
		  exit 0;;
  esac
done
showOpt

path=../data
lutname=${path}/lut_${lensnm}
if [ -f ${lutname}.root ] && [ ${force} = false ] && [ ${lutreg} = true ] # don't remake unless needed
then
	echo "This LUT already exists."
	echo "To remake, use the -f option."
	echo "Exiting"
	exit 0;
fi

# generate LUT 
seed=${start_time}
./prtdirc -s 1 -a 180 -x "opticalphoton" -p "3.18 eV" -c 2015 -gz 378 -gx 85 -gsx 67.5 -w 0 -g 0 -h 1 -b 1 -e ${events} -l ${lensid} -o ${lutname}_tmp.root >> /dev/null

waitForMe 1
printf "\n"

# make special (avg or cs) table if flag set
if [ ${lutcs} = true ] && [ ${lutavg} = true ]
then
	# charge-sharing LUT
	root -l -q -b ../macro/lutmean_cs.C"(\"${lutname}_tmp.root\")"
	mv ${lutname}_tmp_cs_avr.root  ${lutname}_cs_avr.root

	# averaged LUT
	root -l -q -b ../macro/lutmean.C"(\"${lutname}_tmp.root\")"
	mv ${lutname}_tmp_avr.root  ${lutname}_avr.root

elif [ ${lutcs} = true ]
then
	root -l -q -b ../macro/lutmean_cs.C"(\"${lutname}_tmp.root\")"
	mv ${lutname}_tmp_cs_avr.root  ${lutname}_cs_avr.root
	
elif [ ${lutavg} = true ]
then
	root -l -q -b ../macro/lutmean.C"(\"${lutname}_tmp.root\")"
	mv ${lutname}_tmp_avr.root  ${lutname}_avr.root

else
	# make full LUT as normal
	mv ${lutname}_tmp.root ${lutname}.root
fi

