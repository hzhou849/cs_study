#! /usr/bin/python3

'''
Threading 

Shared var - no lock impletemented **requires mutex for threadsafe
_thread module is now deprecated
python3 use the 'import threading' package instead

add queue
'''

import threading
import time

exitFlag = 0

class ThreadObj (threading.Thread):
	def __init__(self, threadID, name, counter):
		threading.Thread.__init__(self)
		self.threadID = threadID
		self.name = name
		self.counter = counter

	def run(self):
		print("Starting " + self.name)
		print_time(self.name, self.counter, 5)
		print("Exiting " + self.name)

	
def print_time(threadName, delay, counter):
	while counter:
		if exitFlag:
			threadName.exit()
		time.sleep(delay)
		print("%s:  %s" % (threadName, time.ctime(time.time())))
		counter -= 1


#Create new threads
t1 = ThreadObj(1, "Thread-1", 1)
t2 = ThreadObj(2, "Thread-2", 2)

#start new threads
t1.start()
t2.start()
t1.join()
t2.join()
print("Exiting Main Thread")
