from tkinter import *

# Creates the main window Object Tk() is constructor
blankWindowObject = Tk()
'''
# Text in Tkinter is a 'label'
theLabel = Label(blankWindowObject,text="blah blah blah")

# Location of where to place the label. pack() is to just place it somewhere.
theLabel.pack()
'''
 

# Create a container/frame
topFrame = Frame(blankWindowObject)
topFrame.pack(side=TOP)

bottomFrame = Frame(blankWindowObject)
bottomFrame.pack(side=BOTTOM)

# Create a button. Must be placed in frames
button1 = Button(topFrame, text="Button1", fg="red")
button2 = Button(topFrame, text="Button2", fg="blue")
button3 = Button(topFrame, text="Button3", fg="green")
button4 = Button(bottomFrame, text="Button 4", fg="purple")

button1.pack(side=LEFT)
button2.pack(side=LEFT)
button3.pack(side=LEFT)
button4.pack(side=BOTTOM)

blankWindowObject.title("GPIO - Application")
# mainloop() GUI needs to infinite loop for updates visual changes
blankWindowObject.mainloop()

