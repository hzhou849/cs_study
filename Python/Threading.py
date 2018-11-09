#!/usr/bin/python3

import threading

class SummingThread(threading.Thread):
	def __inti__(self,low,high):
		super(SummingThread, self).__init__()
		self.low=low
		self.high=high
		self.total=0

	def run(self):
		for i in range(self.low, self.high):
			self.total+=i

thread1 = SummingThread(0,5000)
thread2 = SummingThread(5000,10000000)
thread1.start()
thread2.start()
thread1.join()
thread2.join()

#At this point, both threads have completed
result=thread1.total + thread2.total
print (result)