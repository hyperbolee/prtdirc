#!/bin/bash

# simulation.sh
# Run prtdirc simulation for a given range of
# angles at fixed steps between angles
# with specifiable lens, events, particleID,
# and beam momentum (default values below)
# To force re-run of simulation when file
# already exists use -f option
# 
# Also reconstructs those simulations if
# -r option is specified
#
# Written by Lee Allison, March 3, 2016

# default values for ALL THE THINGS
cores=4
lensid=3
lensnm=3CS
study=151
events=1000
anglemin=20
anglemax=160
anglestp=5
momentum=7
hadd=false
force=false
reco=false
particle="proton"

# print sim options to screen
showOpt ()
{
	printf "simulation options:
    lens\t${lensid} (${lensnm})
    events\t${events}
    min ang\t${anglemin}
    max ang\t${anglemax}
    ang stp\t${anglestp}
    reco\t${reco}
    momentum\t${momentum}
    particle\t${particle}\n\n"
}

# wait for  ${cores} cores at a time
statusline="Sim"
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
OPTS=`getopt -o l:e:i:a:s:m:p:dfrh --long lens:,events:,min:,max:,step:,momentum:,particle:,hadd,force,reco,help -n 'simulation.sh' -- "$@"`
eval set -- "$OPTS"

while true; do
  case "$1" in
	  -h | --help) # huh?
		  showHelp;
		  exit 0;;

	  -l | --lens) # set lens number
		  lensid=$2;
		  case "$2" in # set lens name
			  0 ) lensnm=NON; study=0   ;;
			  1 ) lensnm=2CS; study=150 ;;
			  3 ) lensnm=3CS; study=151 ;;
			  4 ) lensnm=AGL; study=154 ;;
			  * ) echo "Wrong lens option";
				  showHelp;
				  exit 0;;
		  esac
		  shift 2;;

	  -e | --events) # set number of events
		  events=$2;
		  shift 2;;

	  -i | --min) # set minimum angle for loop
		  anglemin=$2;
		  shift 2;;

	  -a | --max) # set maximum angle for loop
		  anglemax=$2;
		  shift 2;;

	  -s | --step) # set stepping size for angle loop
		  anglestp=$2;
		  shift 2;;

	  -m | --momentum) # set momentum for beam
		  momentum=$2;
		  shift 2;;

	  -p | --particle) # set particle
		  particle=$2;
		  shift 2;;

	  -d | --hadd) # hadd reconstruction files after reco
		  hadd=true;
		  shift;;

	  -f | --force) # overwrite files if they exist
		  force=true;
		  shift;;

	  -r | --reco) # reconstruct after simulation
		  reco=true;
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

path=../simulation/${study}
# run simulation for angles in range and specified step
for angle in `seq -f %.2f ${anglemin} ${anglestp} ${anglemax}`
do
	runname=${path}/sim_${lensnm}_${angle}
	if [ -f ${runname}.root ] && [ ${force} = false ]
	then
		continue
	fi
	./prtdirc -p ${momentum} -l ${lensid} -gz 378 -gx 85 -gsx 67.5 -g 2015 -c 2015 -e ${events} -a ${angle} -o ${runname}.root -x ${particle} -b 1 >> /dev/null &

	waitForMe ${cores} # hold your horses!
done
printf "\n"

if [ ${reco} = true ]
then
	statusline="Reco"
	start_time=$(date +%s) # reset time for reconstruction
	for angle in `seq -f %.2f ${anglemin} ${anglestp} ${anglemax}`
	do
		runname=${path}/sim_${lensnm}_${angle}.root
		recname=${path}/reco/reco_${lensnm}_${angle}
		lutname=../data/lut_${lensnm}
		if [ -f ${lutname}_cs_avr.root ]
		then
			# make charge-sharing reco if LUT exists
			./prtdirc -s 2 -t1 5 -e ${events} -u ${lutname}_cs_avr.root -i ${runname} -o ${recname}_cs_avr.root >> /dev/null &
		fi
		waitForMe ${cores} # hold your horses!

		if [ -f ${lutname}_avr.root ]
		then
			# make averaged reco if LUT exists
			./prtdirc -s 2 -t1 5 -e ${events} -u ${lutname}_avr.root -i ${runname} -o ${recname}_avr.root >> /dev/null &
		fi
		waitForMe ${cores} # hold your horses!

		if [ -f ${lutname}.root ]
		then
			# make full reco if LUT exists
			./prtdirc -s 2 -t1 5 -e ${events} -u ${lutname}.root -i ${runname} -o ${recname}.root >> /dev/null &
		fi

		waitForMe ${cores} # hold 'em somemore!

	done
	wait
	printf "\n"

<<EOF
	# make single root file after reconstruction
	if [ ${hadd} = true ]
	then
		sleep .2
		hadd -f ${path}/reco/reco_${lensnm}${lutavg}.root ${path}/reco/*${lutavg}_spr.root;
	fi
EOF

fi