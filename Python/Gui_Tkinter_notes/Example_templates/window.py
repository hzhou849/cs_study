'''
	May not work because of indentation issues
'''

#!/usr/bin/env python3

from tkinter import Tk, BOTH
from tkinter.ttk import Frame

class Example(Frame):

	def __init__(self):
		super().__init__()
		#calls constructor method 
		self.initUI__() 

	def initUI(self):
		self.master.title("GPIO_Application")
		self.pack(fill=BOTH, expand=1)


def main():
	root = Tk()
	root.geometry("250x150+300+300")
	app = Example()
	root.mainloop()


if __name__ == '__main__':
	main()