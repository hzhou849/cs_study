#!/usr/bin/python3
#██████████████
'''
Gui _demo with threading tkinter

'''

from tkinter import *
from tkinter.ttk import Frame, Button, Entry, Style, Progressbar, Label, Scrollbar
from tkinter import messagebox
import tkinter.ttk as ttk
from PIL import Image, ImageTk

#graphing
from random import randint
# from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
# from matplotlib.figure import Figure
#Multithreading packages
import multiprocessing
from multiprocessing import Process, Queue

import threading
from threading import Thread, Event


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
import module_ethernet
# import module_start_test
import module_band_calc
import module_serial_connect # move over to new o version
# import ethernet_connect
# import module_serial_connect_sim
import module_iperf
import module_logger
import module_get_config

import module_serial_connect_o



# Common variables to be used
global active; active = False
global continueThreadExec_rx; continueThreadExec_rx = False
global continueThreadExec_tx; continueThreadExec_tx = False
global threadCounter; threadCounter=0


class App_Frame(Frame):

	global UPDATER_DELAY; UPDATER_DELAY = 1000 #ms
	# global ethDevList; ethDevList = ["0","1", "2"]
	# global subnet_ip_list; subnet_ip_list = ["192.168.2.10", "192.168.1.10", "192.168.3.1"]
	# global test_subnet_list; test_subnet_list = ["10.85.106.196", "169.254.30.9"]
	# global fd; fd = open("cpu_info.csv", "a")
	global p; p=0
	global p2; p2=0 
	global rx_bandwidth; rx_bandwidth = 0.0 
	global tx_bandwidth; tx_bandwidth = 0.0

	#instantiate shared queue variables to share data between functions.
	q_bandwidth =0
	q_size =1

	def __init__(self, main):
		super().__init__()
		self.main=main
		self.initUI(main)



	def initUI(self, main):
		'''
			Main GUI function that handles all the widgets
		'''

		# Initial Flags logical states for the hotplug detect
		self.hpd_thread_ct=0
		self.hot_plug_in_progress = False
		self.hot_plug_detect_on = False
		self.start_test_running = False
		self.test_abort_flag = False
		self.user_abort_flag = False

		self.serial_progress = None
		self.AssemblerID_entry_value_old=""
		self.lotNum_entry_value_old=""

		self.error_msg = "\n"
		self.hot_plug_prev_state = ""

		#threads initialization - to be removed. 
		self.thread1 = None #should no longer be used.
		self.thread2 = None #should no longer be used.
		self.stop_threads = Event()

		self.createFrame()

		# Set the app title
		self.master.title("Cable Tester Application v1.0-2")

		# Initialize themes
		self.style_Init()

		# Initialize grid
		self.row_col_Init()

		# Initalize and create GUI components/widgets
		self.createMenu()
		self.eth_connect_widgets()
		self.id_entry_widgets()
		self.test_cable_buttons()
		self.cable_state_detect_widgets()
		# self.debug_window_widget()
		self.buttons_widgets()

		# self.row0_Blank()

		#Threaded Tasks
		self.get_eth_state0()
		self.get_eth_state1()
		self.get_eth_state2()	
		self.start_bandwidth_thread()	


		# Get the usbport the QD780 is connected to
		self.get_usb_port = module_get_config.auto_detect_usb_port()


		
		self.hotplug_detect()

		#Log startup of application
		module_logger.write_to_log("Application start up.")

		self.pack(fill=BOTH, expand=True)
		self.updater()
		# self.crash_log()

		# Check the log file size and purge activity log if 
		# max size (100mb) is reached.
		module_logger.logger_purge()
		



	def style_Init(self):
		'''
		To implement the style themes properly, it must be assigned as a subclass of 'TButton' ie. 'button_style1.TButton'
		then the Style object attributes get reassigned as per desired attributes in the function call from button press.
		'''
		Style().configure("TButton", padding=(0,5,0,5))
	
		
		# second set of themes 
		Style().configure('ledSysAct.TButton', background="#d9d9d9", foreground="#000000",relief=RAISED)
		Style().configure('ledSysPause.TButton', background="#d9d9d9", foreground="#000000",relief=RAISED)
		Style().configure('start_button.TButton', background = "#d9d9d9", relief=RAISED,\
							state='normal',
							font=('default',30))
		
	
	def createFrame(self):
		'''
		Create and position the frames for the widgets
		'''
		#Create the Frame
		self.mainFrame = Frame(self)
		self.mainFrame.pack(fill=X, padx=20, pady=10, anchor=N, expand=True)

		#Divvy up the screen by the number of subframes
		self.frame1 = Frame(self.mainFrame, relief = SUNKEN, width=5)
		self.frame1.grid(row=0, column=0, columnspan =2, sticky=W, pady=2, padx=5)
		
		self.frame2 = Frame(self.mainFrame, relief = SUNKEN, width=5)
		self.frame2.grid(row=0, column=3, pady=20, padx=50)

		#color map
		self.frame4=Frame(self ,height=0, width=100)
		self.frame4.pack(fill=X, side=TOP,padx=100, pady=5, expand=False)
		

		#LEDs
		self.frame3=Frame(self ,height=50, width=400)
		self.frame3.pack(fill=X,side=TOP, padx=100, pady=5, expand=True)


		#start buton
		self.frame5=Frame(self)
		self.frame5.pack(fill=Y, padx=20, pady=10)
		
		self.frame7=Frame(self)
		self.frame7.pack(fill=Y, padx=20, pady=10, side=BOTTOM)
		self.frame7=Frame(self)
		self.frame7.pack(fill=Y,padx=20, pady=10,side=BOTTOM)


	def restart_app(self):		
		#wait for serial connection for hot_plug_detect to close
		self.wait_hpd_thread_close()
		python = sys.executable
		os.execl(python, python, * sys.argv)
		module_logger.write_to_log("application restarted - reinitialization")


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
		self.eth_con_title_label=Label(self.frame1, text="Cable Connections:")
		self.eth_con_title_label.grid(row=1, column=0, sticky=W, pady=9, padx=10)
		self.eth0_test_title_label=Label(self.frame1, text="ETH2:", width=6)
		self.eth0_test_title_label.grid(row=1, column=2, sticky=W, pady=2, padx=10)

		self.eth1_test_title_label=Label(self.frame1, text="ETH3:")
		self.eth1_test_title_label.grid(row=1, column=3, sticky=W, pady=2, padx=10)

		self.eth2_test_title_label=Label(self.frame1, text="ETH4:")
		self.eth2_test_title_label.grid(row=1, column=4, sticky=W, pady=2, padx=10)
		
		# Ethernet connection states
		self.eth1_cnx_state_label=Label(self.frame1, foreground ='red', text="N/A", width=10)
		self.eth1_cnx_state_label.grid(row=2, column=2, sticky=W, pady=2, padx=10)

		self.eth0_cnx_state_label=Label(self.frame1, foreground='red', text="N/A", width=10)
		self.eth0_cnx_state_label.grid(row=2, column=3, sticky=W, pady=2, padx=10)


		self.eth2_cnx_state_label=Label(self.frame1, foreground='red', text="N/A", width=10)
		self.eth2_cnx_state_label.grid(row=2, column=4, sticky=W, pady=2, padx=10)


	def id_entry_widgets(self):
		'''
		Create widgets for the bandwidth
		'''
		# Display the Bandwidth
		AssemblerID_label =Label(self.frame2, text="Assembler ID#")
		AssemblerID_label.grid(row=0, column=0, sticky=W, pady=5, padx=20)
		self.AssemblerID_entry=Entry(self.frame2, width=10, foreground='blue')
		self.AssemblerID_entry.grid(row=0, column=1, sticky=W, pady=2, padx=10)

		lotNum_label=Label(self.frame2, text="Lot#")
		lotNum_label.grid(row=1, column=0, sticky=W, pady=5, padx=20)
		self.lotNum_entry=Entry(self.frame2, width=10, foreground='#f46242')
		self.lotNum_entry.grid(row=1, column=1, sticky=W, pady=2, padx=10)

	

	def cable_state_detect_widgets(self):
		'''
		Create the widgets for cable state detection
		'''

		# Cable Detect Field
		cable_detect_label = Label(self.frame1, text= "ETH1:")
		cable_detect_label.grid(row=1, column=1, sticky=W, pady=5, padx=5)

		# Entry field
		# self.cable_detect_entry=Entry(self.frame3,width=12, foreground='green')
		# self.cable_detect_entry.grid(row=0, column=1, sticky=W, pady=5, padx=5)

		# Button indicator
		self.cable_detect_label=Label(self.frame1,text="Checking for cable..", width=15, foreground='#f79605')
		self.cable_detect_label.grid(row=2, column=1, sticky=S, pady=5, padx=5)
		# Empty Data field placeholder
		# field3_label = Label(self.frame1, text= "Data_field:")
		# field3_label.grid(row=4, column=0, sticky=S, pady=5, padx=5)
		# self.field3_entry=Entry(self.frame1,width=12, foreground='green')
		# self.field3_entry.grid(row=4, column=1, sticky=W, pady=5, padx=5)


	def test_cable_buttons(self):
		'''
		LED - Load color button images and create the rounded color button labels
		'''

		#button pixel size
		button_width=100
		button_height=100

		map_button_width=400
		map_button_height =50

		padx_value='30'
		# Green button Image
		self.image = Image.open("buttons_color/button_dark_green.png")
		self.image= self.image.resize((button_width,button_height), Image.ANTIALIAS)
		self.green_button_image= ImageTk.PhotoImage(self.image)

		# Red button Image
		self.image = Image.open("buttons_color/button_dark_red.png")
		self.image= self.image.resize((button_width,button_height), Image.ANTIALIAS)
		self.red_button_image= ImageTk.PhotoImage(self.image)

		# yellow button Image
		self.image = Image.open("buttons_color/button_yellow.png")
		self.image= self.image.resize((button_width,button_height), Image.ANTIALIAS)
		self.yellow_button_image= ImageTk.PhotoImage(self.image)

		#color map 
		self.image = Image.open("buttons_color/color_map_thin.png")
		self.image= self.image.resize((map_button_width,map_button_height), Image.ANTIALIAS)
		self.color_map_image= ImageTk.PhotoImage(self.image)



		# Round button 1
		round_button1_title_label = Label(self.frame3, text= 'ETH1')
		round_button1_title_label.grid(row=3, column=0, sticky=S, padx=padx_value, pady=5)
		self.round_button_1 = Label(self.frame3, text = 'button',image=self.yellow_button_image)
		self.round_button_1.grid(row=4, column=0, sticky=S, padx=padx_value, pady=5)

		# Round button 2
		round_button2_title_label = Label(self.frame3, text= 'ETH2')
		round_button2_title_label.grid(row=3, column=1, sticky=S, padx=padx_value, pady=5)
		self.round_button_2 = Label(self.frame3, text = 'button',image=self.yellow_button_image)
		self.round_button_2.grid(row=4, column=1, sticky=S, padx=padx_value, pady=5)

		# Round button 3
		round_button3_title_label = Label(self.frame3, text= 'ETH3')
		round_button3_title_label.grid(row=3, column=2, sticky=S, padx=padx_value, pady=5)
		self.round_button_3 = Label(self.frame3, text = 'button',image=self.yellow_button_image)
		self.round_button_3.grid(row=4, column=2, sticky=S, padx=padx_value, pady=5)

		# Round button 4
		round_button4_title_label = Label(self.frame3, text= 'ETH4')
		round_button4_title_label.grid(row=3, column=3, sticky=S, padx=padx_value, pady=5)
		self.round_button_4 = Label(self.frame3, text = 'button',image=self.yellow_button_image)
		self.round_button_4.grid(row=4, column=3, sticky=S, padx=padx_value, pady=5)

		# color map -column span to expand across the columns and not mess up the LED row.
		color_map_label = Label(self.frame3, text= 'Color Map:')
		color_map_label.grid(row=0, column=0, padx=padx_value, pady=5,columnspan=4, sticky=S )
		self.color_map = Label(self.frame3, text = 'button',image=self.color_map_image)
		self.color_map.grid(row=1, column=0, padx=padx_value, pady=5,columnspan=4, sticky=N)

		#empty row for spacing between map and LEDs
		color_map_label = Label(self.frame3, text= '')
		color_map_label.grid(row=2, column=0, padx=padx_value, pady=10,columnspan=4, sticky=S )




	def debug_window_widget(self):
		''' 
		Debug text box window used for debugging puposes. will not be in final build.
		'''
		self.console_Text=Text(self.frame5, height=18)
		self.vsb=Scrollbar(self.frame5)
		#**line is reaquired to let user scroll vertical scroll bar
		self.vsb.config(command=self.console_Text.yview)
		self.console_Text.configure(yscrollcommand=self.vsb.set)
		self.console_Text.grid(row=0, column=1, sticky=S, pady=5, padx=0)
		# self.console_Text.pack(side=LEFT, fill=BOTH)
		# self.vsb.pack(side=RIGHT, fill=Y) 
		self.vsb.grid(row=0, column=2, sticky=NS, pady=5, padx=0)

	


	def buttons_widgets(self):
		'''
			START BUTTON
			QUIT BUTTON 
			- widgets used in the GUI
			-assembler id and lot# check logic is here
		'''
		# style_var = self.style1.configure(SUNKABLE_BUTTON, releif=SUNKEN)
		

		# Start Buttonfont
		self.start_button_lock = False
		self.quit_shutdown_button_lock = False
		self.start_button=Button(self.frame5, text="Start",command = \
			lambda: self.start_serial_test(1,1), style='start_button.TButton')
		# self.start_button.grid(row=0, column=2, sticky=S, padx=5,pady=5)
		self.start_button.pack(fill=BOTH, side=TOP, expand=True)
		# Quit button
		self.quit_button=Button(self.frame7, text="Quit", command = \
			self.close_window)
		self.quit_button.grid(row=0, column=1, sticky=S, pady=5, padx=5)

		self.shutdown_button=Button(self.frame7, text="Shutdown PC1/PC2", command = \
			self.shutdown)
		self.shutdown_button.grid(row=0, column=2, sticky=S, pady=5, padx=5)

	def popup_thread_wait(self):
		'''
		Create popup window to display please wait
		during waiting of a given task
		'''
		self.wait_win = Toplevel()
		self.wait_win.attributes("-topmost", True)
		self.wait_win.geometry("260x200+500+400")
		self.wait_win.resizable(width=False, height=False)
		self.wait_win.wm_title("Closing last process...")
		
		#trying this to see it it will force window to top
		self.wait_win.lift()

		self.popup_label2= Label(self.wait_win, text="Please wait...")
		self.popup_label2.grid(row=0, column=0, padx = 10, pady=10)

		self.thread_wait_prog_bar = Progressbar(self.wait_win, orient="horizontal", length=200, mode="determinate")
		self.thread_wait_prog_bar.grid(row=2, column=0, padx=30, pady=10)
		self.thread_wait_prog_bar.start()

		self.status_popup_label2=Label(self.wait_win, text="adfadsf")
		self.status_popup_label2.grid(row=3, column=0, padx=10, pady=10)
		
		

	def popup_start_test_window(self):
		'''
		Create a popup window to display the test progress
		'''
	
			
		# Set the test abort flag to stop the test from detecting the 
		# serial queue and pass it to the quit handler instead.	
		
	
		self.win = Toplevel()
		self.win.attributes("-topmost", True)
		self.win.geometry("260x200+500+400")
		self.win.resizable(width=False, height=False)
		self.win.wm_title("Test in progress")
		self.win.protocol("WM_DELETE_WINDOW", DISABLED)
		#trying this to see it it will force window to top
		self.win.lift()

		self.label = Label(self.win, text="Please wait...")
		self.label.grid(row=0, column=0, padx = 10, pady=10)

		self.prog_bar = Progressbar(self.win, orient="horizontal", length=200, mode="indeterminate" )
		self.prog_bar.grid(row=2, column=0, padx = 30, pady=10)
		self.prog_bar.start()

		self.status_label = Label(self.win, text="...")
		self.status_label.grid(row=3,column=0, padx = 10, pady=10)

		self.abort_button = Button(self.win, text="Abort",command=lambda:self.abort_action(1), state =DISABLED) 
		self.abort_button.grid(row=4, column=0, padx = 10, pady=10)

	def abort_action(self, user_abort):
		'''
		Abort - button is managed here as well.
		ABORT BUTTON
		Handle the 'Abort' button action
		Helper function.for popup window.

		args:
			led_state : array that holds the failure state of each ETH device
			0 = ok, 1 = fail
			 [eth1, eth2, eth3, eth4] default is [0,0,0,0]
			user_abort: 0 = default code abort
			            1 = user clicked abort button
						2 = abort and reinitialize the app
		'''
		if user_abort == 1:
			self.error_msg += "User aborted \n"
			print("cbt- 592 " + str(user_abort))
			self.user_abort_flag = True
		# Set the abort flag
		self.test_abort_flag = True			

		# Wait for the last operation to finish
		counter=0
		loop_on=True
		timeout_limit = 20
		

		#kill the serial test thread

		try:
			if user_abort == 1:
				self.thread_serial.abort()
			else:
				self.thread_serial.stop()
		except Exception as e:
			print("Thread exception catched: " + str(e))

		self.popup_thread_wait() #try wrapping this in the while if conditionally once only
		while loop_on == True and user_abort == 1:
			self.start_test_running = True
			if counter % 1000 == 0:
				print("Aborting test")
			elif counter % 2 == 0:
				# self.thread_wait_prog_bar['value'] = counter
				self.status_popup_label2.configure(text=counter)
				# self.status_popup_label2.update_idletasks() # update the gui on same thread iteration cycle
				self.thread_wait_prog_bar['value'] +=15
				self.wait_win.update_idletasks() # update the gui on same thread iteration cycle

				#try updating the whole window and not just the popup label 
				print(".", end="", flush = True)
				# self.hot_plug_detect_on = False
			if self.serial_progress_q.qsize() > 0:
				if self.serial_progress == 1:
					loop_on=False
				elif self.serial_progress == 2:
					loop_on=False
				elif self.serial_progress == 3:
					loop_on=False
				elif self.serial_progress == 4:
					loop_on=False
			

			else:
				# if counter % 3:
				# 	print(".", end="", flush=True)
				time.sleep(.200)
			#reduce the printout frequency by modding this value	
			counter=counter+1

			#timeout period.
			if counter >=timeout_limit:
				# flip this boolean to exit
				loop_on = False
		
		self.wait_win.destroy()

		module_logger.write_to_log("Test Aborted")
		self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,'kill').start()

		# self.restart_app()
		self.win.destroy()

		if user_abort == 2:
			# Initial logical states for the hotplug detect
			self.re_initialize()
			self.hot_plug_in_progress = False
			self.hot_plug_detect_on = False
			self.start_test_running = False
			self.hotplug_detect()


	def wait_hpd_thread_close(self):
		'''
		Wait for hot plug detect to close
		variable: timeout_limit - how much time to wait for thread to close
								  before timing out.
		'''
		#wait for serial connection for hot_plug_detect to close
		# consider branching out the popup window. keep queue management here,
		#open and close will happen outside.
		timeout_limit = 25
		counter=0
		self.popup_thread_wait() #try wrapping this in the while if conditionally once only
		while self.hot_plug_detect_on == True:
			self.start_test_running = True
			if counter % 1000 == 0:
				print("waiting for hot_plug cycle thread to finish")
			elif counter % 2 == 0:
				# self.thread_wait_prog_bar['value'] = counter
				self.status_popup_label2.configure(text=counter)
				# self.status_popup_label2.update_idletasks() # update the gui on same thread iteration cycle
				self.thread_wait_prog_bar['value'] +=10
				self.wait_win.update_idletasks() # update the gui on same thread iteration cycle

				#try updating the whole window and not just the popup label 
				print(".", end="", flush = True)
				# self.hot_plug_detect_on = False
			if self.hot_plug_q.qsize() > 0:
				hot_plug_result = self.hot_plug_q.get(timeout=10)
				self.hot_plug_detect_on = False
			else:
				# if counter % 3:
				# 	print(".", end="", flush=True)
				time.sleep(.200)
			#reduce the printout frequency by modding this value	
			counter=counter+1

			if counter >=timeout_limit:
				# flip this boolean to exit
				
				self.hot_plug_detect_on = False
				self.start_test_running = True # spoof this flag to trick the hot plug detect handler to not restart
		self.wait_win.destroy()

	def updater(self):
		'''
			GUI Handler - Handles misc function execution and updates the GUI
			
		'''
		UPDATE_DELAY=1000



		AssemblerID_entry_value=self.AssemblerID_entry.get()
		lotNum_entry_value=self.lotNum_entry.get()


		#log the assembler info
		if len(AssemblerID_entry_value) != len(self.AssemblerID_entry_value_old):
			module_logger.write_to_log("Assembler ID: "+str(AssemblerID_entry_value))
		if len(lotNum_entry_value) != len(self.lotNum_entry_value_old):
			module_logger.write_to_log("lot#: "+str(lotNum_entry_value))

		# print(len(AssemblerID_entry_value))

		# print(len(lotNum_entry_value))
		
		# Assembler ID and Lot num id == 0, then disable start
		if (len(AssemblerID_entry_value) == 0) or (len(lotNum_entry_value) == 0):
			self.start_button.configure(state=DISABLED)
		else: #if both fields are 
			if self.start_button_lock == True:
				self.start_button.configure(state=DISABLED)	
			else:
				self.start_button.configure(state=NORMAL)

		#restart the hot_plug detect check if test is running first
		# if (self.hot_plug_detect_on == False) and (self.start_test_running== False):
		# 	self.hotplug_detect()
		

		#write to log to check when application crashes
		self.AssemblerID_entry_value_old=AssemblerID_entry_value
		self.lotNum_entry_value_old=lotNum_entry_value

		# Handle the quit and shutdown button locks
		if self.quit_shutdown_button_lock == True:
			self.quit_button.configure(state = DISABLED)
			self.shutdown_button.configure(state = DISABLED)
		else:
			self.quit_button.configure(state = NORMAL)
			self.shutdown_button.configure(state = NORMAL)

		#check to see if this impacts my thread/branching & cpu/memory consumption
		self.after(UPDATE_DELAY, self.updater)

	def crash_log(self):
		module_logger.write_to_log("App is alive")
		self.after(60000, self.crash_log)

	def re_initialize(self):
		'''
		Reset all the flags to their initial states after
		a test has been executed so test can run again. 
		'''
		self.start_button_lock = False
		self.quit_shutdown_button_lock = False
		self.start_button.configure(text='Start')
		self.AssemblerID_entry.config(state='enabled')
		self.lotNum_entry.config(state='enabled')
		self.test_abort_flag = False
		self.error_msg = ""


