#!/bin/bash

COUNTER=0
SOURCE="ite8516k_driver.ko"
GPIO_MAX=18


#load GPIO kernel module 
#check to see if module is already loaded?
# --->if no then proceed. else error and exit
sudo insmod $SOURCE


#sysfs directory for GPIO device driver
cd /sys/class/gpio
sudo chmod 777 *

# Initialize GPIOs
while [ $COUNTER -le $GPIO_MAX ];
do 
	echo "Initalizing GPIO pin $COUNTER"
	sudo echo $COUNTER > export #
	((COUNTER++))
done