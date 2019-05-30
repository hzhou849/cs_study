#! /usr/bin/python3

'''
Threading - using shared queue

This shared queue method is considered thread safe.
'''

import threading
import queue

import time

def thread1(threadName, q):
	#read variable "a" modify by thread2

	while True:
		if q.qsize() == 0:
			print("thread sleeping....")
			time.sleep(0.5)
		
		a = q.get() # this will block until it receives an item
		if a  == "_sig_kill": 
			print("a: {0}".format(a))
			print("Kill signal received")
			return # quit the appliation
		print("a: {0}".format(a))

def thread2(threadName, q):
	for i in range(0,10):
		i += 1
		q.put(i)
		time.sleep(2)

	#kill after end of for loop
	q.put("_sig_kill") # exit condition?- send quit signal when desired 


# main driver class
def main():
	
	qObj = queue.Queue(1)

	t1= threading.Thread(target=thread1, args=("t1", qObj))
	t2 = threading.Thread(target=thread2, args=("t2", qObj))

	t1.start()
	t2.start()

	t1.join()
	t2.join()

if __name__=='__main__':
	main()