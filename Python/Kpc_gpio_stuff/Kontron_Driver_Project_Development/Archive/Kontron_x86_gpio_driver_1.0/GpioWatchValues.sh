#!/bin/bash

#display GPIO reading from sysfs *NOTE only 10 GPIOs are used for the button box

# cd /sys/class/gpio
# watch -n0 cat ./gpio0/value ./gpio1/value ./gpio2/value ./gpio3/value ./gpio4/value ./gpio5/value ./gpio

# method 2 using macros
# this algorithm is intended to auto populate the watch script gpio values
MAXCOUNT=10
COUNTER=0
MACRO=" ./gpio$COUNTER"
while [ $COUNTER -le $MAXCOUNT]; 
do
	a+=" ./gpio$COUNTER"

	((COUNTER++))