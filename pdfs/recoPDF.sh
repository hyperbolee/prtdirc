#!/bin/bash

# reconstruction.sh
# Run prtdirc reconstruction (-s 2) for
# all PDF files in current director
#
# Written by Lee Allison, March 3, 2016
# Modified November 17, 2016

# default values for ALL THE THINGS
cores=3
events=40000
force=false
start_time=$(date +%s)
statusline="PDF Reco"

# print sim options to screen
showOpt ()
{
	printf "reconstruction options:
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
	help="reconstruction.sh - runs prtdirc reconstruction on PDF files\n"
	printf "$help"
}

# read options and set variables
OPTS=`getopt -o f --long force -n 'reconstruction.sh' -- "$@"`
eval set -- "$OPTS"

while true; do
  case "$1" in
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
path=./
for FILE in ${path}/*.00.root
do
	runname=`basename ${FILE%.root}`
	recoout=${path}/reco/reco_${runname}
	if [ -f ${recoout}_spr.root ] && [ ${force} = false ]
	then # don't reconstruct existing file unless it needs to be
		continue
	fi

	lutname=../data/lut_3CS
	if [ -f ${lutname}_cs_avr.root ]
	then
		# make charge-sharing reco if LUT exists
		../build/prtdirc -s 2 -t1 5 -e ${events} -u ${lutname}_cs_avr.root -i ${FILE} -o ${recoout}_cs_avr.root >> /dev/null &
	fi
	waitForMe ${cores} # hold your horses!

done
waitForMe 1 # wait for all processes to finish

printf "\n"

