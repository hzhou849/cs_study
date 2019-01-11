#! /usr/bin/python3


# Race test, if Thread2 finished before thread1, it should wait,
# which is done by locking the second thread just after it finishes
# and force it to wait

import threading, time, random


# Create a mutex
m_mutex = threading.Lock()

class thread1(threading.Thread):
	def run(self):
		#Python mutex global - must be used in each method we want to use 
		#the global variables
		global m_mutex
		print("Thread1 sleeping...")
		# time.sleep(random.randint(1,5))
		time.sleep(2)
		print ("Thread1 done...mutex released..")

		#Release the mutex, now that thread1 has finished
		# we want to release the lock
		m_mutex.release()

class thread2(threading.Thread):
	def run(self):
		#Python mutex global
		global m_mutex
		print("Thread 2 attempting to acquire mutex")
		# time.sleep(random.randint(1,5))

		#Acquire the lock: this thread has to 
		#keep waiting until the lock is release
		#before it can continue.
		
		m_mutex.acquire() #wait here until thread1 releases lock
		
		print("Thread2 has finished...mutex acquired")


m_mutex.acquire()
t1 = thread1()
t2 =thread2()
t1.start()
t2.start()