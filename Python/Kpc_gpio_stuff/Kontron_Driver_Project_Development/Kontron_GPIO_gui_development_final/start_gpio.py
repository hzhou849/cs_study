'''
A simple python script to execute the startup bashscript from the Ubuntu GUI interface
'''

import os

os.system(r'sh -c "./Driver_init.sh"')
# os.system(r'sudo sh -c "echo in > /sys/class/gpio/gpio7/direction"')