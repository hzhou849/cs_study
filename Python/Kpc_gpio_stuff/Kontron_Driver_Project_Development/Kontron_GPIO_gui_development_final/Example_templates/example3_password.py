from tkinter import *

root = Tk()

label_1 = Label(root, text="Name")
label_2 = Label(root, text="Password")
entry_1 = Entry(root)
entry_2 = Entry(root)

# sticky will allow you to align placement  N E S W top, right, bottom, left
label_1.grid(row=0, sticky=E)
label_2.grid(row=1, sticky=E)

entry_1.grid(row=0, column=1)
entry_2.grid(row=1, column=1)

# Check buttons
c = Checkbutton(root, text="Keep me logged in")
c.grid(columnspan=2,row=2)


# Main window execution stuff
root.title("GPIO app")
root.mainloop()
