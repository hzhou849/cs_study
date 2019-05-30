#!/usr/bin/python3

'''
Race test, if Thread2 finishes before thread1, it should wait, 
which is achieved by locking the second thread just after it 
finishes and force it to wait.

'''

import threading, time, random
import inspect

class Thread(threading.Thread):
	def __init__(self, t, *args):
		threading.Thread.__init__(self, target=t, args=args)
		self.start()

count = 0
m_mutex = threading.Lock()

def increment():
	global count
	# get the name of the caller function
	caller = inspect.getouterframes(inspect.currentframe())[1][3]
	print ("Inside %s\n" % (caller))
	print ("Acquiring Lock")

	#Alt method 1
	# m_mutex.acquire()

	#Alt Method 2
	with m_mutex:
		print ("lock Acquired")
		count += 1
		time.sleep(2)


def addCount():
	while count < 5:
		increment()

def addCount2():
	while count < 5:
		increment()

def main():
	t1 = Thread(addCount)
	t2 = Thread(addCount2)

if __name__=='__main__':
	main()