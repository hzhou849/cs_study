#!/usr/bin/python3
#!/usr/bin/python
'''
Python Semaphore implementation

'''
import threading
import time
import inspect

class Semaphore:
	def __init__(self):
		self.counter = 0					# Increment counter
		self.m_mutex = threading.RLock() 	# Re-Entrant lock, normal locks are one-time use only, this allows retry
		self.cv = threading.Condition() 	# Condition Variable

		#python condition variables have their own locks??
	def _notify(self):
		self.cv.acquire()
		# self.m_mutex.acquire() # attempt to acquire, will block
		self.counter += 1
		self.cv.notify()
	
	def _wait(self):
		self.cv.acquire()
		while count == 0:






