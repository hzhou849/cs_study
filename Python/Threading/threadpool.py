#! /usr/bin/python3
'''
Threadpool Example Test

Testing the concurrent.futures module

note calls to future.result() is blocking
'''

from concurrent.futures import ThreadPoolExecutor
from time import sleep


def task(message, dict):
	'''
	Create a task for the threadpool
	'''
	print("accepted: {} ".format(message) )
	sleep(30)
	return dict


def main():
	'''
	Main execution
	'''

	d1 ={"key1": "value1"}
	d2 ={"key2": "value2"}
	d3 ={"key3": "value3"}
	d4 ={"key4": "value4"}
	d5 ={"key5": "value5"}

	# Create three Threadpools for multi-tasking
	# execution in threadpool is non-blocking (atomic)
	# unless you call the future.result() - that will block
	executor = ThreadPoolExecutor(5)

	future1 =  executor.submit(task, ("task1"), (d1) )
	future2 =  executor.submit(task, ("task2"), (d2) )
	future3 =  executor.submit(task, ("task3"), (d3) )
	while future1.done() == False:
		print("future.done(): {}; ".format(future1.done()))
		# print("future.done(): {}; {} ".format(future1.done(), future1.result()))
		sleep(0.5)
	print("block testing...")
	print("future.done(): {}; {} ".format(future1.done(), future1.result()))
	
	temp = future1.result()
	print("temp: {}".format(temp))
	
if __name__ == '__main__':
	main()