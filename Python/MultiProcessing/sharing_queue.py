#!/usr/bin/python3

'''
Sharing Data between multiple processes using Queue

Since multProcessing creates its own address/memory space
in each child process. In order to share data between process,
we must use one of the following methods

1. File r/w
2. Shared Memory
3. Message Pipe


Difference between multprocessing.Queue()
and queue.Queue()

import multiprocessing
- lives in shared memory
- used to share data between PROCESSES

import queue
- lives in in-process memory
- used to share data between THREADS
'''

import time
import multiprocessing

# s_result=[]

# def calc_result(number):
# 	global s_result # python requires a global reference 
# 	for n in number:
# 		print('t1' + str(n*n))
# 		s_result.append(n*n)	

# 	#within the process s_result will work
# 	print('result ' + str(s_result))	


# if __name__ == "__main__":
# 	arr = [2,3,8,9]

# 	#create a seperate process
# 	#syntax not that different from threading
# 	p1 = multiprocessing.Process(target=calc_result, args=(arr,))

# 	#start and merge the thread
# 	p1.start()
# 	p1.join()

# 	#outside the child process, it will not have a result.
# 	print('outside the process result ' + str(s_result))
# 	print("Done!")


def calc_result(number, q):
	for i in number:
		temp= i*i
		# print("result:"+ str(temp))
		q.put(temp)

# Main driver class execution
if __name__ == "__main__":
	arr = [2,3, 4]

	q = multiprocessing.Queue()
	#Create child process
	proc1 = multiprocessing.Process(target=calc_result, args=(arr,q))

	#Start and merge the process after completion
	proc1.start()
	proc1.join()

	#display the result
	print("empty: " + str(q.empty()))

	'''
	either while condition will work
	'''
	# while q.empty() ==  False: 
	while q.size() != 0:
		print("Queu+e memory dump: " + str(q.get()))

	# print("Outside process results: " + str(q))
	print(__name__)

