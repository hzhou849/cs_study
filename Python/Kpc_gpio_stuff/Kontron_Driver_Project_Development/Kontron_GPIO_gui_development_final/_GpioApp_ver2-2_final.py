#!/usr/bin/python3


'''
TBD			- Remove on/off for latch mode
			- keep latch mode persistantly ON

02/01/2018 	- Added error catching for gpio state changes.
			- Added Reset GPIO directions on close.
			- Tested all features working.

01/31/2018 	- Added app terminate detection.
			- tested for single executable build

Copyright 2018 Medtronic.
All Rights Reserved. The information contained herein is confidential
property of Medtronic. The use, copying, transfer or disclosure of such
information is prohibited except by written agreement with Medtronic. 
'''



import pdb
#from tkinter import Tk, E, W, Label and Menu
from tkinter import *
from tkinter.ttk import Frame, Button, Entry, Style
# from PIL import Image, ImageTk

from tkinter import messagebox
import tkinter as ttk
import tkinter.ttk as ttk #??
import subprocess
import shlex # shell lexical analysis of the shell-style syntaxes
import time
import os

os.system("")

class GPIO_Tester (Frame):
	
	global gpioList; gpioList = ["0", "1", "2", "4", "6", "7", "8","9"]
	global backgroundColor; backgroundColor = "#f5f5f5"
	UPDATER_DELAY = 100 #ms
	gpioMode="off" 

	def __init__(self, main):

		super().__init__()
		self.main=main
		self.initUI(main)
		
	def initUI(self,main):
		# Set the app title
		self.master.title("GPIO Test Application v1.0")
		
		# Initialize themes
		self.style_Init()

		# Initialize grid
		self.rowCol_Init()

		# Initialize and create GUI components/widgets
		self.createMenu()
		self.row0_Blank()
		self.GPIO_Labels()
		self.column2_Blank()
		self.Sys_Pause_Components_Init()
		self.Sys_Act_Components_Init()
		self.LatchResetComponents_Init()


		self.updater()
		self.pack(fill=BOTH, expand=1)

	# Define themes and styles	
	def style_Init(self):

		Style().configure("TButton", padding=(0,5,0,5))
	
		Style().configure("TFrame", background=backgroundColor)
		# Adjust the frame attributes
		
		# second set of themes 
		Style().configure('ledSysAct.TButton', background="#d9d9d9", foreground="#000000",relief=RAISED)
		Style().configure('ledSysPause.TButton', background="#d9d9d9", foreground="#000000",relief=RAISED)
	
	def rowCol_Init(self):
		self.columnconfigure(0, pad=20)
		self.columnconfigure(1, pad=20)
		self.columnconfigure(2, pad=20)
		self.columnconfigure(3, pad=20)
		self.columnconfigure(4, pad=20)
		self.columnconfigure(5, pad=20)
		self.columnconfigure(6, pad=20)

		self.rowconfigure(0, pad=00)
		self.rowconfigure(1, pad=20)
		self.rowconfigure(2, pad=20)
		self.rowconfigure(3, pad=20)
		self.rowconfigure(4, pad=20)
		self.rowconfigure(5, pad=20)
		self.rowconfigure(6, pad=20)
		self.rowconfigure(7, pad=20)
		self.rowconfigure(8, pad=20)
		self.rowconfigure(9, pad=20)
		self.rowconfigure(10,pad=20)
	
	#======== GUI COMPONENTS=====================================================


	def createMenu(self):
		# *****Create menu object to be placed in main 'self' window
		menuObject = Menu(self.master)
		self.master.config(menu=menuObject)

		fileMenu = Menu(menuObject, tearoff=0)
		menuObject.add_cascade(label="File", menu=fileMenu)
		fileMenu.add_command(label="Command1", command=self.getGpioState)
		fileMenu.add_command(label="Command2", command=self.getGpioState)
		fileMenu.add_separator()
		fileMenu.add_command(label="Exit", command=self.quit)

		aboutMenu = Menu(menuObject, tearoff=0)
		menuObject.add_cascade(label="About", menu=aboutMenu)
		aboutMenu.add_command(label="about") #add command

	def row0_Blank(self):
		blankLabel=Label(self, text=" ", background=backgroundColor); blankLabel.grid(column=0, row=0)
		# blankLabel=Label(self, text=" ", background=backgroundColor); blankLabel.grid(column=0, row=1)
	def GPIO_Labels(self):
		gpio0Label = Label(self, text="Gpio_0", background=backgroundColor)
		gpio0Label.grid(row=1, column=0)
		gpio1Label = Label(self, text="Gpio_1", background=backgroundColor) 
		gpio1Label.grid(row=2, column=0)
		gpio2Label = Label(self, text="Gpio_2", background=backgroundColor)
		gpio2Label.grid(row=3, column=0)
		gpio4Label = Label(self, text="Gpio_4", background=backgroundColor)
		gpio4Label.grid(row=4, column=0)
		gpio6Label = Label(self, text="Gpio_6", background=backgroundColor)
		gpio6Label.grid(row=5, column=0)
		gpio7Label = Label(self, text="Gpio_7", background=backgroundColor)
		gpio7Label.grid(row=6, column=0)
		gpio8Label = Label(self, text="Gpio_8", background=backgroundColor)
		gpio8Label.grid(row=7, column=0)
		gpio9Label = Label(self, text="Gpio_9", background=backgroundColor)
		gpio9Label.grid(row=8, column=0)

		self.gpio0_entry = Entry(self, width=5)
		self.gpio0_entry.grid(row=1, column=1)
		self.gpio1_entry = Entry(self, width=5)
		self.gpio1_entry.grid(row=2, column=1)
		self.gpio2_entry = Entry(self, width=5)
		self.gpio2_entry.grid(row=3, column=1)
		self.gpio4_entry = Entry(self, width=5)
		self.gpio4_entry.grid(row=4, column=1)
		self.gpio6_entry = Entry(self, width=5)
		self.gpio6_entry.grid(row=5, column=1)
		self.gpio7_entry = Entry(self, width=5)
		self.gpio7_entry.grid(row=6, column=1)
		self.gpio8_entry = Entry(self, width=5)
		self.gpio8_entry.grid(row=7, column=1)
		self.gpio9_entry = Entry(self, width=5)
		self.gpio9_entry.grid(row=8, column=1)

	def column2_Blank(self):
		#blankLabel=Label(self, text="       ", background='black'); blankLabel.grid(column=2, row=0)
		verticalSeperator = ttk.Separator(self, orient=VERTICAL).grid(row=1,rowspan=10,column=2,padx=10 ,sticky=NS)
	
		
	
	def Sys_Pause_Components_Init(self):
		""" Sys_Pause GUI Components"""
		sysPauseLabel = Label(self, text="System Pause Button:", background=backgroundColor)
		sysPauseLabel.grid(row=4, column=3,sticky=W)

		# Sys_Pause ON OFF Label
		self.sysPauseLabelOnOff = Label(self,width=5, text="OFF", foreground='gray', relief=SUNKEN)
		self.sysPauseLabelOnOff.grid(row=4, column=4)

		# LED button
		self.sysPauLED_Button=Button(self, text="LED Off",width=8, command = \
			lambda: self.LEDbuttonPress("sys_pause"), style='ledSysPause.TButton' )
		self.sysPauLED_Button.grid(row=5, column =3, sticky=W)

		splitter = ttk.Separator(self)
		splitter.grid(row=6, column=3, columnspan=3, sticky="ew")

	def Sys_Act_Components_Init(self):
		"""Sys_Activate button components"""
		sysActLabel = Label(self, text="System Activate Button:", background=backgroundColor)
		sysActLabel.grid(row=1, column=3, sticky=W)

		self.sysActLabelOnOff = Label(self,width=5, text="OFF", foreground='gray', relief=SUNKEN)
		self.sysActLabelOnOff.grid(row=1, column=4)

		# LED button
		self.sysActLED_Button=Button(self, text="LED Off",width=8, command = \
			lambda: self.LEDbuttonPress("sys_act"), style='ledSysAct.TButton' )
		self.sysActLED_Button.grid(row=2, column =3, sticky=W)

		splitter = ttk.Separator(self)
		splitter.grid(row=3, column=3, columnspan=3, sticky="ew")

	def LatchResetComponents_Init(self):
	
		sysLatch_Label = Label(self, text="Latch Mode: ", background=backgroundColor)
		sysLatch_Label.grid(row=7, column=3, sticky=W)
		
		self.sysLatch_OnOffIndicator_Label = Label(self,width=5, text="SET", foreground='gray', relief=SUNKEN)
		self.sysLatch_OnOffIndicator_Label.grid(row=7, column=4)
		# Latch mode radio button
		v=IntVar()
		self.LatchRadioOn = Radiobutton(self, text="On",relief=SUNKEN, \
										command=lambda: self.LatchResetButtonPress("latchOn"), \
										background=backgroundColor, variable=v, value=1)
		self.LatchRadioOn.grid(row=8, column=3, sticky=W)

		self.LatchRadioOn = Radiobutton(self, text="Off",relief=SUNKEN,\
										command=lambda: self.LatchResetButtonPress("latchOff"), \
										background=backgroundColor, variable=v, value=2)
		self.LatchRadioOn.set(1)
		self.LatchRadioOn.grid(row=8, column=4, sticky=W)
		#break this button out if possible
		self.sysReset_Button=Button(self, text="Reset",width=5, \
									command = lambda: self.LatchResetButtonPress("sysReset"), \
									style='direction.TButton' )

		self.sysReset_Button.grid(row=9, column =3, sticky=W)

		self.quit_Button=Button(self, text="Quit", width=5,
								command=self.close_window)

		self.quit_Button.grid(row=9, column=4, sticky=E)
		
		# self.terminalWindow=Entry(self)
		# self.terminalWindow.grid(row=9,pady=10, columnspan=6,rowspan=2, sticky=W+E)
	#GPIO Initialization	
	# try:
	# 	# driverLoadCheck = subprocess.check_output(["./driverCheck.sh"])
	# 	# print(driverLoadCheck)
	# 	# pass terminal commands through python subprocess functions

	# 	# convert to os.system()
	# 	cmd = "lsmod |grep 'ite8516k'"
	# 	ps = subprocess.Popen(cmd,shell=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
	# 	output = ps.communicate()[0]
	# 	print (output)
	# 	print("drivers loaded.")
		
	# except:
	# 	print("fail - driver not found")
	# 	exit(1)
		

