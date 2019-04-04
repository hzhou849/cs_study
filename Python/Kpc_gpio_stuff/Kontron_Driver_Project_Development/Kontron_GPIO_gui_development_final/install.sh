#! /bin/bash

if [[ $1 == "-b" ]]; then
	pyinstaller --clean -F GpioApp_v1_2.py
fi
	
scp dist/GpioApp_v1_2 medtronic@169.254.30.42:/home/medtronic/tb_dev
