#!/usr/bin/python3
from tkinter import *
from tkinter.messagebox import *

def show_change():
	Ans = int(num1.get()) + int(num2.get())
	blank.delete(0,END)
	blank.insert(0,Ans)

main = Tk()
Label(main, text="gpio0:").grid(row=0)
Label(main, text="gpio1:").grid(row=1)
Label(main, text="Changed value:").grid(row=2)

num1=Entry(main)
num2=Entry(main)
blank=Entry(main)

num1.grid(row=0, column=1)
num2.grid(row=1, column=1)
blank.grid(row=2, column=1)

Button(main, text='Quit', command=main.destroy).grid(row=4, column=0)
Button(main, text='Show', command=show_change).grid(row=4, column=1)

mainloop()
