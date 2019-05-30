#! /usr/bin/python3

'''
Using the self.after method to refresh the GUI

not the best way as the loop can run uncontrolled. but good for quick prototype.

'''

import tkinter
import os




class ApplicationWindow(tkinter.Frame):	#must use tinker.Frame to prevent a random window tk# from opening
	'''
	the def __init__(self, master):
			super().__init__() ** keyword used for selfupdater loop scheduler
	    def initUI(self, master): 
	format must be used in order to have the self.after updater to work.
	'''

	def __init__(self, master): # master is this instance of the parent window/Frame
		super().__init__()
		self.master=master
		self.initUI(master)

	def initUI(self, master):
		self.master.title("Advanced GUI loop+ template v1.0")
		self.master.geometry('640x480+200+200')
		self.master.attributes("-topmost", True)
		self.master['padx'] = 8

		# Create Menu components
		menuObject = tkinter.Menu(self.master)			# create the Menubar object
		self.master.config(menu=menuObject)				# Menubar to the main window
		fileMenu=tkinter.Menu(menuObject, tearoff=0)
		menuObject.add_cascade(label="File", menu=fileMenu) 
		fileMenu.add_command(label="Exit", command=self.onExit)


		# Create Function buttons
		self.button1 = tkinter.Button(self.master, width=10, text="Quit", command=self.onExit)	
		self.button1.grid(row=4, column=2, sticky='w')

		# Create the Main Window Grid
		self.master.columnconfigure(0, weight=100)
		self.master.columnconfigure(1, weight=1)
		self.master.columnconfigure(2, weight=1000)
		self.master.columnconfigure(3, weight=6)
		self.master.columnconfigure(4, weight=1000)
		self.master.rowconfigure(0,weight=1)
		self.master.rowconfigure(1, weight=10)
		self.master.rowconfigure(2, weight=1)
		self.master.rowconfigure(3, weight=3)
		self.master.rowconfigure(4, weight=3)

		#Create the File list box, data items and scrollbar
		self.fileList = tkinter.Listbox(self.master)
		self.fileList.grid(row=1, column=0, sticky='nsew', rowspan=2)
		self.fileList.config(border=2, relief='sunken')

		for item in os.listdir('/usr/bin'):
			self.fileList.insert(tkinter.END, item)
		
		self.listScroll = tkinter.Scrollbar(self.master, orient=tkinter.VERTICAL, command=self.fileList.yview)
		self.listScroll.grid(row=1, column=1, sticky='nsw', rowspan=2)

		self.fileList['yscrollcommand'] = self.listScroll.set # add the scrollbar to fileList box

		#Create a frame for the radio button group
		self.optionFrame = tkinter.LabelFrame(self.master, text="File Details")
		self.optionFrame.grid(row=1, column=2, sticky='ne')

		#Radio Button
		self.rbValue = tkinter.IntVar()
		self.rbValue.set(1)
		self.radio1 = tkinter.Radiobutton(self.optionFrame, text="Filename",  variable=self.rbValue, value=1,command=lambda:self.update(1))
		self.radio2 = tkinter.Radiobutton(self.optionFrame, text="Path",  variable=self.rbValue, value=2,command=lambda:self.update(2))
		self.radio3 = tkinter.Radiobutton(self.optionFrame, text="Timestamp",  variable = self.rbValue, value=3,command=lambda:self.update(3))

		self.radio1.grid(row=0, column=0, sticky='w')
		self.radio2.grid(row=1, column=0, sticky='w')
		self.radio3.grid(row=2, column=0, sticky='w')

		#Result Label
		
		self.resultLabel = tkinter.Label(self.master, text="Result")
		self.resultLabel.grid(row=2, column=2, padx=8, sticky='nw')
		self.result = tkinter.Entry(self.master)
		self.result.grid(row=2, column=2, sticky='sw', padx=10) #pad the x/y directly
		print('testing')
		print(self.rbValue.get())
		self.result.insert(0,str(self.rbValue.get()))
		self.tester()


	def update(self,value):
		print("go" + str(value))
		self.result.delete(0)
		self.result.insert(0,str(self.rbValue.get()))

	def tester(self):
		print(self.rbValue.get())
		self.loop_id=self.after(200, self.tester)

		

	def onExit(self):
		print(self.loop_id)
		# self.master.after_cancel(self.tester) # kill the scheduled self.after loop
		self.master.destroy()
		# self.master.after_cancel(self.loop_id) # don't really need

def main():
	root = tkinter.Tk()				# Create tkinter
	app =ApplicationWindow(root)    # Create a class instance and pass root and execute
	root.mainloop()					# run the mainloop

if __name__ == '__main__':
	main()