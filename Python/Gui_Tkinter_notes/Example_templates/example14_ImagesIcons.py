#! /usr/bin/env python3
from tkinter import *


root = Tk()

photo = PhotoImage(file="analytics.png")
label = Label(root, image=photo)
label.pack()

root.title("GPIO Application - Graphics")
root.mainloop()