#! /usr/bin/python3

'''
Advance GUI Class layout Template

Stable implementation of utilizing both self.after updater loop and 
seperatae thread

added - GUI threadpool
added - self.after schdeduled loop
'''

import tkinter
import os
import time
import threading
import queue		# thread queue object

class ApplicationWindow(tkinter.Frame):
	def __init__(self, master): # master is this instance of the parent window/Frame
		super().__init__()
		self.master=master
		self.qObj = queue.Queue(1)  # create thread queue max size 1

		self.t1 = threading.Thread(target=self.threadpool, args=("Thread-1", self.qObj))
		self.t1.start()
	
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

		#kickoff the threadpool
		



	def update(self, value):
		print("go" + str(value))
		self.result.delete(0)
		self.result.insert(0,str(self.rbValue.get()))

	def tester(self):
		print(self.rbValue.get())
		self.after(500, self.tester)

	def threadpool(self,threadName, q):
		'''
		Threadpool spins until queue >0, condition 9 for kill code as part of join/termination process.
		'''

		while True:
			if q.qsize() == 0:
				print("thread sleeping...")
				time.sleep(0.5)

			q_value = q.get() 		# This will block until it receives an item 
			if q_value == "_SIG_KILL":
				print("q_value: {0}".format(q_value))
				print("Kill signal received, terminating thread")
				return				# exit the thread function allow join()

			print("a: {0}".format(q_value))

	def thread_task_generator(self, q):
		for i in range (0, 10):
			i += 1
			q.put(i)
			time.sleep(2)

	def onExit(self):
		
		#join the thread.
		# self.after_cancel(self.update_loop)
		self.qObj.put("_SIG_KILL")
		self.t1.join()
		self.master.destroy()
		# self.after_cancel(self.loop_id)

def main():
	root = tkinter.Tk()				# Create tkinter
	app =ApplicationWindow(root)    # Create a class instance and pass root and execute
	root.mainloop()					# run the mainloop

if __name__ == '__main__':
	main()