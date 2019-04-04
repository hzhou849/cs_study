#!/usr/bin/python3

# from tkinter import Tk, W, E, Label, Menu
from tkinter import *
from tkinter.ttk import Frame, Button, Entry, Style 
from PIL import Image, ImageTk


# import tkinter as ttk
import tkinter.ttk as ttk
import subprocess
import shlex # shell lexical analysis of the shell-style syntaxes
import time

class GPIO_Tester(Frame):
	global gpioList; gpioList = ["0", "1", "2", "4", "6", "7", "8","9"]
	UPDATER_DELAY = 300 #ms
	gpio_state = "RAISED";
	
	def __init__(self):
		
		
		super().__init__()
		self.master.configure(relief=SUNKEN)
		self.master.title("GPIO Tester Application")
			
		self.styleInit()
		self.rowColInit()

		Style().configure("TFrame", background="#333")
		
		self.row0_label_Init()
		self.row1_label_Init()	
		self.row2_GPIO_Button_Init()
		self.row3_GPIO_Entry_Init()
		self.row4_GPIO_blank()
		
		
		
	
		
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
		self.pack(fill=BOTH, expand=1)

	
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

	def styleInit(self):

		Style().configure("TButton", padding=(0,5,0,5))
		s2 = ttk.Style()
		
		s2.configure('blue.TButton', foreground='orange', background='blue')
	def rowColInit(self):
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
		self.rowconfigure(7, pad=3)
		self.rowconfigure(8, pad=3)

	def row0_label_Init(self):	
		# ROW 0 - blank row for spacing 
		label = Label(self, text=" ")
		label.grid(row=0, columnspan=4)

	def row1_label_Init(self):
		# ROW 1 - Labels
		gpio0Label = Label(self, text="Gpio 0")
		gpio0Label.grid(row=1, column=0)

		gpio1Label = Label(self, text="Gpio 1")
		gpio1Label.grid(row=1, column=1)

		gpio2Label = Label(self, text="Gpio 2")
		gpio2Label.grid(row=1, column=2)

		gpio4Label = Label(self,text="Gpio 4")
		gpio4Label.grid(row=1, column=3)

	def row2_GPIO_Button_Init(self):

		# buttonImage= Image.open('analytics.png')
		# self.buttonPhoto = ImageTk.PhotoImage(buttonImage)

		#****Button theme declarations ******
		SUNKABLE_BUTTON = 'SunkableButton.TButton'
		self.style1=ttk.Style()
		print(GPIO_Tester.gpio_state  )
		style_var = self.style1.configure(SUNKABLE_BUTTON, relief=RAISED, )
		#Style().configure(self.style1, padding=(0,5,0,5), relief=SUNKEN)
		
		# ROW 2 - GPIO 0 - 3 - ***must use lamda statements for command
		# self.gpio0 = Button(self, text="IN",style=SUNKABLE_BUTTON, command=lambda:self.buttonPressed("1"))
		# self.gpio0=Button(self, image=self.buttonPhoto, text="IN", command= \
		# 	lambda: self.buttonPressed("1", style_var), style='blue.TButton')

		self.gpio0=Button(self, text="IN", command= \
			lambda: self.buttonPressed("1", style_var), style='blue.TButton')
		# print (str(self.gpio0.config())) - dump button stats
		self.gpio0.grid(row=2, column=0)
		

		self.gpio0.bind("<Enter>", self.on_enter)
		self.gpio0.bind("<Leave>", self.on_leave)

		

		gpio1 = Button(self, text="IN", command=self.getGpioState)
		gpio1.grid(row=2, column=1)

		gpio2 = Button(self, text="IN")
		gpio2.grid(row=2, column=2)

		gpio3 = Button(self, text="IN")
		gpio3.grid(row=2, column=3)

	def	on_enter(self, event):
		self.gpio0.configure(text="mouse over", bg='orange')
		Style().configure("blue.TButton", activebackground='orange')
	def on_leave(self, event):
		self.gpio0.configure(text="mouse leave")
		Style().configure("blue.TButton", activebackground='orange')
	


	def row3_GPIO_Entry_Init(self):
		#ROW 3 - GPIO Entry/Status row for GPIOs 0-3
		self.gpio0_entry = Entry(self, width=10)
		self.gpio0_entry.grid(row=3, column=0)

		self.gpio1_entry = Entry(self, width=10)
		self.gpio1_entry.grid(row=3, column=1)

		self.gpio2_entry = Entry(self, width=10)
		self.gpio2_entry.grid(row=3, column=2)
		
		self.gpio4_entry = Entry(self, width=10)
		self.gpio4_entry.grid(row=3, column=3)

	def row4_GPIO_blank(self):
		#ROW 4 - blank spacer row
		label = Label(self, text=" ")
		label.grid(row=4, columnspan=4)

	

	def buttonPressed(self, gpioNumber, style_var):
		# self.gpio0.state(['pressed','disabled'])
		# self.gpio0.config(state=DISABLED)
		print(str(self.gpio0['state']))
		print("old state: " +self.gpio0.cget('text'))
		currentButtonState =str(self.gpio0.cget('text'))

		if currentButtonState == "OUT":
			Style().configure('blue.TButton', relief=RAISED, foreground='blue')
			self.gpio0.config(text="IN")
			currentButtonState = print ("working"  + self.gpio0.cget('text'))
		else :
			Style().configure('blue.TButton', relief=SUNKEN, foreground='red')
			self.gpio0.config(text="OUT")
			
		# style1 = ttk.Style()
		# Style().configure("TButton", relief=SUNKEN, foreground='green')
		
		#tempSyntax = "self" + ".gpio"+ str(gpioNumber) + ".config(relief=SUNKEN)"
		# print(gpioNumber+"pressed")
		# self.gpio0.config(bg="red")
	
		# self.gpio0.configure(relief=SUNKEN)
		# exec(tempSyntax)	
	

	def getGpioState(self):
		
		for x in gpioList:
			self.gpio1_entry.config(state=NORMAL)
			# p = subprocess.check_output(["cat", "/sys/class/hwmon/hwmon3/fan1_input"])
			state = subprocess.check_output(["cat", "/sys/class/hwmon/hwmon2/temp1_input"])
			tempSyntax = "self."+"gpio"+ x + "_entry.delete(0,END)"

			# [:-1] is to trim last buffer value
			tempSyntax2 = "self." + "gpio"+ x +"_entry.insert(END, state[:-1])"	
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

		


def main():

	root = Tk()
	root.geometry("500x280+300+300")
	root.resizable(False, False)
	app = GPIO_Tester()
	root.mainloop()

	

if __name__ == '__main__':
	main() 