#! /usr/bin/env python3
import tkinter as tk



class AppName(tk.Frame):
	def __init__(self, master=None):
		tk.Frame.__init__(self, master)
		self.grid()
		self.createWidgets()
	
	def createWidgets(self):
		self.quitButton = tk.Button(self, text='Quit', command=self.quit)
		self.quitButton.grid()

app = AppName()
app.master.title("GPIO Application")
app.master.iconbitmap('./icon.ico')
app.mainloop()