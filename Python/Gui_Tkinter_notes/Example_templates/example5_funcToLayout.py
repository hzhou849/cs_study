from tkinter import *

root = Tk()

def printName():
	print("Hello world!")
	label1=Label(root, text="Hello world!!", bg="red", fg="white")
	label1.grid(row=1)

button_1 = Button(root, text="Execute", command=printName)
button_1.grid(row=0)

root.title("My Application")
root.mainloop()
