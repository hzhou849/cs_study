#!/usr/bin/env python3

from tkinter import*
from tkinter.ttk import Frame, Button, Entry, Style

import tkinter as ttk
import subprocess

# global gpioList; gpioList = ["0", "1", "2", "4", "6", "7", "8","9"]
global gpioList; gpioList = ["0"]
STATE_BUTTON = 'SunkableButton.TButton'
UPDATER_DELAY = 300
root = Tk()

root.columnconfigure(0, pad=30)
root.columnconfigure(1, pad=30)
root.columnconfigure(2, pad=30)

root.rowconfigure(0, pad=3)
root.rowconfigure(1, pad=3)
root.rowconfigure(2, pad=3)
root.rowconfigure(3, pad=3)

style=Style()

def start():
	button.state(['pressed', 'disabled'])
	style.configure(STATE_BUTTON, relief=SUNKEN, disabledbackground='green')

def stop():
	button.state(['!pressed', '!disabled'])
	style.configure(STATE_BUTTON, relief=RAISED, foreground='red')

def getGpioState():

	for x in gpioList:
			gpio0_entry.config(state=NORMAL)
			# p = subprocess.check_output(["cat", "/sys/class/hwmon/hwmon3/fan1_input"])
			state = subprocess.check_output(["cat", "/sys/class/hwmon/hwmon2/temp1_input"])
			tempSyntax = "gpio"+ x + "_entry.delete(0,END)"

			# [:-1] is to trim last buffer value
			tempSyntax2 = "gpio"+ x +"_entry.insert(END, state[:-1])"	
			# self.gpio0_entry.delete(0,END)
			# self.gpio0_entry.insert(END,p[:-1])
			# print(x)
			# print(tempSyntax)
			# print(tempSyntax2)
			
			exec(tempSyntax)
			exec(tempSyntax2)
			# gpio1_entry.config(state=DISABLED)

button=Button(root, text="Start", command=getGpioState, style=STATE_BUTTON)
button.grid(row=0, column=0)

button2=Button(root, text="Stop", command=stop).grid(row=0, column=1)

gpio0_entry = Entry(root, width=10)
gpio0_entry.grid(row=1, column=0)


def updater():
	root.getGpioState()
	#time.sleep(.500)
	root.after(GPIO_Tester.UPDATER_DELAY, self.updater)

	
updater()
root.mainloop()
