#! /usr/bin/python3

'''
AsyncIO 

A more advanced implemenation of IO


'''

import asyncio
import time
import datetime
import queue
import multiprocessing
from multiprocessing import Queue

class Module_serial():
	def __init__(self, queue):
		self.queue = queue
		self.loop_on_flag = True
		self.hpd_counter = 0
		self.bufferMax = 10





	async def read_serial(self):
		while self.queue.qsize() < 1:
			self.hpd_counter += 1
			if self.hpd_counter >= self.bufferMax:
				self.queue.put("Finished")
			else:
				await asyncio.sleep(.5)
				print("hpd count: {}".format(self.hpd_counter))
				
		print("exited")
		
	async def timer(self):
		while self.queue.qsize() < 1:
			print("sleeping..")
			await asyncio.sleep(.5)


if __name__ == "__main__":
	bq = Queue(1)
	classObj = Module_serial(bq)
	classObj.read_serial()
	
	
	loop = asyncio.get_event_loop()
	task = loop.create_task(classObj.read_serial())
	# asyncio.set_event_loop(loop)
	# try:
	# asyncio.ensure_future(classObj.read_serial())
	loop.run_until_complete(classObj.timer())
	
	result = bq.get()
	
	
	
	print(result)
	

	# except KeyboardInterrupt:
	# 	pass
	# finally:
	# 	print("Closing loop")
	# 	loop.close()
