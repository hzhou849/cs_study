#!/usr/bin/python3
#██████████████
'''

#============================================================================
#
# Python script for Console cable fucntional testing  setup
#  Version     Author              Release Notes		Date
#    1.0       H. Zhou	   			Initial Release		July 18 2018
# 	  							
#                               
#============================================================================

Copyright 2018 Medtronic.
All Rights Reserved. The information contained herein is confidential
property of Medtronic. The use, copying, transfer or disclosure of such
information is prohibited except by written agreement with Medtronic. 

TODO: 

1) remote access with teamviewer.
gnome-screensaver-command -l


2) fix eth detect remove fixed list numbers - DONE!
3) rename and format module 'mod_bandwith
   - seperate all other functions if possible
4) remove as many elements into the cfg.ini file.
'''


from tkinter import *
from tkinter.ttk import Frame, Button, Entry, Style

from tkinter import messagebox
#graphing
from random import randint
# from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
# from matplotlib.figure import Figure
#Multithreading packages
import multiprocessing
from multiprocessing import Process, Queue

import threading


import subprocess
from subprocess import Popen, PIPE
import datetime
import time
import os
import errno
import string
import sys

# import asyncio

# External Function imports
import module_bandwidth
import module_start_test
import serial_driver
import ethernet_connect



# Common variables to be used
global active; active = False
global continueThreadExec_rx; continueThreadExec_rx = False
global continueThreadExec_tx; continueThreadExec_tx = False
global threadCounter; threadCounter=0


def runloop(thread_queue=None):
	'''
	after result is produced put it in queue
	'''
	result = 0
	
	time.sleep(2)
	thread_queue.put(result)
	

