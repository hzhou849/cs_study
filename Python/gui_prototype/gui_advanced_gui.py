#! /usr/bin/python3
'''
Advance GUI layout Template
'''

#create Menu components




import tkinter
import os

def onExit():
	mainWindow.destroy()

#Create the main window 
mainWindow = tkinter.Tk()
mainWindow.title("Grid Advanced v1.0")
mainWindow.geometry('640x480+200+200')
mainWindow.attributes("-topmost", True)
mainWindow['padx'] = 8								# Pads the sides of the main window, so frames don't line up directly to the edge

# Create Menu components 
menuObject=tkinter.Menu(mainWindow) 				# create the Menubar object
mainWindow.config(menu=menuObject) 					# Menubar to the main window
fileMenu=tkinter.Menu(menuObject, tearoff=0)
menuObject.add_cascade(label="File", menu=fileMenu) # create the menu category
fileMenu.add_command(label="Exit", command=onExit) 	# create a command and add it to a category 


#Make label span across horizontally 
label=tkinter.Label(mainWindow, text="Tkinter Advanced Grid")
label.grid(row=0, column=0, columnspan=3)

mainWindow.columnconfigure(0, weight=100)
mainWindow.columnconfigure(1, weight=1)		 # give the scrollbar a weight 0 so when it resizes it will not shrink
mainWindow.columnconfigure(2, weight=1000)
mainWindow.columnconfigure(3, weight=6)
mainWindow.columnconfigure(4, weight=1000)
mainWindow.rowconfigure(0, weight=1)
mainWindow.rowconfigure(1, weight=10)
mainWindow.rowconfigure(2, weight=1)
mainWindow.rowconfigure(3, weight=3)
mainWindow.rowconfigure(4, weight=3)

fileList = tkinter.Listbox(mainWindow)
fileList.grid(row=1, column=0, sticky='nsew', rowspan=2)	#other options: flat, grooved, raised, ridged, solid, sunken
fileList.config(border=2, relief='sunken')


# Create a File list box with scroll bar 
'''
	when inserting into a list box you need to specify the insertion 
	point, in this case at the END
	windows '/windows/System32'
'''
for item in os.listdir('/usr/bin'):
	fileList.insert(tkinter.END, item) 

listScroll = tkinter.Scrollbar(mainWindow, orient=tkinter.VERTICAL, command=fileList.yview)
listScroll.grid(row=1, column=1, sticky='nsw', rowspan=2)

fileList['yscrollcommand'] = listScroll.set			#add the scroll bar to fileList Box

#Create a frame for the radio button group 
'''Label frame is similar to frame but allows for a caption title'''
optionFrame = tkinter.LabelFrame(mainWindow, text="File Details")
optionFrame.grid(row=1, column=2, sticky ='ne')


# Radio button
'''radio buttons share the same variable so that one is selected at a time'''
rbValue = tkinter.IntVar()
rbValue.set(1) 					# set the default value on startup
radio1 = tkinter.Radiobutton(optionFrame, text="Filename", value =1, variable=rbValue)
radio2 = tkinter.Radiobutton(optionFrame, text="path", value =2, variable=rbValue)
radio3 = tkinter.Radiobutton(optionFrame, text="Timestamp", value =3, variable=rbValue)

radio1.grid(row=0, column=0, sticky='w')
radio2.grid(row=1, column=0, sticky='w')
radio3.grid(row=2, column=0, sticky='w')


# Result Label 
resultLabel = tkinter.Label(mainWindow, text="Result")
resultLabel.grid(row=2, column=2, padx=8, sticky='nw')
result = tkinter.Entry(mainWindow)
result.grid(row=2, column=2, sticky='sw', padx=10) #---> pad the grid x/y directly

# Frame for Time Spinner widgets
timeFrame = tkinter.LabelFrame(mainWindow, text="Time")
timeFrame.grid(row=3, column=0, sticky='new', pady=10)

# Create the Time spinners
hourSpinner = tkinter.Spinbox(timeFrame, width=2, values=tuple(range(0, 24))) # 0-23 {zero-indexed} tuple is good for list ie calendar months, days etc..
minuteSpinner = tkinter.Spinbox(timeFrame, width=2, from_=0, to=59) # from is a reserved word from python main scope tkinter uses '_'
secondSpinner = tkinter.Spinbox(timeFrame, width=2, from_=0, to=59)

hourSpinner.grid(row=0, column=0)
tkinter.Label(timeFrame, text=':').grid(row=0, column=1)
minuteSpinner.grid(row=0, column=2)
tkinter.Label(timeFrame, text=':').grid(row=0, column=3)
secondSpinner.grid(row=0, column=4)
timeFrame['padx'] = 36 		#edit attribute directly to pad and center out the spinners in frame



# Frames for date spinners
dateFrame = tkinter.Frame(mainWindow)
dateFrame.grid(row=4, column=0, sticky='new')
# Date Labels
dayLabel = tkinter.Label(dateFrame, text="Day")
monthLabel = tkinter.Label(dateFrame, text="Month")
yearLabel = tkinter.Label(dateFrame, text="Year")

dayLabel.grid(row=0, column=0, sticky='w')
monthLabel.grid(row=0, column=1, sticky='w')
yearLabel.grid(row=0, column=2, sticky='w')
#Date spinners
daySpin = tkinter.Spinbox(dateFrame, width=5, from_=1, to=31)
monthSpin = tkinter.Spinbox(dateFrame, width=5, values=("Jan", "Feb", "Mar", "Apr", "May", "June", "July","Aug", "Sep", "Oct", "Nov", "Dec"))
yearSpin = tkinter.Spinbox(dateFrame, width=5, from_=2000, to=2099)
daySpin.grid(row=1, column=0)
monthSpin.grid(row=1, column=1)
yearSpin.grid(row=1, column=2)


# Buttons
okButton = tkinter.Button(mainWindow, text="OK")
okButton.grid(row=4, column=3, sticky='e')		#sticky 'e' pushes the ok button ---> to make the buttons grouped as close as possible

'''root.quit() - built in command to destroy the window, but use destroy instead,  
	as quit() will destroy the interpreter whereas destroy() will properly stop the 
	mainloop and widgets and child widgets.

	command=<function_name> the reason you are only putting a function name here 
	instead of the function() call syntax is because you do not want the function to
	run until the button is pressed. Typing parenthesis makes the python interpretor
	think you are doing a function call and it will try to execute the fucntion 
	as the interpretor sees it in this case, it will destroy the widgets prematurely

'''
cancelButton = tkinter.Button(mainWindow, text="Cancel", command=mainWindow.destroy) 	#mainWindow.quit() can work, but not advised.
cancelButton.grid(row=4, column=4, sticky='w')		# sticky 'w' pushes the cancel button <--- to make the buttons grouped as close as possible




print(rbValue.get()) #printout the rbValue clicked
print()

# Mainloop
'''
passes control to TK main tkinter mainloop method to handle 
all the GUI event handling/processing
'''
mainWindow.mainloop()