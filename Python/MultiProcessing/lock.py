#!/usr/bin/python3

'''
Mutiprocessing - Lock module


'''

import time
import multiprocessing
# import threading

def increment(counter):
	for i in range(1000000):
		# time.sleep(0.01)
		mylock.acquire()
		#This is the critical section of code
		counter.value = counter.value +1
		mylock.release() 

def decrement(counter):
	for i in range(1000000):
		# time.sleep(0.01)
		mylock.acquire()
		#Critical section
		counter.value=counter.value -1
		mylock.release()


if __name__ == '__main__':
	counter = multiprocessing.Value('i',0)
	mylock = multiprocessing.Lock()

	proc1 = multiprocessing.Process(target=increment, args=(counter,))
	proc2 = multiprocessing.Process(target=decrement, args=(counter,))

	proc1.start()
	proc2.start()

	proc1.join()
	proc2.join()


	print("counter: " + str(counter.value))
