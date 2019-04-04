#!/bin/bash

execute_path=$(dirname "$0")

# Check if Driver is loaded, if not load it.
driver_check() 
{
	driverCheck=$(lsmod | grep "ite8516k")

	if [ ! -z "$driverCheck" ]
	then 
		echo $driverCheck
		echo -e "Driver found. skipping load sequence. \n"
	else
		echo -e "No driver found, attempting to load GPIO drivers.\n\n"
		sudo insmod ite8516k_driver.ko
	fi
}
		
# Check if all the GPIOs exist and are loaded properly
gpio_device_check()
{	
	for i in {0,1,2,4,6,7,8,9}
	do 
		#sudo sh -c 'echo $i > /sys/class/gpio/export' 
		statusCheck=$(find /sys/class/gpio -name  gpio$i)
		if [ -z "$statusCheck" ]
		then 
			echo -e "Cannot find device id $i"
			state="failed"
		else
			echo -e "$statusCheck - device found"
		fi
	done
}


# Load and initialize GPIOs
init_gpio_sequence()
{
	for i in {0,1,2,4,6,7,8,9}
	do
		# Only use double quotes for sh statements
		sudo sh -c "echo $i > /sys/class/gpio/export"
		echo "reloading gpio($i)..."
	done

	gpio_device_check
}

# Execution 
driver_check
gpio_device_check

#if gpio_device_check returns "failed" then initalize GPIOs and run application
if [ "$state" == "failed" ]
	then
		echo "initializing GPIO"
		init_gpio_sequence
		
	else
		echo "nothing needed to be done, loading GUI application...."
fi

echo -e "$execute_path\n"
$execute_path/GpioApp_v1_2

