#!/usr/bin/python3

'''
Copyright 2018 Medtronic.
All Rights Reserved. The information contained herein is confidential
property of Medtronic. The use, copying, transfer or disclosure of such
information is prohibited except by written agreement with Medtronic. 
'''
from tkinter import *
from tkinter.ttk import Frame, Button, Entry, Style

class Fan_App(Frame):
	def __init__(self, master):
		frame = Frame(master)
		frame.pack()
		self.text=Text()
		self.text.pack()

		menu = Menu(master)
		root.config(menu=menu)

		#file menu
		filemenu = Menu(menu, tearoff=0)
		menu.add_cascade(label="File", menu=filemenu)
		filemenu.add_command(label="New")
		filemenu.add_command(label="Open", command=self.file_open)
		filemenu.add_command(label="Save", command=self.file_save)
		filemenu.add_separator()
		filemenu.add_command(label="Exit", command=self.do_exit)

	def file_open(self):
		
		#Optional initial directory to look at
		initial_dir = "/home/howardz/"

		#the filetype mask (default is all files)
		mask = \
		[("Text and Python files", "*.txt *.py *.pyw"),
		("HTML Files", "*htm"),
		("All files", "*.*")]
		fin = askopenfile(initialDir = initial_dir, filetypes=mask, mode='r')
		text = fin.read()
		if text != None:
			self.text.delete(0.0, END)
			self.text.insert(END,txt)
	