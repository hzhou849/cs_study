#!/usr/bin/python3

'''
Share memory variable - Multiprocess
Module used to share data between multiple processes

**NOTE
multiprocessing.Array does not have the same attributes
as normal arrays. ie 'append()' is not one of its functions
as this structure is used for interprocess communication
purposes maily.

'''

import time
import multiprocessing

#using shared Array
def calculate(input_n, shared_var):

	#enumerate() -returns index and value from the passed array
	for index, i in enumerate (input_n):
		print('index ' + str(index) + '   value: ' + str(i))
		shared_var[index]= (i * i)

# Main method execution 
if __name__ == "__main__":
	arr = [2, 3, 5]

	# allocate an shared memory array (<type i for int> , size 3)
	mp_array = multiprocessing.Array('i',3 )
	proc1 = multiprocessing.Process(target=calculate, args = (arr, mp_array))

	proc1.start()
	proc1.join()


	#syntax to do an array dump
	print(mp_array[:])