# =======================================================================================================================================
# Thread management
#=======================================================================================================================================
	
	# Ethernet Connection state handlers
	def get_eth_state0(self):
		'''
			Dependencies: 'module_ethernet.py'
			Creates a thread to check for ethernet connection state 
			- One time execution to create the thread.
		'''
		
		self.eth0_thread_loop_on = True
		self.eth0_q = Queue(self.q_size)
		self.thread_task = module_ethernet.Ethernet_thread('0', self.eth0_q).start()
		self.get_eth_state_queue0()

	def get_eth_state1(self):
		
		self.eth1_thread_loop_on =True
		self.eth1_q = Queue(self.q_size)
		self.task1 = module_ethernet.Ethernet_thread('1', self.eth1_q).start()
		self.get_eth_state_queue1()
	
	def get_eth_state2(self):
		self.eth2_thread_loop_on =True
		self.eth2_q = Queue(self.q_size)
		self.task2 = module_ethernet.Ethernet_thread('2', self.eth2_q).start()
		self.get_eth_state_queue2()

	def get_eth_state_queue0(self):
		'''
			Queue handling for  get_eth_state() thread
			detects changes in Queue state and gets the data
			NOTE: Be careful of the self.after refresh rate if < 1000ms may result in unstable GUI

			self.eth[x]_thread_loop_on logic used to prevent threads from over-creating
			can be removed if liked.
		'''

		if self.eth0_q.qsize() >0:
			q_result = self.eth0_q.get(timeout=10)
			exec("self.eth0_cnx_state_label.config(text=q_result[1], foreground=q_result[2])")
			self.eth0_thread_loop_on = False
		
		if self.eth0_thread_loop_on == True:
			self.after(800, self.get_eth_state_queue0) # 1500ms tested ok
		elif self.eth0_thread_loop_on == False:	
			self.get_eth_state0()
	
	def get_eth_state_queue1(self):
		if self.eth1_q.qsize() >0:
			q_result1 = self.eth1_q.get(timeout=10)
			exec("self.eth1_cnx_state_label.config(text=q_result1[1], foreground=q_result1[2])")
			self.eth1_thread_loop_on = False

			# self.get_eth_state1()
		if self.eth1_thread_loop_on == True:
			self.after(800, self.get_eth_state_queue1)
		elif self.eth1_thread_loop_on == False: 
			self.get_eth_state1()


	def get_eth_state_queue2(self):
		if self.eth2_q.qsize() >0:
			q_result2 = self.eth2_q.get(timeout=10)
			# self.eth2_q.task_done()

			exec("self.eth2_cnx_state_label.config(text=q_result2[1], foreground=q_result2[2])")
			self.eth2_thread_loop_on =False

		if self.eth2_thread_loop_on == True:
			self.after(800, self.get_eth_state_queue2)
		elif self.eth2_thread_loop_on == False:
			self.get_eth_state2()



	
	# Bandwidth calculation thread **** disable self update, only needs to run 
	#modify thread to one thread and reiterate only getting bandwidth.
	def start_bandwidth_thread(self):
		'''
		Dependencies: 'module_bandwidth.py'
		Creates a thread to get bandwidth value - use bandwidth applicaiton
		- One time execution to create the thread.
		'''
		self.band_q_loop=True
		self.q_band_values = Queue(self.q_size)
		self.thread_band_calc = module_band_calc.band_calc_thread(self.q_band_values).start()
		self.get_bandwidth_q_handler()

	def get_bandwidth_q_handler(self):
		if self.q_band_values.qsize() >0:
			self.q_bandwidth = self.q_band_values.get(timeout=10)
			# print("bandwidth queue")
			# print(self.q_bandwidth)
			self.band_q_loop=False # for thread management

		if self.band_q_loop == True:
			self.after(1500, self.get_bandwidth_q_handler)
		else:
			self.start_bandwidth_thread() # restart the bandwidth detect



