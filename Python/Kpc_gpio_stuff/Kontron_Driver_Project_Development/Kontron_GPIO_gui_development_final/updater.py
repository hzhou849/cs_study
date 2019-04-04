#!/usr/bin/python3
from tkinter import *
import os
# import tkinter

UPDATE_RATE = 1000

class Application(Frame):
	
	def __init__(self, master):
		super().__init__()
		self.grid()
		self.create_widgets()
		self.updater()

	def create_widgets(self):
	
		self.button1 = Button(self)
		self.button1["text"] = "Router"
		self.button1["fg"] = "white"
		self.button1.grid(row=0, column=5)

	def update_button1(self):
		hostname = "192.168.0.1"
		response = os.system("ls" )
		print(response)
		if response == 0:
			self.button1["bg"] = "green"
		else:
			self.button1["bg"] = "red"
	
	def updater(self):
		self.update_button1()
		self.after(UPDATE_RATE, self.updater)

root = Tk()
root.title("Monitor")
app=Application(root)
root.mainloop()
