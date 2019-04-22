#!/usr/bin/python3

'''
Multiprocessing vs threads
- "Heavyweight"
- Process have their own virtual memory and address space
-can create their own threads.
have their own PID. 
Threads live inside the process.
- have their own address space, 
  can use interprocess communication technique to share
  data ie: file on disk, shared memory, or message pipe



Threads:
- "light-weight"
- Share the Process address space.
- have their own core
- have their own stack memory
- have their own address pointer
- ie global and heap memory can be accessed by 
  each thread in the same process



- Benefit of multiprocessing is that error or memory
  leak in one process won't affect execution
  of another process. Whereas if a thread has a memory
  leak, it can affect the entire process or other threads
  or parent process.
'''
'''
# Becareful with multprocessing
Notice no result will be printed at the end for 
s_result.
Because multiprocessing will create its own memory space
so it will have a second instance of the s_result
global variable independant from the instance
from parent process



In this example, the global variable s_result 
will not be shared. You will need to implement some kind of
interprocess communication (IPC) technique if you want to 
share data between two processes.
'''


import time
import multiprocessing

s_result=[]

def calc_result(number):
	global s_result # python requires a global reference 
	for n in number:
		print('t1' + str(n*n))
		s_result.append(n*n)	

	#within the process s_result will work
	print('result ' + str(s_result))	


if __name__ == "__main__":
	arr = [2,3,8,9]

	#create a seperate process
	#syntax not that different from threading
	p1 = multiprocessing.Process(target=calc_result, args=(arr,))

	p1.start()
	p1.join()

	#outside the child process, it will not have a result.
	print('result ' + str(s_result))
	print("Done!")


