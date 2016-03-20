#!/bin/bash

# reconstruction.sh
# Run prtdirc reconstruction (-s 2) for
# all data files in a given study (based on lens)
#
# Written by Lee Allison, March 3, 2016

# default values for ALL THE THINGS
cores=4
lensid=3
lensnm=3CS
study=151
runtype=data
events=10000
force=false
start_time=$(date +%s)
statusline="Reco"

# print sim options to screen
showOpt ()
{
	printf "reconstruction options:
    lens\t${lensid} (${lensnm})
    study\t${study}
    events\t${events}\n\n"
}

# wait for  ${cores} cores at a time
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
	help="reconstruction.sh - runs prtdirc reconstruction on data files with selected study\n"
	printf "$help"
}

# read options and set variables
OPTS=`getopt -o l:e:sfh --long lens:,events:,sim,force,help -n 'reconstruction.sh' -- "$@"`
eval set -- "$OPTS"

while true; do
  case "$1" in
	  -h | --help) # huh?
		  showHelp;
		  exit 0;;

	  -l | --lens) # set lens number
		  lensid=$2;
		  case "$2" in # set lens name
			  1 ) lensnm=2CS; study=150 ;;
			  3 ) lensnm=3CS; study=151 ;;
			  4 ) lensnm=AGL; study=154 ;;
			  * ) echo "Unrecongnized lens option";
				  showHelp;
				  exit 0;;
		  esac
		  shift 2;;

	  -e | --events) # set number of events
		  events=$2;
		  shift 2;;

	  -s | --sim) # reconstruct simulation
		  runtype=simulation;
		  shift;;

	  -f | --force) # overwrite files if they exist
		  force=true;
		  shift;;

	  -- ) # break at end of args string
		  shift; 
		  break;;

	  *  ) # that's not how this script works...
		  showHelp
		  exit 0;;
  esac
done
showOpt

#path=../${runtype}/${study}
path=../data/${study}
for FILE in ${path}/*C.root
do
	runname=`basename ${FILE%C.root}`
	recoout=${path}/reco/reco_${runname}
	if [ -f ${recoout}_spr.root ] && [ ${force} = false ]
	then # don't reconstruct existing file unless it needs to be
		continue
	fi

	lutname=../data/lut_${lensnm}
	if [ -f ${lutname}_cs_avr.root ]
	then
		# make charge-sharing reco if LUT exists
		./prtdirc -s 2 -t1 5 -e ${events} -u ${lutname}_cs_avr.root -i ${FILE} -o ${recoout}_cs_avr.root >> /dev/null &
	fi
	waitForMe ${cores} # hold your horses!

	if [ -f ${lutname}_avr.root ]
	then
		# make averaged reco if LUT exists
		./prtdirc -s 2 -t1 5 -e ${events} -u ${lutname}_avr.root -i ${FILE} -o ${recoout}_avr.root >> /dev/null &
	fi
	waitForMe ${cores} # hold your horses!

	if [ -f ${lutname}.root ]
	then
		# make full reco if LUT exists
		./prtdirc -s 2 -t1 5 -e ${events} -u ${lutname}.root -i ${FILE} -o ${recoout}.root >> /dev/null &
	fi
	waitForMe ${cores} # hold your horses!

done

# make single root file after reconstruction
hadd -f ${path}/reco/reco_beam_${study}.root  ${path}/reco/*spr.root
printf "\n"

