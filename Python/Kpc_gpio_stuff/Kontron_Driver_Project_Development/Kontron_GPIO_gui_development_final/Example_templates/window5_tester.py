#!/usr/bin/env python3

from tkinter import Tk, BOTH
from tkinter.ttk import Frame, Button, Style

class Example(Frame):

	def __init__(self):
		super().__init__()

		self.initUI()

	def initUI(self):
		self.master.title("GPIO Diagnostic Tool")
		self.pack(fill=BOTH, expand=1)
		self.centerWindow()

		quitButton = Button(self, text="Quit", command=self.quit)
		quitButton.place(x=50, y=50)

	def centerWindow(self):
		w = 290
		h = 150

		sw = self.master.winfo_screenwidth()
		sh = self.master.winfo_screenheight()

		x = (sw - w)/2
		y = (sh - h) /2
		self.master.geometry('%dx%d+%d+%d' % (w, h, x, 100))

def main():
	root = Tk()
	app = Example()
	root.mainloop()

if __name__ == '__main__':
	main()