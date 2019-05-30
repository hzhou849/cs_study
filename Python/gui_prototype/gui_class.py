#! /usr/bin/python3

'''
TKinter GUI class  - Prototype

Module versions:
import Tkinter - python2
import tkinter - python3 

Tkinter GUI uses a window heirarchy

Demonstrates class GUI  is a proper class layout

A sample class Template for Tkinter GUI 

#import guard for both versions of python
try:
	import tkinter  #for python3
except ImportError: #python 2
	import Tkinter as tkinter


'''

import tkinter

class ApplicationWindow(tkinter.Tk):
	
	def __init__(self, master=None):
		self.master=master
		self.master.geometry('800x400')
		self.master.f_app = tkinter.Frame(self.master).pack()
		menubar=tkinter.Menu(self.master)
		self.master.config(menu=menubar)

		fileMenu=tkinter.Menu(menubar)
		fileMenu.add_command(label="Exit", command=self.onExit)
		menubar.add_cascade(label="File", menu=fileMenu)
		self.b_log=tkinter.Button(self.master, width=10, text="button1", command=self.test).pack()

	def onExit(self):
		self.master.destroy()

	def test(self):
		print("hello")

def main():
	root = tkinter.Tk()
	app=ApplicationWindow(root)
	root.mainloop()


if __name__ == '__main__':
	main()