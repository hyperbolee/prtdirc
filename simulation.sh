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
    events\t${events} per particle
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
	help="simulation.sh - runs prtdirc simulation over a range of angles\n\t$1 option not defined\n\n"
	printf "$help"
}

# read options and set variables
OPTS=`getopt -o l:e:i:a:s:m:p:c:frh --long lens:,events:,min:,max:,step:,momentum:,particle:,core:,force,reco,help -n 'simulation.sh' -- "$@"`
eval set -- "$OPTS"

while true; do
  case "$1" in
	  -h | --help) # huh?
		  showHelp;
		  exit 0;;

	  -l | --lens) # set study number
		  study=$2;
		  case "$2" in # set lens name
			  0   ) lensnm=NON; lensid=0 ;;
			  150 ) lensnm=2CS; lensid=1 ;;
			  151 ) lensnm=3CS; lensid=3 ;;
			  158 ) lensnm=3CS; lensid=3 ;;
			  154 ) lensnm=AGL; lensid=4 ;;
			  160 ) lensnm=3CS; lensid=3; momentum=5;;
			  152 ) lensnm=NON; lensid=0; radiator=;;
			  * ) echo "Wrong lens option";
				  showHelp;
				  exit 0;;
		  esac
		  shift 2;;

	  -e | --events) # set number of events per particle
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

	  -p | --particle) # set particle species
		  particle=$2;
		  shift 2;;

	  -c | --core) # hadd reconstruction files after reco
		  cores=$2;
		  shift 2;;

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
		  showHelp $1
		  exit 0;;
  esac
done
showOpt

path=../simulation/${study}
#path=../studies/reflectivity/sim/
# run simulation for angles in range and specified step
for angle in `seq -f %.2f ${anglemin} ${anglestp} ${anglemax}`
do
	runname=${path}/sim_${lensnm}_${angle}
	if [ -f ${runname}.root ] && [ ${force} = false ]
	then
		continue
	fi
	
	# make proton sim
	./prtdirc -p ${momentum} -l ${lensid} -gz 378 -gx 85 -gsx 67.5 -g 2015 -c 2015 -e ${events} -a ${angle} -o ${runname}_p.root -x "proton" -b 1 >> /dev/null &

	waitForMe ${cores} # hold your horses!

	# make pion sim
	./prtdirc -p ${momentum} -l ${lensid} -gz 378 -gx 85 -gsx 67.5 -g 2015 -c 2015 -e ${events} -a ${angle} -o ${runname}_pi.root -x "pi+" -b 1 >> /dev/null &

	waitForMe ${cores} # hold your horses!
done

waitForMe 1 # make sure all processes are finished

# combine proton and pion sims into one file
for angle in `seq -f %.2f ${anglemin} ${anglestp} ${anglemax}`
do
	runname=${path}/sim_${lensnm}_${angle}
	if [ -f ${runname}.root ] && [ ${force} = false ]
	then
		continue
	fi
	
	hadd -f ${runname}.root ${runname}_p.root ${runname}_pi.root >> /dev/null
	rm ${runname}_p.root ${runname}_pi.root
done

wait

printf "\n"

if [ ${reco} = true ]
then
	statusline="Sim Reco"
	start_time=$(date +%s) # reset time for reconstruction
	for angle in `seq -f %.2f ${anglemin} ${anglestp} ${anglemax}`
	do
		runname=${path}/sim_${lensnm}_${angle}.root
		recname=${path}/../reco/reco_${lensnm}_${angle}
		lutname=../data/lut_${lensnm}
		#if [ -f ${lutname}.root ]
		#then
			# make full reco if LUT exists
			#./prtdirc -s 2 -t1 5 -e ${events} -u ${lutname}.root -i ${runname} -o ${recname}.root >> /dev/null &
		#fi
		#waitForMe ${cores} # hold your horses!

		if [ -f ${lutname}_cs_avr.root ]
		then
			# make charge-sharing reco if LUT exists
			# reconstruct twice the events cause you
			# have both pions and protons
			recname=${path}/reco/cs/reco_${lensnm}_${angle}
			./prtdirc -s 2 -t1 5 -e $((2 * ${events})) -u ${lutname}_cs_avr.root -i ${runname} -o ${recname}_cs_avr.root >> /dev/null &
		fi
		waitForMe ${cores} # hold your horses!

		#if [ -f ${lutname}_avr.root ]
		#then
			# make averaged reco if LUT exists
			#recname=${path}/reco/avr/reco_${lensnm}_${angle}
			#./prtdirc -s 2 -t1 5 -e ${events} -u ${lutname}_avr.root -i ${runname} -o ${recname}_avr.root >> /dev/null &
		#fi
		#waitForMe ${cores} # hold your horses!

	done
	waitForMe 1 # make sure all processes are done
	printf "\n"

fi #end if reco
