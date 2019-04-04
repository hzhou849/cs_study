#!/bin/bash
# rm -r /home/howardz/Development/Ubuntu_x86/Kontron_GPIO_gui/build
# rm -r /home/howardz/Development/Ubuntu_x86/Kontron_GPIO_gui/dist
# rm -r /home/howardz/Development/Ubuntu_x86/Kontron_GPIO_gui/__pycache__
pyinstaller --clean GpioApp_ver2-2.py
# sh -c echo "pyinstaller Gpio_ver2-2.py"
# rm  /home/howardz/Development/Ubuntu_x86/Kontron_GPIO_gui/dist/Gpio_App_ver2.tar.gz
# sh -c echo "tar -cvzf GpioApp_ver2.tar.gz Gpio_App_ver2-2/"
cd dist
scp -r GpioApp_ver2-2/ medtronic@192.168.1.4:/home/medtronic/