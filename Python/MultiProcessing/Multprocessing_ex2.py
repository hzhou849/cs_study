#!/usr/bin/python3

''' 
Multiprocessing

a normal scenario.
'''

import time
import multiprocessing

def process1(numbers):
	for i in numbers:
		time.sleep(0.2)
		print('p1 ' + str(i*i))

def process2(numbers):
	for i in numbers:
		time.sleep(0.2)
		print('p2 ' + str(i*i*i))


if __name__ == "__main__":
	arr = [2,3,8,9]
	p1 = multiprocessing.Process(target=process1, args=(arr,))
	p2 = multiprocessing.Process(target=process2, args=(arr,))

	p1.start()
	p2.start()

	p1.join()
	p2.join()

