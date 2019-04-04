#!/usr/bin/python3

# from tkinter import Tk, W, E, Label, Menu
from tkinter import *
from tkinter.ttk import Frame, Button, Entry, Style



import tkinter as ttk
import tkinter.ttk as ttk
import subprocess
import shlex # shell lexical analysis of the shell-style syntaxes
import time

class GPIO_Tester(Frame):
	global gpioList; gpioList = ["0", "1", "2", "4", "6", "7", "8","9"]
	UPDATER_DELAY = 300 #ms
	gpio_state = 'RAISED';


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
		#*************************************************************	

	
	def __init__(self, main):
	
		gpio0_status = ""
		gpio1_status = ""
		gpio2_status = ""
	
		super().__init__()
		self.main=main
		self.initUI(main)
		
		self.master.title("GPIO Tester Application")
		
		#self.createMenu()

		Style().configure("TButton", padding=(0,5,0,5))
		


		self.columnconfigure(0, pad=30)
		self.columnconfigure(1, pad=30)
		self.columnconfigure(2, pad=30)
		self.columnconfigure(3, pad=30)

		self.rowconfigure(0, pad=3)
		self.rowconfigure(1, pad=3)
		self.rowconfigure(2, pad=3)
		self.rowconfigure(3, pad=3)
		self.rowconfigure(4, pad=3)
		self.rowconfigure(5, pad=3)
		self.rowconfigure(6, pad=3)

		# entry = Entry(self)
		# entry.grid(row=0, columnspan=4, sticky=W+E)
		#entry.grid(row=0, column=1)

		# ROW 0 - blank row for spacing 
		label = Label(self, text=" ")
		label.grid(row=0, columnspan=4)

		# ROW 1 - Labels
		gpio0Label = Label(self, text="Gpio 0")
		gpio0Label.grid(row=1, column=0)

		gpio1Label = Label(self, text="Gpio 1")
		gpio1Label.grid(row=1, column=1)

		gpio2Label = Label(self, text="Gpio 2")
		gpio2Label.grid(row=1, column=2)

		gpio4Label = Label(self,text="Gpio 4")
		gpio4Label.grid(row=1, column=3)


		#****Button theme declarations ******
		SUNKABLE_BUTTON = 'SunkableButton.TButton'
		self.style1=ttk.Style()
		print(GPIO_Tester.gpio_state  )
		style_var = self.style1.configure(SUNKABLE_BUTTON, relief=RAISED)
		#Style().configure(self.style1, padding=(0,5,0,5), relief=SUNKEN)

		# ROW 2 - GPIO 0 - 3 - ***must use lamda statements for command
		# self.gpio0 = Button(self, text="IN",style=SUNKABLE_BUTTON, command=lambda:self.buttonPressed("1"))
		self.gpio0=Button(self, text="IN", command= \
			lambda: self.buttonPressed("1", style_var), style=SUNKABLE_BUTTON)
		self.gpio0.grid(row=2, column=0)
		
		gpio1 = Button(self, text="IN", command=self.getGpioState)
		gpio1.grid(row=2, column=1)

		gpio2 = Button(self, text="IN")
		gpio2.grid(row=2, column=2)

		gpio3 = Button(self, text="IN")
		gpio3.grid(row=2, column=3)
		
		#ROW 3 - GPIO Entry/Status row for GPIOs 0-3
		self.gpio0_entry = Entry(self, width=10)
		self.gpio0_entry.grid(row=3, column=0)

		self.gpio1_entry = Entry(self, width=10, foreground="#000000",background="green")
		self.gpio1_entry.grid(row=3, column=1)

		self.gpio2_entry = Entry(self, width=10)
		self.gpio2_entry.grid(row=3, column=2)
		
		self.gpio4_entry = Entry(self, width=10)
		self.gpio4_entry.grid(row=3, column=3)
	
		#ROW 4 - blank spacer row
		label = Label(self, text=" ")
		label.grid(row=4, columnspan=4)

		#ROW 5 - Labels GPIO 6-9,
		gpio6Label = Label(self, text= "Gpio 6")
		gpio6Label.grid(row=5, column=0)

		gpio7Label = Label(self, text="Gpio 7")
		gpio7Label.grid(row=5, column=1)

		gpio8Label = Label(self, text="Gpio 8")
		gpio8Label.grid(row=5, column=2)

		gpio9Label = Label(self, text="Gpio 9")
		gpio9Label.grid(row=5, column=3)

		#ROW 6 - GPIO 6-9
		gpio6 = Button(self, text="IN")
		gpio6.grid(row=6, column=0)
		
		gpio7 = Button(self, text="IN")
		gpio7.grid(row=6, column=1)

		gpio8 = Button(self, text="IN")
		gpio8.grid(row=6, column=2)
		
		gpio9 = Button(self, text="IN")
		gpio9.grid(row=6, column=3)

		#Row 7 - Entry/Status for GPIOs 6-9
		self.gpio6_entry = Entry(self,width=10)
		self.gpio6_entry.grid(row=7, column=0)

		self.gpio7_entry = Entry(self, width=10)
		self.gpio7_entry.grid(row=7, column=1)

		self.gpio8_entry = Entry(self, width=10)
		self.gpio8_entry.grid(row=7, column=2)

		self.gpio9_entry = Entry(self, width=10)
		self.gpio9_entry.grid(row=7, column=3)

		
		self.createMenu()
		self.updater()
		self.pack()

	



	# def action1(self):
	# 	fileObject = open("/sys/class/hwmon/hwmon1/temp1_max", "r")
	# 	content=fileObject.read()
	# 	fileObject.close()
	# 	self.gpio0_entry.delete(0,END)
	# 	self.gpio0_entry.insert(END, content[:-4])
		
	# 	print("command working.")
		
	# 	while True:
	# 		try: 
	# 			self.gpio1_entry.delete(0,END)
	# 			time.sleep(.1)
	# 			gpio_data = subprocess.check_output(["cat","/sys/class/hwmon/hwmon3/fan1_input"],stderr=subprocess.STDOUT)
				
	# 			line=gpio_data.readline()
	# 			print(line)
	# 			self.gpio1_entry.insert(END,gpio_data[:-1])
	# 			#print("output is {}".format(agpio_data))

	# 			print(str(inchar), end='')
	# 		except ValueError:
	# 			print("Error")
	# 			break
	

	# def action2(self):
	
	# 	p = subprocess.check_output(["cat","/sys/class/hwmon/hwmon3/fan1_input"])
	# 	#process = subprocess.Popen(shlex.split((["cat", "/sys/class/hwmon/hwmon3/fan1_input"])), stdout=subprocess.PIPE)
	# 	# while True:
	# 	#p = subprocess.check(['cat', '/sys/class/hwmon/hwmon3/fan1_input'], stdout=subprocess.PIPE)
	# # 	#print(p.stdout.read())

	# 	#output = str(p.stdout.read())
	# 	self.gpio1_entry.delete(0,END) # delete first interpreted application
	# 	self.gpio1_entry.insert(END,p[:-1] )
	# # 	time.sleep(.5)
	# 	#self.gpio1_entry.delete(0,END)
	# 	#output = process.stdout.readline()
	# 	#output = process.stdout.readline().decode('utf-8')
	# 	# if p == '' and process.poll() is not None:
	# 	# 	break
	# 	# if p:
	# 	#rc = process.poll()

	# 	#return rc

	def buttonPressed(self, gpioNumber, style_var):
		
		style_var = self.style1.configure('SunkableButton.TButton', SUNKEN)
		# style1 = ttk.Style()
		# Style().configure("TButton", relief=SUNKEN, foreground='green')
		
		#tempSyntax = "self" + ".gpio"+ str(gpioNumber) + ".config(relief=SUNKEN)"
		print(gpioNumber+"pressed")
		# self.gpio0.config(bg="red")
		state = 'SUNKEN'
		
		# self.gpio0.configure(relief=SUNKEN)
		# exec(tempSyntax)	
		print(state)
		return style_var

	def getGpioState(self):
		
		for x in gpioList:
			self.gpio1_entry.config(state=NORMAL)
			# p = subprocess.check_output(["cat", "/sys/class/hwmon/hwmon3/fan1_input"])
			try:
				state = subprocess.check_output(["cat", "/sys/class/hwmon/hwmon2/temp1_input"])
				tempSyntax = "self."+"gpio"+ x + "_entry.delete(0,END)"

				# [:-1] is to trim last buffer value
				tempSyntax2 = "self." + "gpio"+ x +"_entry.insert(END, state[:-1])"	
			except:
				print("could not execute subprocess")
			# self.gpio0_entry.delete(0,END)
			# self.gpio0_entry.insert(END,p[:-1])
			# print(x)
			# print(tempSyntax)
			# print(tempSyntax2)
			
			exec(tempSyntax)
			exec(tempSyntax2)
			self.gpio1_entry.config(state=DISABLED)
			
	def GPIO_ChangeDirection(self):
		print("temp")

	def updater(self):
		self.getGpioState()
		#time.sleep(.500)
		self.after(GPIO_Tester.UPDATER_DELAY, self.updater)
	
	def close_window(self):
		if messagebox.askokcancel("Quit", "Are you sure you want to quit?"):
			print("shutdown successful.")
			self.main.destroy()
				

		


def main():

	root = Tk()
	root.geometry("500x280+300+300")
	root.resizable(False, False)
	app = GPIO_Tester()

	root.protocol("WM_DELETE_WINDOW", app.close_window) #re-route back from main to self
	root.mainloop()

	

if __name__ == '__main__':
	main() 