class App_Frame(Frame):

	global UPDATER_DELAY; UPDATER_DELAY = 1000 #ms
	global ethDevList; ethDevList = ["0","1", "2"]
	global subnet_ip_list; subnet_ip_list = ["192.168.2.10", "192.168.1.10", "192.168.3.1"]
	# global test_subnet_list; test_subnet_list = ["10.85.106.196", "169.254.30.9"]
	# global fd; fd = open("cpu_info.csv", "a")
	global p; p=0
	global p2; p2=0 
	global rx_bandwidth; rx_bandwidth = 0.0 
	global tx_bandwidth; tx_bandwidth = 0.0
	
	def __init__(self, main):
		super().__init__()
		self.main=main
		self.initUI(main)





	def initUI(self, main):
		'''
			Main GUI function that handles all the widgets
		'''
		

		self.createFrame()

		# Set the app title
		self.master.title("Cable Tester Application v1.0")

		# Initialize themes
		self.style_Init()

		# Initialize grid
		self.row_col_Init()

		# Initalize and create GUI components/widgets
		self.createMenu()
		self.eth_connect_widgets()
		self.bandwidth_widgets()
		self.cable_state_detect_widgets()
		self.debug_window_widget()
		self.buttons_widgets()
		self.update_text()
		# self.row0_Blank()

		self.pack(fill=BOTH, expand=True)
		self.updater()
		
		



	def style_Init(self):

		Style().configure("TButton", padding=(0,5,0,5))
	
		# Style().configure("TFrame", background=backgroundColor)
		# Adjust the frame attributes
		
		# second set of themes 
		Style().configure('ledSysAct.TButton', background="#d9d9d9", foreground="#000000",relief=RAISED)
		Style().configure('ledSysPause.TButton', background="#d9d9d9", foreground="#000000",relief=RAISED)
		Style().configure('led_button.TButton', background = "#d9d9d9", foreground="#000000", relief=SUNKEN)
	
	def createFrame(self):

		#Create the Frame
		self.mainFrame = Frame(self)
		self.mainFrame.pack(fill=X, padx=20, pady=10, anchor=N, expand=True)

		#Divvy up the screen by the number of subframes
		self.frame1 = Frame(self.mainFrame, relief = SUNKEN, width=30)
		self.frame1.grid(row=0, column=0, sticky=W, pady=2, padx=10)
		self.frame2 = Frame(self.mainFrame, relief = SUNKEN)
		self.frame2.grid(row=0, column=1, sticky=W, pady=2, padx=10)
		self.frame3 = Frame(self.mainFrame)
		self.frame3.grid(row=1, column=0, sticky=W, pady=20, padx=10)
		self.frame4=Frame(self)
		self.frame4.pack(fill=Y, padx=20, pady=5)
		self.frame5=Frame(self)
		self.frame5.pack(fill=Y, padx=20, pady=10, side=BOTTOM)

	# Define grid attributes
	def row_col_Init(self):
		self.columnconfigure(0, pad=3)
		self.columnconfigure(1, pad=3)
		self.columnconfigure(2, pad=3)
		self.columnconfigure(3, pad=3)

		self.rowconfigure(0, pad=3)
		self.rowconfigure(1, pad=3)
		self.rowconfigure(2, pad=3)
		self.rowconfigure(3, pad=3)
		self.rowconfigure(4, pad=3)


	# GUI Components
	def createMenu(self):
		'''
			# Create menu object to be placed in main 'self' window
		'''
		menuObject=Menu(self.master)
		self.master.config(menu=menuObject)
		fileMenu=Menu(menuObject, tearoff=0)
		menuObject.add_cascade(label="File", menu=fileMenu)

		fileMenu.add_command(label="task 1", command=self.close_window)
		fileMenu.add_separator()
		fileMenu.add_command(label="Exit", command=self.close_window)


	def eth_connect_widgets(self):
		'''
			# Ethernet connection test widgets
		'''
		self.eth_con_title_label=Label(self.frame1, text="Ethernet Connection:")
		self.eth_con_title_label.grid(row=1, column=0, sticky=W, pady=9, padx=10)
		self.eth0_test_title_label=Label(self.frame1, text="Eth_A", width=6)
		self.eth0_test_title_label.grid(row=1, column=1, sticky=W, pady=2, padx=10)

		self.eth1_test_title_label=Label(self.frame1, text="Eth_B")
		self.eth1_test_title_label.grid(row=1, column=2, sticky=W, pady=2, padx=10)

		self.eth2_test_title_label=Label(self.frame1, text="Eth_C")
		self.eth2_test_title_label.grid(row=1, column=3, sticky=W, pady=2, padx=10)
		
		# Ethernet connection states
		self.eth0_cnx_state_label=Label(self.frame1, foreground='red', text="N/A")
		self.eth0_cnx_state_label.grid(row=2, column=1, sticky=W, pady=2, padx=10)

		self.eth1_cnx_state_label=Label(self.frame1, text="N/A")
		self.eth1_cnx_state_label.grid(row=2, column=2, sticky=W, pady=2, padx=10)

		self.eth2_cnx_state_label=Label(self.frame1, foreground='red', text="N/A")
		self.eth2_cnx_state_label.grid(row=2, column=3, sticky=W, pady=2, padx=10)


	def bandwidth_widgets(self):
		'''
			Create widgets for the bandwidth
		'''
		# Display the Bandwidth
		rx_band_label =Label(self.frame2, text="Rx")
		rx_band_label.grid(row=0, column=0, sticky=W, pady=5, padx=5)
		self.rx_band_entry=Entry(self.frame2, width=12, foreground='blue')
		self.rx_band_entry.grid(row=0, column=1, sticky=W, pady=2, padx=20)

		tx_band_label=Label(self.frame2, text="Tx")
		tx_band_label.grid(row=1, column=0, sticky=W, pady=5, padx=5)
		self.tx_band_entry=Entry(self.frame2, width=12, foreground='#f46242')
		self.tx_band_entry.grid(row=1, column=1, sticky=W, pady=2, padx=20)

	def cable_state_detect_widgets(self):
		'''
			Create the widgets for cable state detection
		'''
		# Cable Detect Field
		cable_detect_label = Label(self.frame3, text= "Cable Detect:")
		cable_detect_label.grid(row=0, column=0, sticky=W, pady=5, padx=5)

		# Entry field
		# self.cable_detect_entry=Entry(self.frame3,width=12, foreground='green')
		# self.cable_detect_entry.grid(row=0, column=1, sticky=W, pady=5, padx=5)

		# Button indicator
		self.cable_detect_button=Button(self.frame3, text="Cable Not Found",state='disabled', width=8, style='led_button.TButton')
		self.cable_detect_button.grid(row=0, column=1, sticky=S, pady=5, padx=5)
		# Empty Data field placeholder
		field3_label = Label(self.frame3, text= "Data_field:")
		field3_label.grid(row=1, column=0, sticky=S, pady=5, padx=5)
		self.field3_entry=Entry(self.frame3,width=12, foreground='green')
		self.field3_entry.grid(row=1, column=1, sticky=W, pady=5, padx=5)


	def debug_window_widget(self):
		''' 
			Debug text box window used for debugging puposes. will not be in final build.
		'''
		self.console_Text=Text(self.frame4, height=18)
		self.vsb=Scrollbar(self.frame4)
		#**line is reaquired to let user scroll vertical scroll bar
		self.vsb.config(command=self.console_Text.yview)
		self.console_Text.configure(yscrollcommand=self.vsb.set)
		self.console_Text.grid(row=0, column=1, sticky=S, pady=5, padx=0)
		# self.console_Text.pack(side=LEFT, fill=BOTH)
		# self.vsb.pack(side=RIGHT, fill=Y)
		self.vsb.grid(row=0, column=2, sticky=NS, pady=5, padx=0)

	
	def buttons_widgets(self):
		'''
			Buttons widgets used in the GUI
		'''

		# Start Button
		self.start_button=Button(self.frame5, text="Start", command = \
			self.start_test)
		self.start_button.grid(row=0, column=0, sticky=S, padx=5,pady=5)
		# Quit button
		self.quit_button=Button(self.frame5, text="Quit", command = \
			self.close_window)
		self.quit_button.grid(row=0, column=1, sticky=S, pady=5, padx=5)

	

	def threadLocker_rx(self):
		'''
		used to manage thread flow control to prevent extra instances of 
		threaded functions to execute before existing instance is finished.
		'''
		global continueThreadExec_rx
		if continueThreadExec_rx == True:
			continueThreadExec_rx = False
			
		else:
			continueThreadExec_rx = True

		# print(continueThreadExec_rx)
	
	def threadLocker_tx(self):
		'''
		used to manage thread flow control to prevent extra instances of 
		threaded functions to execute before existing instance is finished.
		'''
		global continueThreadExec_tx
		if continueThreadExec_tx == True:
			continueThreadExec_tx = False
		
		else:
			continueThreadExec_tx = True
	
		# print(continueThreadExec_tx)

	def test_lock(self):
		'''
		used to manage thread flow control to prevent extra instances of 
		threaded functions to execute before existing instance is finished.
		'''
		global active
		if active == True:
			active = False
		
		else:
			active = True
	
		# print(continueThreadExec_tx)
		
		

	def bandwidth(self):
		'''
			Calculates and returns network traffic bandwidth to the gui
		'''

		global rx_bandwidth
		global tx_bandwidth

		global threadCounter
		def receive():
			global threadCounter
			global continueThreadExec_rx
				# Rx traffic
			while continueThreadExec_rx:
				try: 
					# cmd1 = subprocess.Popen(['cat', '/proc/net/dev'], stdout=subprocess.PIPE)
					# cmd2 = subprocess.Popen(['grep', 'eth1:',], stdin=cmd1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
					# cmd3 = subprocess.Popen(["awk', '"{print $10}"'], stdin=cmd2.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

					# cmd1 = subprocess.Popen("cat /proc/net/dev", shell=True, stdout=subprocess.PIPE)
					# cmd2 = subprocess.Popen("grep 'eth1:'", shell=True, stdin=cmd1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
					# cmd3 = subprocess.Popen("awk '{print $2}'", shell=True,stdin=cmd2.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
					# cmd1.stdout.close()
					# cmd2.stdout.close()
					# rx_bandwidth, err= cmd3.communicate()

					# test bandwith version
					cmd1=subprocess.Popen(['./bandwidth_calc.sh'], stdout=subprocess.PIPE)
					cmd2=subprocess.Popen("grep 'Rx'", shell =True, stdin = cmd1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
					cmd3=subprocess.Popen("awk '{print $3 $4}'", shell = True, stdin=cmd2.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
					cmd1.stdout.close()
					cmd2.stdout.close()
					rx_bandwidth, err = cmd3.communicate()
					rx_bandwidth=str(rx_bandwidth.decode('ascii')).strip('\n')
					# print (rx_bandwidth)
					#**move this line to up GUI portion for output
					self.rx_band_entry.delete(0,END)
					self.rx_band_entry.insert(END, rx_bandwidth)
					time.sleep(3)
					continueThreadExec_rx=False
				except Exception as e:
					print("closing rx_thread...")
					continueThreadExec_rx=False
					# exit(1)
					# print("error"+str(e))
			threadCounter-=1

		def transmit():
			global continueThreadExec_tx
			while continueThreadExec_tx:
			#Tx traffic
				try: 
					cmd1 = subprocess.Popen(['./bandwidth_calc.sh'], stdout=subprocess.PIPE)
					cmd2 = subprocess.Popen(['grep', 'Tx'], stdin=cmd1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
					cmd3=subprocess.Popen("awk '{print $3 $4}'", shell = True, stdin=cmd2.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

					cmd1.stdout.close()
					cmd2.stdout.close()
					tx_bandwidth, err = cmd3.communicate()
					tx_bandwidth = str(tx_bandwidth.decode('ascii')).strip('\n')
					# print(tx_bandwidth)
					self.tx_band_entry.delete(0,END)
					self.tx_band_entry.insert(END, tx_bandwidth)
					time.sleep(2)
					continueThreadExec_tx=False
				except Exception as e:
					print("closing tx_thread... ")
				# 	print("error"+e)
				# 	cmd1 = subprocess.Popen(['ls', '/sys/class/net/'], stdout=subprocess.PIPE)
				# 	cmd2 = subprocess.Popen(['grep', 'eth', ], stdin=cmd1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
				# 	cmd1.stdout.close() # Allow cmd1 to receive a SIGPIPE if proc2 exists
				# 	ifaces, err = cmd2.communicate()
				# 	ifaces = str(ifaces.decode('ascii'))
				# 	# for line in ifaces.splitlines():
				# 	#     print("each"+line)
				# 	ifaces=ifaces.splitlines()
					# print ("asdfgsdfg"+ifaces[1])
					continueThreadExec_tx=False

		self.threadLocker_rx()
		self.threadLocker_tx()

		rx_thread=threading.Thread(target=receive)
		rx_thread.start()
		threadCounter+=1
		tx_thread=threading.Thread(target=transmit)
		tx_thread.start()
		

	
	def cable_state(self):
		'''
			Detected and display the cable state entry fields
		'''
		test1 = module_bandwidth.function1()
		print(test1)
		

	def serial_tester(self):
		str=serial_driver.wait_animation()
		self.console_Text.insert(END,"RX:"+str+"\n")
	# 	self.rx_band_entry.delete(0,END)
	# 	self.rx_band_entry.insert(END, str)

	def get_last_PID(self):
		
		cmd1 = subprocess.Popen(['cat', 'pid_tester.txt'], stdout=subprocess.PIPE)
		lastPID, err = cmd1.communicate()
		lastPID = str(lastPID.decode('ascii'))

		# write to the debug text box
		# self.console_Text.insert(END, "PID pass test: "+lastPID+"\n")
		# self.console_Text.see(END)
		return lastPID

	def start_test(self):
		global p,p2
		global tx_bandwidth, rx_bandwidth

		try: 
			print("process:")
			print(p)
			print(p2)
			p.kill()
			p2.kill()
		except Exception as e:
			print ("failed kill" + str(e))

		rx_bandwidth = self.rx_band_entry.get().replace("Kbit/s","")
		tx_bandwidth = self.tx_band_entry.get().replace("Kbit/s","")
		# messagebox.showinfo("running", "running again" + str(rx_bandwidth)+" /"+str(tx_bandwidth))

		# def netstart():
		# 	os.system("./NetworkStress.sh & echo $! > pid_tester.txt")
		
		# def pc_connect():
		# 	os.system("./pc_connect.tl")
		
		# netstart_thread=threading.Thread(target=netstart)
		# netstart_thread.start()
		# pc_connect_thread=threading.Thread(target=pc_connect)
		# pc_connect_thread.start()
		
		# os.system("./NetworkStress.sh & echo $! > pid_tester.txt")
		# os.system("gnome-terminal -e './pc_connect.tl'")
		
		# set if RX and TX is greater than threshold, do not start
		if float(rx_bandwidth) < 10.0 and float(tx_bandwidth) < 10.0:
			FNULL = open(os.devnull, 'w')
			messagebox.showinfo("running", "running again" + str(rx_bandwidth)+" /"+str(tx_bandwidth))
			p=subprocess.Popen(["./NetworkStress.sh", ">", "/dev/null", "&" "echo $!", ">", "pid_tester.txt", ],stdout=FNULL, stderr=subprocess.STDOUT)
			# p2 = subprocess.Popen(["gnome-terminal", "-e", "'./pc_connect.tl'",">" "/dev/null"])
			p2 = subprocess.Popen(["./pc_connect.tl","&"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
			serial_driver.connect_serial(self)

		else:
			messagebox.showinfo("Alert!", "Network test already running, please wait..")
		

		# #Execute start_test script.

		# return getPid

		
	def updater(self):
		'''
			GUI Handler - Handles all function execution and updates the GUI
			
		'''

		UPDATE_DELAY=1000
		# self.eth_cnx_test()
		module_bandwidth.eth_cnx_test_external(self)
		self.bandwidth()
		# self.external_task1()
		# self.cable_state()
		# self.get_last_PID()

		# self.serial_tester()

		# Thread/branch out the bandwidth calculation.
		# self.threadLocker()
		# self.t1= threading.Thread(target=self.bandwidth).start()
	
		#check to see if this impacts my thread/branching & cpu/memory consumption
		self.after(UPDATE_DELAY, self.updater)

	def update_text(self):
		self.console_Text.insert(END,"Running loop"+"\n")
		self.console_Text.see(END)
		
		self.Queue = Queue()
		self.task1=ThreadedTask(self.Queue).start()
		self.after(100, self.process_queue)

	def process_queue(self):
		if self.Queue.qsize() >0:
			print(self.Queue.get())
			self.console_Text.insert(END,"Finished and restarting"+"\n")
			self.console_Text.see(END)
			self.update_text()
		self.after(100, self.process_queue)
	
	def listen_for_result(self):
		'''
		check if there is something in the queue
		'''
		try:
			if self.thread_queue.qsize() > 0:
				q_read = self.thread_queue.get()
				self.console_Text.insert(END, "loop terminated" + str(q_read) + "\n")
				self.console_Text.see(END)
			
		except Exception as e:
			print(e)
			self.console_Text.insert(END, "error: " +"\n")
			self.console_Text.see(END)
			self.after(100, self.listen_for_result)



	def close_window(self):
		'''
			Terminate windows on clicking 'x' close button
		'''
		global continueThreadExec_rx
		global continueThreadExec_tx
		global p, p2

		if messagebox.askokcancel("Quit", "Are you sure you want to quit?"):
			
			
			try:
				fd.close()
				# print("file closed successfully")
			except:
				print("file close failed")

			try:
				os.system("echo 'terminating processess.'")
			except:
				print("termination failed")

			print("shutdown successful.")
			continueThreadExec_rx = False
			continueThreadExec_tx = False
			
			try: 
				print("process:")
				print(p)
				print(p2)
				p.kill()
				p2.kill()
			except Exception as e:
				print ("caught condition - OK failed kill" + str(e))
			self.main.destroy()



#=======================Main loop =======================================
class ThreadedTask(threading.Thread):
	def __init__(self,queue):
		threading.Thread.__init__(self)
		self.queue = queue
	def run(self):
		time.sleep(1)
		print("starting thread")
		time.sleep(5)
		self.queue.put("Task Finished")
	

def main():
	root = Tk()
	root.resizable(width=False, height=False)
	root.geometry("830x550+300+300")
	app=App_Frame(root)
	

	root.protocol("WM_DELETE_WINDOW", app.close_window) #re-route back from main to self
	os.system('clear')

	

	root.mainloop()

if __name__ == '__main__':
	main()