# ==========================================================================================
	def LatchResetButtonPress(self, buttonName):
		
		if buttonName == "latchOn":
			try:
				print("latch on")
				currentState = subprocess.check_output(["cat", "/sys/class/gpio/gpio7/direction"])
				os.system(r'sudo sh -c "echo out > /sys/class/gpio/gpio7/direction"')
				time.sleep(.100)
			except:
				print("failed. Check driver...")
		if buttonName == "latchOff":
			try:
				currentState = subprocess.check_output(["cat", "/sys/class/gpio/gpio7/direction"])
				print("latch off")
				os.system(r'sudo sh -c "echo in > /sys/class/gpio/gpio7/direction"')
				time.sleep(.100)
			except:
				print("failed. Check driver...")				
		if buttonName =="sysReset":
			try:
				print("reset")
				#adding subprocess, allows a check and exception handling to work properly
				currentState = subprocess.check_output(["cat", "/sys/class/gpio/gpio7/direction"])
				os.system(r'sudo sh -c "echo in > /sys/class/gpio/gpio7/direction"')
				time.sleep(.300)
				os.system(r'sudo sh -c "echo out > /sys/class/gpio/gpio7/direction"')
				#set status to off
			except:
				print("failed. Check driver...")


	def LEDbuttonPress(self, buttonName):
	"""	Handles the LED button press, by changing GPIO direction on SYS_Pause 
		and Sys_act buttons.
		NOTE: IN = off, OUT = on
	"""

		if buttonName == "sys_pause":
			try:
				# gets sys_pause gpio values
				currentState = subprocess.check_output(["cat", "/sys/class/gpio/gpio6/value"])
				currentState = str(currentState.decode('ascii').strip('\n'))

				if currentState == "0":
					# 'r' is used to pass quotes in os.system
					# Turns on LED light
					os.system(r'sudo sh -c "echo out > /sys/class/gpio/gpio6/direction"')
					self.sysPauLED_Button.config(text="LED ON")
					Style().configure('ledSysPause.TButton', relief=SUNKEN,foreground="#FFFFFF", \
										background ="#ffad33")
				else:
					# Turns OFF LED light
					os.system(r"sudo sh -c 'echo in > /sys/class/gpio/gpio6/direction'")
					self.sysPauLED_Button.config(text="LED Off")
					Style().configure('ledSysPause.TButton', background="#d9d9d9",foreground="#000000", \
										relief=RAISED)
			except:
				print("failed. Check driver...")

		if buttonName == "sys_act":
			try:
				# gets the sys_act gpio Values
				currentState = subprocess.check_output(["cat", "/sys/class/gpio/gpio4/value"])
				currentState = str(currentState.decode('ascii').strip('\n'))

				if currentState == "0":
					print("sys_pause success")
					os.system(r'sudo sh -c "echo out > /sys/class/gpio/gpio4/direction"')
					self.sysActLED_Button.config(text="LED ON")
					Style().configure('ledSysAct.TButton', relief=SUNKEN,foreground="#FFFFFF", \
					background ="#000099", activebackground='black', activeforground='black')
				else:
					os.system(r"sudo sh -c 'echo in > /sys/class/gpio/gpio4/direction'")
					self.sysActLED_Button.config(text="LED Off")
					Style().configure('ledSysAct.TButton', background="#d9d9d9", foreground="#000000",\
										relief=RAISED,  activebackground='black', activeforeground='black')
			except:
				print("failed. Check driver...")

	
	def getGpioState(self):
	""" Retrieve states for all gpios and updates the GUI based on state """
		
		for x in gpioList:
			
			try:
				self.gpio0_entry.config(state=NORMAL)
				state = subprocess.check_output(["cat", "/sys/class/gpio/gpio"+x+"/value"])
				# state = subprocess.check_output(["cat", "/sys/class/hwmon/hwmon0/temp1_input"])
				state = str(state.decode('ascii').strip('\n'))
				# print ("state: "+str(state) + " x: "+x)
				
			except:
				state = "N/A" #extra * character to be trimmed properly

			tempSyntax = "self."+"gpio"+ x + "_entry.delete(0,END)"
			# [:-1] is to trim last buffer value
			tempSyntax2 = "self." + "gpio"+ x +"_entry.insert(END, state)"	
			exec(tempSyntax)
			exec(tempSyntax2)
			
			# get gpio_0 values SYS_PAUSE and SYS_ACTIVATE
			gpio0_Value = str(self.gpio0_entry.get())
			gpio9_Value = str(self.gpio9_entry.get())
			
			if gpio0_Value == "1" and gpio9_Value =="1":
				self.sysPauseLabelOnOff.config(text="ON", background='#42f4ad', \
												foreground='#FFFFFF', relief=RAISED)
			else:
				self.sysPauseLabelOnOff.config(text="OFF",background='#d9d9d9', \
												relief=SUNKEN,foreground='gray')
			
			# get gpio_1 and gpio_8 values #SYS_ACTIVATE
			gpio1_Value = str(self.gpio1_entry.get())
			gpio8_Value = str(self.gpio8_entry.get())

			if gpio1_Value == "0" and gpio8_Value =="0": 
				self.sysActLabelOnOff.config(text="ON", background='#42f4ad', \
											foreground='#FFFFFF', relief=RAISED)
			else:
				self.sysActLabelOnOff.config(text="OFF",background='#d9d9d9', \
											relief=SUNKEN,foreground='gray')

			gpio2_Value = str(self.gpio2_entry.get())
			if gpio2_Value == "1":
				self.sysLatch_OnOffIndicator_Label.config(background='#42f4ad', \
														foreground='#FFFFFF', \
														relief=RAISED)
			else:
				self.sysLatch_OnOffIndicator_Label.config(background='#d9d9d9', \
				relief=SUNKEN,foreground='gray')
			# self.gpio_entry.config(state=DISABLED)

	
	def gpioReset(self):
	'''Resets the GPIO directions back to their default ("off"/IN positions) on exit.
		Reads gpio directions for GPIO 4,6,7 and resets the direction if they are left
		on prior to exiting application.
	'''
		for gpioNumber in (4,6,7):
			# Get the current values of all gpios
			try:
				state = subprocess.check_output(["cat", "/sys/class/gpio/gpio"+str(gpioNumber)+"/direction"])
				state = str(state.decode('ascii').strip('\n'))
				time.sleep(.100)
				
				if state =="out":  
					print("GpioNumber: " +str(gpioNumber)+ "state: " +str(state))
					os.system(r"sudo sh -c 'echo in > /sys/class/gpio/gpio"+str(gpioNumber)+"/direction'")

			except:
				print("Gpio"+str(gpioNumber)+" not found.")
				state="0"

	def updater(self):
		self.getGpioState()
		self.after(GPIO_Tester.UPDATER_DELAY, self.updater)

	def close_window(self):
		if messagebox.askokcancel("Quit", "Are you sure you want to quit?"):
			try: 
				self.gpioReset()
				print("shutdown and reset all gpios")
				print("shutdown successful")
			except OSError as err:
				print("file close failed")
			
			self.main.destroy()
	
def main():

	root = Tk()
	
	root.geometry("500x400+300+300")
	root.resizable(False, False)
	app = GPIO_Tester(root)

	root.protocol("WM_DELETE_WINDOW", app.close_window) #re-route back from main to self
	root.mainloop()

	

if __name__ == '__main__':
	main() 