#!/usr/bin/python3
'''
 An example to thread and pass information from child thread 
'''
import multiprocessing
from multiprocessing import Process, Queue
import time
import threading



def f(q):
	while True:
		time.sleep(2)
		
		#purge the old value if exist
		if q.qsize() > 1:
			q.get() # clear the old value
		else:
			q.put([40, None, 'hello']) #input new value

#***make sure you specify byte size for queue otherwise it will be infinte and during collision
# extra data will keep getting add to memory --> memory leak!
q = Queue(byte_size)
p = Process(target=f, args=(q,))
p.start()
while True:
	print("GUi updating")
	time.sleep(1)
	
	#This is necessary otherwise the sleep delay will affect the main loop
	if q.qsize() > 0:
		print(q.get())    # prints "[42, None, 'hello']"
p.join()
