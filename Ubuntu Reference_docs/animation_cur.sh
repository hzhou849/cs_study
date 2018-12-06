#!/bin/bash

# Waiting cursor animation. Apply this script to be execuated with any 
# other scripts you want to execute with in conjunction.
# HOW TO USE: 
# - Add/pass bashscripts you want to execute with this animation script


#Idle animation
animation() {
	# Declared variables
	declare -a a_sprites=("|" "/" "-" "\\")
	counter=1

	# '-d name exists in directory'
	while [ -d /proc/$PID ]
	# while true
	do 
		if [[ "$counter" -gt "4" ]]; then
			counter=1
		fi

		printf "\rPlease wait...${a_sprites[$counter]}"

		#careful this causes unpredictable results
		tput rc; 
		# tput el #rc=restore cursor, el = erase to End of line
		(( ++counter ))
		sleep 0.2
	done
	printf "\r\n"
	sleep 0.2
	# echo -e "\n"
	
}

# Add scripts you want to run with this animation script. Forks to bg
./$1 $2 $3 $4 $5 &

# Tag the PID with the backgroud task script execution
PID=$!

# Run the animation to be excuted until the previous PID task ends
echo "connecting please wait..."
animation


#if task does not terminate on its own...
# kill "$!"