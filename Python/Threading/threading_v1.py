#!/usr/bin/python3

'''
Threading timed execution
'''

import time
import threading

# do stuff
def op_function1(array_num):
	print("op_function1")
	for i in array_num:
		time.sleep(0.2)
		print("o1 {}".format(i*i))

#do stuff again
def op_function2(array_num):
	print("op_function2")
	for i in array_num:
		time.sleep(0.2)
		print("o2 {}".format(i*i*i))

#initialize array
arr = [2,3,4,5]

#init threads
# comma makes args into a 1-tuple

'''
The args argument to threading.Thread expects a sequence, but if a string or in this case array is passed... 
This is causing it to interpret each letter of the strings as an individual argument, 
resulting in too many arguments for your target function.

'''
# because arr is a tuple you have to put comma ',' in the argument field
t1=threading.Thread(target=op_function1, args=(arr,)) # comma makes args into a 1-tuple. required otherwise fail
t2=threading.Thread(target=op_function2,args=(arr,)) # comma makes args into a 1-tuple



t = time.time() # start the counter
t1.start()
t2.start()

t1.join()
t2.join()
tCompleted=time.time() # end time
print("elapsed time: {}".format(tCompleted-t))
