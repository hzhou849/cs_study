
# ABOUT:
Directions on building python executable using pyinstaller to package all dependencies.
Tower Button Test v1.2
This application is used to test the tower button box functionality.


#to compile:
pyinstaller for python 3 is required to build and compile for 
self-contained execution.

to install pyinstaller:
#install
for python3:
type 'pip3 install pyinstaller' (requires pip3)



# Single file build


1)'pyinstaller --clean -F fan_gui.py'
- this line will clean and compile at the same time.

2) a new folder in the source directory will be generated called 'dist'

3) copy the newly generated executable file into a folder (you may create a new folder if desired)
   with the following files:
   
	Driver_init.sh
	ite8516k_driver.ko
	start_gpio






#How to use:
1) run the 'start_fan.py' script


2 -OPTIONAL (if step 1 does not work) load the module ite8516k_driver.ko by using the command:
	- sudo insmod ite8516k_driver.ko (or just run the script below)