#=====================================================================
	# Start thread to execute iperf test
#=====================================================================
	def start_iperf(self):
		'''
		Kick off the iperf test
		'''
		self.iperf_loop = True
		self.iperf_thread_q = Queue(self.q_size)
		self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,1).start()
		self.iperf_q_handler()

	def iperf_q_handler(self):
		if self.iperf_thread_q.qsize() > 0:
			self.iperf_loop = False
			self.iperf_q_value =self.iperf_thread_q.get(timeout=10)
			# print(self.iperf_q_value)
			self.start_serial_test2(self.iperf_q_value)
			# return (iperf_q_value) 

		if self.iperf_loop == True:
			self.after(1500, self.iperf_q_handler)

			
		#2) check wait for bandwidth > 500mbps and return control
	    # back to main thread.
	
	
	def start_serial_test2(self, iperf_err_code):
		'''
		Phase two of the serial test.
		'''

		# Create a queue to share info and start the serial connection
		if iperf_err_code == 'ok':
			self.serial_test_q = Queue(self.q_size)
			self.serial_progress_q = Queue(self.q_size)

			# can move this thread creation out to init function***
			self.thread_serial = module_serial_connect_o.Serial_connect_thread(self.serial_test_q, self.serial_progress_q)
			self.thread_serial.start()

			#enable the Abort button
			self.abort_button.config(state='normal')

			#instanitate the  loop control variables for the queue handlers
			self.loop_on =True
			self.progress_loop_on = True

			#bandwidth is good, switch the ethernet leds to green 
			#get the individual bandwidth
			
			# self.round_button_2.configure(image=self.green_button_image)
			# self.round_button_3.configure(image=self.green_button_image)
			# self.round_button_4.configure(image=self.green_button_image)

			# pass control to serial handler
			self.serial_q_handler()
			self.serial_progress_q_handler()
		else:
			err_msg = iperf_err_code + " :check connection and run test again."
			self.status_label.configure(text="Warning"+err_msg ) 
			self.win.destroy()
			messagebox.showwarning("Warning", err_msg)
			# self.start_button.configure(state=NORMAL)
			self.re_initialize()
			self.hot_plug_in_progress = False
			self.hot_plug_detect_on = False
			self.start_test_running = False
			self.hotplug_detect()

	

	

	# Serial driver test thread 
	def start_serial_test(self, button_state, iperf_mode):
		'''
		Dependencies: 'module_serial_connect.py'
		Creates a thread to and establishes a serial connection
		test with the Quantum Data 780E 
		- One time execution to create the thread.

		Args:
			button_state:  '1' Disables the start test button and resets the 
							LED indicators to inital (amber color) state.
		'''
		timeout_limit = 30
		# Log Button press event in activity log
		module_logger.write_to_log("Start Button pressed.")
		
		# let the gui know the test is running and not allow another 
		# instance of hot_plug_detect to start
		self.start_test_running = True
		self.cable_detect_label.configure(text = 'Checking for cable...',  foreground='#f79605')

		self.AssemblerID_entry.config(state='disabled')
		self.lotNum_entry.config(state='disabled')
	
		

		if button_state == 1:
			# self.start_button.configure(state=DISABLED)
			self.start_button_lock = True
			self.quit_shutdown_button_lock = True
			self.start_button.configure(text='Testing...')
			self.round_button_1.configure(image=self.yellow_button_image)
			self.round_button_2.configure(image=self.yellow_button_image)
			self.round_button_3.configure(image=self.yellow_button_image)
			self.round_button_4.configure(image=self.yellow_button_image)
			# Style().configure('start_button.TButton', relief='SUNKEN', foreground='grey', background ='grey', state=DISABLED)

		#wait for serial connection for hot_plug_detect to close
		# do not use the wait_hpd_thread_close() function,
		# this is a different execution. 
		cable_detect_value = self.cable_detect_label["text"]
		counter=0
		self.popup_thread_wait() # create the popup window only
		self.proceed_serial_test = True
		while self.hot_plug_detect_on == True:
			self.start_test_running = True
			if counter % 1000 == 0:
				print("")
				#update the popup progress window
				# self.status_label.configure(text = "Waiting for hot plug detect to finish")
			elif counter % 2 == 0:
				# print(".", end="", flush = True)
				# self.hot_plug_detect_on = False
				self.status_popup_label2.configure(text=counter)
				self.thread_wait_prog_bar['value'] +=10 # progress bar increment value
				self.wait_win.update_idletasks() # update the gui on same thread iteration cycle


			if self.hot_plug_q.qsize() > 0:
				hot_plug_result = self.hot_plug_q.get(timeout=10)
				self.hot_plug_detect_on = False
			else:
				# if counter % 3:
				# 	print(".", end="", flush=True)
				time.sleep(.200)
			#reduce the printout frequency by modding this value	
			counter=counter+1
			
			#timeout this check and ask to check serial connection to 780E
			if counter >=timeout_limit:
				self.wait_win.destroy()
				messagebox.showinfo("Alert!", "serial connection to 780E not detected. check connection and try again")
				self.proceed_serial_test = False
				self.hot_plug_detect_on = False
				#restart application
				# self.restart_app()
			

		self.wait_win.destroy()
		print("1063-self.proceed_serial_test:")
		print(self.proceed_serial_test)
		# start_iperf returns ok or fail
		if self.proceed_serial_test == True:
			#start the progressbar
			self.popup_start_test_window()
			self.status_label.configure(text = "Starting Cable test. Please wait")
			try:
				self.start_iperf()
			except Exception as e:
				print("1045 iperf kickoff exception" + str(e))
				print("1046 exitinging and restarting: " + str(self.proceed_serial_test))
			
				
		else: #serial connection fails, restart the application
			# Restart and Initial logical states for the hotplug detect
			print("1076 proceed serial test?: " + str(self.proceed_serial_test))
			self.re_initialize()
			self.hot_plug_in_progress = False
			self.hot_plug_detect_on = False
			self.start_test_running = False
			self.hotplug_detect()
			


	
	def serial_progress_q_handler(self):
		'''
		Args:
		 	Counter = pass 0 to start from zero increment counter
			 for timeout check
		queue handler to handle the return of the test progress
		and update the popup progress window.

		'''
		#initialize serial_progress
		
		# print("1084-self.error_msg:" + (self.error_msg))

		if (self.serial_progress_q.qsize() > 0) and (self.test_abort_flag == False):
			self.serial_progress = self.serial_progress_q.get(timeout=10)
			if self.serial_progress == "Reading from serial device":
				self.abort_button.config(state=DISABLED)
				self.serial_progress = "\nAttempting to retreive data \nfrom serial device\n"
				
			print("."+str(self.serial_progress), end="", flush = True)
			print(" returned progress")
			print(self.serial_progress)
				# self.last_ser_progress = self.serial_progress
			try:
				self.status_label.configure(text ="Completing step - " + str(self.serial_progress)+" of 4.")
			except Exception as e:
				print("Exceptions 1077ctg - " +  str(e))


			if self.serial_progress == -1:
				print("timeout_catched")
				self.abort_action(0)

			if self.serial_progress == 1:
				#set the ETH1 connection to Connected.
				self.cable_detect_label.configure(text = 'Connected',  foreground='green')

			#Check if the network cables are disconnected and cancel the test
			# if self.serial_progress == 2 or self.serial_progress == 3:
			if self.serial_progress == 3:
				# read which label is disconneted
				# flip the LEDS to red based on this reading then abort
				if self.eth0_cnx_state_label.cget("text") == "Disconnected" or \
					self.eth1_cnx_state_label.cget("text") == "Disconnected" or \
					self.eth2_cnx_state_label.cget("text") == "Disconnected" or \
					self.eth0_cnx_state_label.cget("text") == "Network Error" or \
					self.eth1_cnx_state_label.cget("text") == "Network Error" or \
					self.eth2_cnx_state_label.cget("text") == "Network Error":
					
				# 	module_logger.write_to_log("Test Aborted - Eth2 - Disconnected")
				# 	self.round_button_2.configure(image=self.red_button_image)
				# 	# messagebox.showwarning("Stopping Test", "Eth2 cable disconnected..Test aborted")

				# 	self.abort_action()
				# 	module_logger.write_to_log("Test Aborted - Eth3 - Disconnected")
				# 	# messagebox.showwarning("Stopping Test", "Eth3 cable disconnected..Test aborted")
				# 	self.round_button_3.configure(image=self.red_button_image)
				# 	self.abort_action()
				# 	self.round_button_3.configure(image=self.red_button_image)
				# 	module_logger.write_to_log("Test Aborted - Eth4 - Disconnected")
				# 	# messagebox.showwarning("Stopping Test", "Eth4 cable disconnected..Test aborted")
				# 	self.abort_action()
					led_states=self.update_led()
					self.abort_action(0)
				
			if self.serial_progress == 4:
				self.progress_loop_on = False

		
		# if self.test_abort_flag == True:
		# 	self.status_label.configure(text ="Attempting to abort test. Please wait..")


		if self.progress_loop_on == True and self.test_abort_flag == False:
			# if progress_counter % 1000 == 0:
			# 	print("."+str(progress_counter), end="", flush = True)
			# if progress_counter >=5000:
			# 	messagebox.showinfo("Alert!", "Test timed out. Please try again.")
			# 	self.progress_loop_on = False
			self.after(200, self.serial_progress_q_handler)

	def update_led(self):
		'''
		updates the LEDs based on test status
		'''
		led_states = [0,0,0,0]
		print("1131 - " + str(self.eth1_cnx_state_label.cget("text")) + str(self.test_abort_flag))
		if self.cable_detect_label.cget("text") != "Connected":
			self.round_button_1.configure(image=self.red_button_image)
			led_states[0] = 1
		if self.eth1_cnx_state_label.cget("text") == "Disconnected" or \
			self.eth1_cnx_state_label.cget("text") == "Network Error":
			self.round_button_2.configure(image=self.red_button_image)
			led_states[1] = 1

		if self.eth0_cnx_state_label.cget("text") == "Disconnected" or \
			self.eth0_cnx_state_label.cget("text") == "Network Error" :
			self.round_button_3.configure(image=self.red_button_image)
			led_states[2] = 1
		if self.eth2_cnx_state_label.cget("text") == "Disconnected" or \
			self.eth2_cnx_state_label.cget("text") == "Network Error":
			self.round_button_4.configure(image=self.red_button_image)
			led_states[3] = 1

		if self.user_abort_flag == True:
			self.round_button_1.configure(image=self.yellow_button_image)
			self.round_button_2.configure(image=self.yellow_button_image)
			self.round_button_3.configure(image=self.yellow_button_image)
			self.round_button_4.configure(image=self.yellow_button_image)

		return led_states

		#kickoff queue state check
	def serial_q_handler(self):
		'''
		TODO:
		1) check the dictionary size
		2) add 1080p pixel error check 
		'''
		self.fail_reason =""
		state_test=""
		serial_state =""
		band_threshold_value = 900000.0
		# band_threshold_value = float(99000.0)

		# Upon successful retrieval of queue data
		if self.serial_test_q.qsize() >0:
			try:
				self.win.destroy()
			except Exception as e:
				print("1267 - no win to destroy")
		
			#updated serial connection is ok
			serial_q = self.serial_test_q.get(timeout=10)
			#add this delay to help process - noticed this reduces crashing.
			time.sleep(.200)
			# print("1173 serial_q: " + str(serial_q)  )
			#close the serial thread.
			#kill the serial test thread
			try:
				# print("1175 ct - serial q: " +str(serial_q))
				# print("1191 -  " + self.test_abort_flag)
				
				self.thread_serial.stop()
			except Exception as e:
				print("No Thread exception catched" )
			
			if serial_q == 'SER_ERROR':
				# self.error_msg  +="Test NOT completed.\n\n"
				self.error_msg  +="Device read error.\n\n"
				self.error_msg  +="Please check connection and try again.\n\n"
				# self.prog_bar.stop()
				# self.win.destroy()
				# self.close_window()
				state_test = 'FAIL'
				serial_state = 'FAIL'
				self.cable_detect_label.configure(text = 'Cable Not Detected',  foreground='red')

				# led_states = self.update_led()
				# length = len(led_states)
				#go through the led_states array to see what device failed.
				# for i in range(0,length):
				# 	# print("1186 test abort flag- " + str(self.test_abort_flag))
				# 	if led_states[i] == 1 :
						
				# 		if i == 0:
				# 			self.error_msg +="ETH 1 - Failed \n"
				# 		elif i == 1:
				# 			self.error_msg +="ETH 2 - Failed \n"
				# 		elif i == 2:
				# 			self.error_msg +="ETH 3 - Failed \n"
				# 		elif i == 3:
				# 			self.error_msg +="ETH 4 - Failed \n"

				messagebox.showinfo("Alert!", "Test FAILED:\n\n" + str(self.error_msg))
				#run killscript
				self.cable_detect_label.configure(text = 'Cable Not Detected',  foreground='red')

				self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,'kill').start()
			
				# Initial logical states for the hotplug detect
				self.re_initialize()
				self.hot_plug_in_progress = False
				self.hot_plug_detect_on = False
				self.start_test_running = False
				self.hotplug_detect()

			elif serial_q == 'VID_ERROR':
				# self.error_msg  +="Test NOT completed.\n\n"
				# self.error_msg  +="Serial Connection error.\n\n"
				# self.prog_bar.stop()
				# self.win.destroy()
				# self.close_window()
				state_test = 'FAIL'
				serial_state = 'FAIL'
				self.cable_detect_label.configure(text = 'Cable Not Detected',  foreground='red')

				led_states = self.update_led()
				length = len(led_states)
				#go through the led_states array to see what device failed.
				for i in range(0,length):
					# print("1186 test abort flag- " + str(self.test_abort_flag))
					if led_states[i] == 1 :
						
						if i == 0:
							self.error_msg +="ETH 1 - Failed \n"
						elif i == 1:
							self.error_msg +="ETH 2 - Failed \n"
						elif i == 2:
							self.error_msg +="ETH 3 - Failed \n"
						elif i == 3:
							self.error_msg +="ETH 4 - Failed \n"

				messagebox.showinfo("Alert!!!", "Test FAILED:\n\n" + str(self.error_msg))
				#run killscript
				self.cable_detect_label.configure(text = 'Cable Not Detected',  foreground='red')

				self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,'kill').start()
			
				# Initial logical states for the hotplug detect
				self.re_initialize()
				self.hot_plug_in_progress = False
				self.hot_plug_detect_on = False
				self.start_test_running = False
				self.hotplug_detect()
				
			elif serial_q == 'ERROR':
				# self.error_msg  +="Test NOT completed.\n\n"
				led_states = self.update_led()
				# try:
				# 	self.win.destroy()
				# except Exception as e:
				# 	print("1267 - no win to destroy")
				# self.error_msg = "\n"
				length = len(led_states)
				#go through the led_states array to see what device failed.
				for i in range(0,length):
					if led_states[i] == 1 and self.user_abort_flag != True:
						
						if i == 0: #ignore this msg if User aborted
							self.error_msg +="ETH 1 - Failed \n"
						elif i == 1:
							self.error_msg +="ETH 2 - Failed \n"
						elif i == 2:
							self.error_msg +="ETH 3 - Failed \n"
						elif i == 3:
							self.error_msg +="ETH 4 - Failed \n"

				messagebox.showinfo("Alert!!", "Test FAILED:\n\n" + str(self.error_msg))
				# self.close_window()
				state_test = 'FAIL'
				serial_state = 'FAIL'
				#run killscript
				self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,'kill').start()
			
				# Initial logical states for the hotplug detect
				self.re_initialize()
				self.hot_plug_in_progress = False
				self.hot_plug_detect_on = False
				self.start_test_running = False
				self.hotplug_detect()
			
			elif serial_q == 'ABORT':
				'''
				this needs to do the same as 'ERROR' condition,
				but can be stripped down. NOT TESTED YET!	
				'''
				messagebox.showinfo("Alert!", "test Aborted, Press 'OK' to continue")
				# self.close_window()
				state_test = 'FAIL'
				serial_state = 'FAIL'

				#run killscript
				self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,'kill').start()
			
				# Initial logical states for the hotplug detect
				self.re_initialize()
				self.hot_plug_in_progress = False
				self.hot_plug_detect_on = False
				self.start_test_running = False
				self.hotplug_detect()

			else: 
				self.loop_on = False
				# self.start_button.configure(state=NORMAL)
				# print("1338-serial queue dump")
				# print(serial_q)
				#change the led lights
				state_test= str(serial_q['+5v:'])

				
				#get the pixel error values
				try:
					pixel_error = str(serial_q['1080p60 (8 bits):']).replace('errors', '')
					pixel_error = [int(s) for s in pixel_error.split() if s.isdigit()]
					pixel_error = str(pixel_error[0])


					#pull the MSE values
					tx_mse = str(serial_q['Tx_Remote_MS Error (dB):'])
					rx_mse = str(serial_q['Rx_Local_MSE (dB):'])
					print("mse values")
					tx_mse=str(tx_mse).split(',')
					rx_mse=str(rx_mse).split(',')
				except:
					state_test = 'FAIL'
					serial_state = 'FAIL'
					self.fail_reason =" data read failed\n"
				# print(tx_mse)
				# print(rx_mse)

				self.round_button_1.configure(image=self.green_button_image)
				for value in tx_mse:
					# print("935-" + str(value))
					if float(value) > -15.5:
						state_test = 'FAIL'
						serial_state = 'FAIL'
						self.fail_reason="tx_mse value > -15.5\n"
				for value in rx_mse:
					if float(value) > -15.5:
						state_test = 'FAIL'
						self.fail_reason="rx_mse value > -15.5\n"
						serial_state = 'FAIL'

				# add pixel error check
				# print("pixel_error:")
				# print(pixel_error)
				if int(pixel_error) >= 3:
					state_test = 'FAIL' 
					serial_state = 'FAIL'
				elif 'PRN' in pixel_error:
					state_test = 'FAIL'
					serial_state = 'FAIL'
					
				else:
					print("line-1102: pixel_error detect failed  " + str(pixel_error))
	
				
				if serial_state == 'FAIL' and self.test_abort_flag == False:
					print("serial state 1196 - chaged to red")
					self.round_button_1.configure(image=self.red_button_image)


				# individual bandwidth LED check
				#if bandwidth rx and tx > 500 then pass *can also sum the rx and tx
				# and get single average value
				#eth0 --> ETH2 label
				print("line-1 113")
				print("rx: "+str(self.q_bandwidth[2]['eth1']) + "tx:" +str(self.q_bandwidth[3]['eth1']))
				print("rx: "+str(self.q_bandwidth[2]['eth0']) + "tx:" +str(self.q_bandwidth[3]['eth0']))
				print("rx: "+str(self.q_bandwidth[2]['eth3']) + "tx:" +str(self.q_bandwidth[3]['eth3']))
				if (self.q_bandwidth[2]['eth1']) > band_threshold_value and (self.q_bandwidth[3]['eth1'] > band_threshold_value):
					# print("testing...")
					# print(type(self.q_bandwidth[2]['eth1']))

					self.round_button_2.configure(image=self.green_button_image)
				else:
					self.round_button_2.configure(image=self.red_button_image)
					state_test = 'FAIL'
					self.fail_reason +="ETH-2 Failure\n"


				if (self.q_bandwidth[2]['eth0'] > band_threshold_value) and (self.q_bandwidth[3]['eth0']> band_threshold_value):
					self.round_button_3.configure(image=self.green_button_image)
				else:
					self.round_button_3.configure(image=self.red_button_image)
					state_test = 'FAIL'
					self.fail_reason +="ETH-3 Failure\n"

				if (self.q_bandwidth[2]['eth3'] > band_threshold_value) and (self.q_bandwidth[3]['eth3']> band_threshold_value):
					self.round_button_4.configure(image=self.green_button_image)
				else:
					self.round_button_4.configure(image=self.red_button_image)
					state_test = 'FAIL'
					self.fail_reason +="ETH-4 Failure\n"
				#close queue
				# self.serial_test_q.task_done()
				if state_test == 'PASS':
					if serial_state != 'Fail':
						self.round_button_1.configure(image=self.green_button_image)
					
					# try:
					# 	self.prog_bar.stop()
					# 	self.win.destroy()
					# except Exception as e:
					# 	print("1430 Exception caught"+str(e))
					messagebox.showinfo(state_test,"Test Passed!\n\n Press 'ok' to continue")
					self.re_initialize()

					# Close the popup window

					# self.start_button.configure(state=NORMAL)
					# os.system('clear')


					#run kill script
					self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,'kill').start()
					self.start_test_running = False
					self.hotplug_detect()
					# self.restart_app()
					
					# test debug exit bug
					# count=0
					# print("closing 1117ln", end="", flush = True)
					# while (count % 1000 == 0):
					# 	print(".", end="", flush = True)

				else:
					# self.round_button_1.configure(image=self.red_button_image)
					# self.round_button_2.configure(image=self.red_button_image)
					# self.round_button_3.configure(image=self.red_button_image)
					# self.round_button_4.configure(image=self.red_button_image)
					# self.quit_action()
					try:
						self.prog_bar.stop()
						self.win.destroy()
					except Exception as e:
						print("cbt 1403 - no prog_Bar" + str(e))
					# self.round_button_1.configure(image=self.red_button_image)
					messagebox.showwarning(state_test, "Failure detected: \n\n" + self.fail_reason)
					self.re_initialize() #reinitialize gui

					# Close the popup window


					# self.start_button.configure(state=NORMAL)
					# os.system('clear')
					
					#run killscript
					self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,'kill').start()
				
					# Restart and Initial logical states for the hotplug detect
					self.hot_plug_in_progress = False
					self.hot_plug_detect_on = False
					self.start_test_running = False
					self.hotplug_detect()

					# self.restart_app()
						# test debug exit bug
					# count=0
					# print("closing 1117ln", end="", flush = True)
					# while (count %  == 0):
					# 	print(".", end="", flush = True)

				if self.user_abort_flag == True:
					print("cbt 1426 - test_abort_flag: " + str(self.test_abort_flag))
					led = self.update_led()


			# restart idle hotplug detect 
		
		if self.loop_on == True:
			# if self.q_bandwidth :
				# print(self.q_bandwidth)
			self.after(1500, self.serial_q_handler)

		'''
		Detect if the HDBaseT cable is present 
		'''	
	def hotplug_detect(self):
		'''
		modify hotplug detect to accept usb port as an arg so you do not
		have to do a usb check every time.
		There may be double execution by my logic. needs rework.
		'''
		#used for debugging can comment out.
		self.hpd_counter=0
		self.hpd_thread_ct +=1
		
		if self.get_usb_port == 'failed':
			self.get_usb_port = module_get_config.auto_detect_usb_port()
			print("1223" + str(self.get_usb_port))
		
		# USB port is detected
		if self.get_usb_port != 'failed':
			# print("1226" + str(self.get_usb_port))
			time.sleep(1)
			self.hot_plug_q = Queue(self.q_size)
			self.thread_serial = module_serial_connect.Serial_hot_detect(self.hot_plug_q, self.get_usb_port).start()
			self.hot_plug_detect_on = True

			self.hot_plug_detect_handler()
		else:
			print("1234 - else")
			self.cable_detect_label.configure(text='No serial connection', foreground='red')
			self.after(1000, self.hotplug_detect)

	def hot_plug_detect_handler(self):
		# print("1239 - cable_main -> "+str(self.hpd_counter) +"| "+str(self.hpd_thread_ct) + str(self.hot_plug_detect_on) + str(self.start_test_running))
		if self.hot_plug_q.qsize() > 0:
			hot_plug_result = self.hot_plug_q.get(timeout=10)

			#print debug statement if state has changed and assign the new value to self.hot_plug_prev_state.
			if self.hot_plug_prev_state  != hot_plug_result:
				print("ctg-1460 - hot plug detect state change: " + str(hot_plug_result))
				self.hot_plug_prev_state = hot_plug_result

			self.hot_plug_detect_on = False

			if hot_plug_result == 'PASS':
				self.cable_detect_label.configure(text = 'Connected',  foreground='green')
				
			else:
				self.cable_detect_label.configure(text = 'Cable Not Detected',  foreground='red')
				# self.round_button_1.configure(image=self.yellow_button_image)

			
			#if the start button is pressed, replace the above results bc
			# a new cable test is conducted
			if self.start_test_running == True:
				self.cable_detect_label.configure(text = 'Checking for cable...',  foreground='#f79605')


		# if data received from queue restart the test, elseif keep polling. 
		if (self.hot_plug_detect_on == False) and (self.start_test_running== False):
			# print("cbt-1569 - hot plug detect restarted " + str(self.hot_plug_detect_on))
			self.hpd_counter=0
			self.hpd_thread_ct=0
			self.hotplug_detect()
		
		elif (self.hot_plug_detect_on == True) and (self.start_test_running == False):
			self.hpd_counter+=1
			self.after(800, self.hot_plug_detect_handler) # 800 tested

		

