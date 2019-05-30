#!/usr/bin/python3

'''
Share memory variable - Multiprocess
Module used to share data between multiple processes

A value variable in shared memory used for cross process communication
in this case a double shared variable is declared and passed
between processes.

'''

import time
import multiprocessing


def calculate(shared_var):
	shared_var.value = 5.67


if __name__ == "__main__":

	#declare a shared variable of type 'd' double initialized as '0.0'
	shared_var = multiprocessing.Value('d', 0.0)
	proc=multiprocessing.Process(target=calculate, args=(shared_var,))

	proc.start()
	proc.join()

	if shared_var.size() != 0:
		print(shared_var.size())
		print(shared_var.value)
		
