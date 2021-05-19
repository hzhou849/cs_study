from tkinter import *


class GPIO_Application:
	
	# Function will self initialize on object creation
	def __init__(self, master):
		frame = Frame(master)
		frame.pack()

		self.printButton = Button(frame, text="Print Message", command=self.printMessage)
		self.printButton.pack(side=LEFT)

		self.quitButton = Button(frame, text="Quit", command=frame.quit)
		self.quitButton.pack(side=LEFT)

	def printMessage(self):
		print("call function")



root = Tk()

# must pass main window root

root.geometry('%dx%d+%d+%d' % (600,640,200, 100))
classObject = GPIO_Application(root)
root.title("GPIO Application")
root.mainloop()