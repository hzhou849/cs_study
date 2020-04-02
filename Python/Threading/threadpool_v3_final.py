#!/usr/bin/python3
'''
Threadpool - working full implemenation of passing function into queue for 
			processing with full arguemnts
'''
import threading
import queue
import time
import multiprocessing

class Worker(threading.Thread):
	def __init__(self, qtasks, thread_name):
		threading.Thread.__init__(self,name=str(thread_name))
		self.qtasks = qtasks
		self.loop_on_flag = True

	def run(self):
		while self.loop_on_flag:
			print("\nI am: {}".format(threading.current_thread().getName()), end=" ")
			if self.qtasks.qsize() > 0:		
				print("success",end=" ")
				func, args, kargs = self.qtasks.get()
				# print("func {}, args {}, kargs {}".format(func,args, kargs))
				# if func == "KILL_THREAD"
				try:
					print("processing")
					func(*args, **kargs)
				except Exception as e:
					#Exception happedned in this thread
					print(e)
				finally:
					# Mark this task as done, whether an exception happened or not
					self.qtasks.task_done()		
			else:
				print("waiting for tasks", end=" ")
				print(self.qtasks.qsize())
				time.sleep(1)

	# Kill the thread loop
	def tstop(self):
		self.loop_on_flag = False

class Threadpool:
	def __init__(self, num_threads):
		self.qtasks = queue.Queue(num_threads)
		self.num_threads = num_threads
		self.procThreads=[]		

		#Spawn the worker threads and store in an array.
		for i in range(num_threads):
			print("Creating thread {0} of {1}".format(i, num_threads))
			self.procThreads.append(Worker(self.qtasks, "thread-"+str(i)))
			self.procThreads[i].start()

		

	def add_task(self, func, *args, **kargs):
		'''
		add tasks to queue
		Args: take function(args)
		'''
		self.qtasks.put((func, args, kargs))	
	
	
		
	def wait_completion(self):
		'''
		wait for completion of all tasks and kill threads
		'''
		for i in self.procThreads:
			print("killing threadpool {} of {}".format(i, self.num_threads))
			i.tstop()
			i.join()


if __name__ == "__main__":
	import random
	
	#test function to be executed in thread
	def wait_delay(d):
		print("sleeping for (%d)sec" %d)
		time.sleep(d)
		
	def test_func():
		print("no args function passed")

	def test_function(queue, arg1, arg2, arg3):
		time.sleep(1)
		print("arg1: {}, arg2:{}, arg3:{}".format(arg1,arg2,arg3))
		queue.put("PASSS")

	testq = queue.Queue()

	pool = Threadpool(3)

	# can use taskMapper() for bulk jobs or addtask() for individual tasks
	# code will block here, which will make impossible to cancel
	pool.add_task(wait_delay,2)
	pool.add_task(wait_delay,3)
	pool.add_task(test_func)
	
	pool.add_task(test_function,testq,1,2,3)

	while testq.empty():
		print("waiting for queue result")
		time.sleep(.5)
	get_result = testq.get()
	print("value returned: {}".format(get_result))

	# for _ in range(20):
	# 	pool.add_task(wait_delay, random.randint(0,5))
	# 	print("doing other stuff...")
	# 	time.sleep(random.randint(0,3))
	


	pool.wait_completion()

	# for t in pool.procThreads:
	# 	t.join()