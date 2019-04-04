### Example 10  and 11 is combined in this code

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


# **** Toolbar *******
toolbar = Frame(root, bg="blue")

insertToolBarButton = Button(toolbar, text="Insert Image", command=function1)
insertToolBarButton.pack(side=LEFT, padx=2, pady=2)		 # padx - adds padding
printButton = Button(toolbar, text="Print", command=function1)
printButton.pack(side=LEFT, padx=2, pady=2)


toolbar.pack(side=TOP, fill=X) #display the toolbar on the top, fill=x fills the width of window

# **** Status Bar Indicator *****
status = Label(root, text="GPIO status updated.", bd=1, relief=SUNKEN, anchor=W) # bd is border values, anchor keeps the text west(W)
status.pack(side=BOTTOM, fill=X)

root.title("GPIO Application")
root.mainloop()