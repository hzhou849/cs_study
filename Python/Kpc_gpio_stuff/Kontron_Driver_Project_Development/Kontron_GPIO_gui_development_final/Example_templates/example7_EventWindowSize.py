from tkinter import *

root = Tk()

def center_window(width=300, height=200):
	w=800 #width for the Tk root
	h=640 #height for the Tk root

	#get the screen width and height
	ws = root.winfo_screenwidth()
	hs = root.winfo_screenheight()

	#calculate x and y coordinates for the Tk root window
	x = (ws/2) - (w/2)
	y = (hs/2) - (h/2)

	# Set the dimensions of the screen and where it is placed
	root.geometry('%dx%d+%d+%d' % (w, h, x, 200))




def leftClick(event):
	print("Left")

def middleClick(event):
	print("Middle")

def rightClick(event):
	print("Right")

frame = Frame(root, width=300, height=250)
frame.bind("<Button-1>", leftClick)
frame.bind("<Button-2>", middleClick)
frame.bind("<Button-3>", rightClick)
frame.pack()

root.title("Example 7")
center_window(500,400)
root.lift()
root.mainloop()