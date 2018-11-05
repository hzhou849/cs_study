#! /usr/bin/python3
'''

7.5.5 Event Objects
This is one of the simplest mechanisms for communication between threads: one thread signals an event and one or more other threads are waiting for it.

An event object manages an internal flag that can be set to true with the set() method and reset to false with the clear() method. The wait() method blocks until the flag is true.

Event () - The internal flag is initially false.

isSet () - Return true if and only if the internal flag is true.

set () - Set the internal flag to true. All threads waiting for it 
		to become true are awakened. Threads that call wait() once 
		the flag is true will not block at all.

clear () - Reset the internal flag to false. 
		Subsequently, threads calling wait() will block until set() 
		is called to set the internal flag to true again.

wait ([timeout]) -Block until the internal flag is true. 
				If the internal flag is true on entry, return immediately. 
				Otherwise, block until another thread calls set() 
				to set the flag to true, or until the optional 
				timeout occurs.

				When the timeout argument is present and not None, 
				it should be a floating point number specifying a 
				timeout for the operation in seconds (or fractions thereof).


dRecieved = connFile.readline()
processThread = threading.Thread(target=processLine, args=(dRecieved,))  # <- note extra ','
processThread.start()
Or use brackets to make a list:

dRecieved = connFile.readline()
processThread = threading.Thread(target=processLine, args=[dRecieved])  # <- 1 element list
processThread.start()
'''
import threading
from threading import Thread, Event
from subprocess import call
import time

class Controller (object):
	def __init__(self):
		self.thread1 = None
		self.thread2 = None
		self.stop_threads = Event() # initial state is false
	
	def loop1(self, arg1):
		while not self.stop_threads.is_set():
			time.sleep(.500)
			print("Thread 1 "+str(arg1))
	
	def loop2(self, arg1):
		while not self.stop_threads.is_set():
			time.sleep(.500)
			print("Thread 2" + str(arg1))
	
	def start(self):
		self.stop_threads.clear()
		self.thread1 = Thread(target = self.loop1, args=("args1",))
		self.thread2 = Thread(target = self.loop2, args=("args1",))
		self.thread1.start()
		self.thread2.start()

	def stop(self):
		self.stop_threads.set()
		self.thread1.join()
		self.thread2.join()
		self.thread1 = None
		self.thread2 = None
		print("thread closed.")

#init object
control = Controller()

control.start()
time.sleep(20)
control.stop()
time.sleep(10)

