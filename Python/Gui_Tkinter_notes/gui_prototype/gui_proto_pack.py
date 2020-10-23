#! /usr/bin/python3

'''
TKinter GUI - Prototype

Module versions:
import Tkinter - python2
import tkinter - python3 

Tkinter GUI uses a window heirarchy

PACK Geometry with main window and sub-frames

'''
#import guard for both versions of python

try:
	import tkinter  #for python3
except ImportError: #python3
	import Tkinter as tkinter

# print(tkinter.TkVersion)
# print(tkinter.TclVersion)

#Prints a test window dispalys version and buttons 
# tkinter._test()

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
label.pack(side='top')


leftFrame = tkinter.Frame(mainWindow)
leftFrame.pack(side="left", anchor="n", fill = tkinter.Y, expand=False)

#create canvas
canvas = tkinter.Canvas(leftFrame, relief='raised', borderwidth=1)
#X requires 'expand=true' because you packed to left if change to top, then y will not fill 
canvas.pack(side='left', fill=tkinter.X, expand='true') #fill Y -vertical. 

rightFrame = tkinter.Frame(mainWindow, relief='raised')
rightFrame.pack(side="right", anchor='n', expand='true')

button1 = tkinter.Button(rightFrame, text="button1")
button2 = tkinter.Button(rightFrame, text="button2")
button3 = tkinter.Button(rightFrame, text="button3")

button1.pack(side="left")
button2.pack(side="left")
button3.pack(side="left")




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