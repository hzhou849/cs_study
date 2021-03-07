#! /usr/bin/python3

'''
TKinter GUI - Prototype using GRID Geometry

GRID Geometry with main window and sub-frames

Grid geomerty is a much better frame manager for more 
flexible design and professional designs.


Module versions:
import Tkinter - python2
import tkinter - python3 

Tkinter GUI uses a window heirarchy

What is "weight"?

In the simplest terms possible, a non-zero weight causes a row or 
column to grow if there's extra space. The default is a weight of 
zero, which means the column will not grow if there's extra space.
https://stackoverflow.com/questions/45847313/what-does-weight-do-in-tkinter

What happened? Because column zero had a weight of one, tkinter 
gave the extra space to this column. You could have set the weight 
to 1, 100, 100000 and you would get the same result. In this case, 
all of the extra space goes to this one column.

What happens if you give both columns a weight? The weight is divided 
between the columns proportional to their weight. For example, let's 
say you want a navigation area on the left that takes up 1/4 of the 
screen and the main area should take up 3/4 of the screen.

Change the weights to look like this:

root.grid_columnconfigure(0, weight=1)
root.grid_columnconfigure(1, weight=3)

Since both columns have weight, extra space is given to both columns. 
For every four pixels of extra space, column 0 will get 1 and column 1 
will get the other 3.

example: with column weight c1 = weight 1 and c3 = weight 3
so for every 4 pixels, c1 gets 25% and c2 gets 75% of available
expansion
column1    column2 
[1]    |   [2][2][2]


'''
#import guard for both versions of python

try:
	import tkinter  #for python3
except ImportError: #python3
	import Tkinter as tkinter



def onExit():
	'''Closes the window on exit.'''
	mainWindow.destroy()


#mainWindow is the root window
mainWindow=tkinter.Tk()
mainWindow.title("GUI App v1.0")
mainWindow.geometry("640x480+100+100") #W x h + (-)x+ (-)y

#create Menu components

menuObject=tkinter.Menu(mainWindow)
mainWindow.config(menu=menuObject)
fileMenu=tkinter.Menu(menuObject, tearoff=0)
menuObject.add_cascade(label="File", menu=fileMenu)
fileMenu.add_command(label="Exit", command=onExit)

#Create a label
label = tkinter.Label(mainWindow, text = "Gui app title")
label.grid(row=0, column=0)


leftFrame = tkinter.Frame(mainWindow)
leftFrame.grid(row=1, column=1)


#create canvas
canvas = tkinter.Canvas(leftFrame, borderwidth=1)
#X requires 'expand=true' because you packed to left if change to top, then y will not fill 
canvas.grid(row=1, column=0)
rightFrame = tkinter.Frame(mainWindow)

# rightFrame.config (relief='sunken')
rightFrame.grid(row=1, column=2, sticky='n')

button1 = tkinter.Button(rightFrame, text="button1")
button2 = tkinter.Button(rightFrame, text="button2")
button3 = tkinter.Button(rightFrame, text="button3")

button1.grid(row=0, column=0)
button2.grid(row=1, column=0)
button3.grid(row=2, column=0)



#configure the columns - pads the columns
mainWindow.columnconfigure(0, weight=1)
mainWindow.columnconfigure(1, weight=1)
mainWindow.grid_columnconfigure(2, weight=1)

# highlight the frames to show how they relate
leftFrame.config(relief='sunken', borderwidth=1)
rightFrame.config(relief='sunken', borderwidth=1)
leftFrame.grid(sticky='ns')
rightFrame.grid(sticky='new')

# sticky has no effect unitl a weight is set on rightFrame.
#now that the column has a weight, it can be set
rightFrame.columnconfigure(0, weight=1)
button2.grid(sticky='ew') 






'''
	passes control to TK main tkinter mainloop method to handle 
	all the GUI event handling/processing
'''
mainWindow.mainloop()











# def close_window(self):
# 		'''
# 			Terminate windows on clicking 'x' close button
# 		'''
# 		global continueThreadExec_rx
# 		global continueThreadExec_tx
# 		global p, p2

# 		# self.popup_thread_wait()

# 		if messagebox.askokcancel("Quit", "Are you sure you want to quit?"):
		
# 			try:
# 				os.system("echo 'terminating processess.'")
# 			except:
# 				print("termination failed")

# 			print("shutdown successful.")
# 			continueThreadExec_rx = False
# 			continueThreadExec_tx = False
# 			self.start_test_running = True # spoof this flag to trick the hot plug detect handler to not restart

			
# 			try: 
# 				# p.kill()
# 				# p2.kill()
# 				if (self.q_bandwidth[0] > 500.0) or (self.q_bandwidth[1] > 500.0):
# 					self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,'kill').start()
# 				# os.system('clear')

# 				#wait for serial connection for hot_plug_detect to close
# 				self.wait_hpd_thread_close()
# 				print("1589 - start test running?: " + str(self.start_test_running))

# 				#Log the successful closure of appliation
# 				module_logger.write_to_log("Application successfully exited.")
# 				print("")
# 				print("Application successfully closed. Press Ctrl-c to return to terminal")
# 			except Exception as e:
# 				print ("caught condition - OK failed kill:" + str(e))
# 			self.main.destroy()


# #=======================Main loop =======================================

# def main():
	
# 	root = Tk()
# 	root.resizable(width=False, height=False)
# 	root.geometry("950x600+100+100")
# 	root.attributes("-topmost",True)
# 	# root.attributes("-disabled', True")
# 	app=App_Frame(root)
	


# 	root.protocol("WM_DELETE_WINDOW", DISABLED) #re-route back from main to self
# 	# root.protocol("WM_DELETE_WINDOW", app.close_window) #re-route back from main to self

# 	# os.system('clear')

	
# 	root.mainloop()

# if __name__ == '__main__':
# 	main()