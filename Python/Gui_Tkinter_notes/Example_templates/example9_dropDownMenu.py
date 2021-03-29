from tkinter import *

def function1():
	print("working")


root = Tk()
# Creates menu object to be placed in root window
menuObject = Menu(root)
root.config(menu=menuObject)

# creates submenu for the menu
subMenu = Menu(menuObject, tearoff=0)

# add menu button
menuObject.add_cascade(label="File", menu=subMenu)
subMenu.add_command(label="New Project...", command=function1)
subMenu.add_command(label="New...", command=function1)
subMenu.add_separator()
subMenu.add_command(label="Exit", command=root.quit)


editMenu = Menu(menuObject, tearoff=0)
menuObject.add_cascade(label="Edit", menu=editMenu)
editMenu.add_command(label="Redo", command=function1)


root.title("GPIO Application")
root.mainloop()