#=============================================================================	
# Shut down and close windows
#============================================================================
	def shutdown(self):
		'''
		Shut down both local and remote computers.
		'''
		if messagebox.askokcancel("Quit", "Are you sure you want to shutdown?"):
			try:
				#wait for serial connection for hot_plug_detect to close
				
				if (self.q_bandwidth[0] > 500.0) or (self.q_bandwidth[1] > 500.0):
					self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,'kill').start()

				self.wait_hpd_thread_close()

				#Log the successful closure of appliation
				#get the pc2 IP address.


				pc2_ip_list = module_get_config.get_subnet_ips('pc2')
				pc2_ip = pc2_ip_list[0]
				
				#shut down remote computer
				string_cmd = "gnome-terminal --geometry 1x1+1+1 -e 'sudo ./pc_shutdown.tl " + pc2_ip+"'"

				#shutdown local computer
				string_cmd2 = "gnome-terminal --geometry 1x1+1+1 -e 'sudo ./shutdown_local.sh'"

				os.system(string_cmd)
				time.sleep(2) # short sleep period
				os.system(string_cmd2)
				module_logger.write_to_log("Application successfully exited.")
			except Exception as e:
				messagebox.showwarning("Shutdown", "shutdown failed " + str(e))


	def close_window(self):
		'''
			Terminate windows on clicking 'x' close button
		'''
		global continueThreadExec_rx
		global continueThreadExec_tx
		global p, p2

		# self.popup_thread_wait()

		if messagebox.askokcancel("Quit", "Are you sure you want to quit?"):
			# try:
			# 	fd.close()
			# 	# print("file closed successfully")
			# except:
			# 	print("file close failed")

			# if self.start_test_running == True:
			# 	while self.serial_progress == None:
			# 		print(self.serial_progress)
			# 		time.sleep(1)
			# 	self.abort_action()
			try:
				os.system("echo 'terminating processess.'")
			except:
				print("termination failed")

			print("shutdown successful.")
			continueThreadExec_rx = False
			continueThreadExec_tx = False
			self.start_test_running = True # spoof this flag to trick the hot plug detect handler to not restart

			
			try: 
				# p.kill()
				# p2.kill()
				if (self.q_bandwidth[0] > 500.0) or (self.q_bandwidth[1] > 500.0):
					self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,'kill').start()
				# os.system('clear')

				#wait for serial connection for hot_plug_detect to close
				self.wait_hpd_thread_close()
				print("1589 - start test running?: " + str(self.start_test_running))

				#Log the successful closure of appliation
				module_logger.write_to_log("Application successfully exited.")
				print("")
				print("Application successfully closed. Press Ctrl-c to return to terminal")
			except Exception as e:
				print ("caught condition - OK failed kill:" + str(e))
			self.main.destroy()


#=======================Main loop =======================================

def main():
	
	root = Tk()
	root.resizable(width=False, height=False)
	root.geometry("950x600+100+100")
	root.attributes("-topmost",True)
	# root.attributes("-disabled', True")
	app=App_Frame(root)
	


	root.protocol("WM_DELETE_WINDOW", DISABLED) #re-route back from main to self
	# root.protocol("WM_DELETE_WINDOW", app.close_window) #re-route back from main to self

	# os.system('clear')

	
	root.mainloop()

if __name__ == '__main__':
	main()

