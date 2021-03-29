from tkinter import * 
import tkinter.messagebox


root = Tk()
tkinter.messagebox.showinfo('Warning', 'Status updated.')

answer = tkinter.messagebox.askquestion('Question1','true false?')

if answer == 'yes':
	print("success")

	
root.title("GPIO Application")
root.mainloop()