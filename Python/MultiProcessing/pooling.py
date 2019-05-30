#!/usr/bin/python3

'''
Sync: Blocking operations.
Async: Non blocking operations.
Concurrency: Making progress together.
Parallelism: Making progress in parallel.

Mutliprocessing pooling

- utilize all the work among available cores (all processing power)
  dividing the work among the cores is called 'Map'

- when you aggregate the results back into one single output
 called 'Reduce'

work will be divided among available cores as evenly as possible (map)
input: [a,b,c,d,e]

 core1 {a,e}

 core2 {b}

 core3 {c}

 core4 {d}

 combining the results back output {abcde (post processed)} ->reduce

TERMINATING POOLS / CLEANUP:

when you using Pool() objects
	you must call p.close() first then p.join() to wait 

	p.close() - terminate the  worker process when all assigned work
	            is completed. Usually called when you are not gonna
				submit more work to the pool instance.
	
	p.join() - wait for the worker process to terminate.
	result


https://stackoverflow.com/questions/26520781/multiprocessing-pool-whats-the-difference-between-map-async-and-imap

There are two key differences between imap/imap_unordered and 
map/map_async:

The way they consume the iterable you pass to them.
The way they return the result back to you.

MAP -  consumes your iterable by converting the iterable to a list 
	(assuming it isn't a list already), breaking it into chunks, and 
	sending those chunks to the worker processes in the Pool. Breaking the 
	iterable into chunks performs better than passing each item in the 
	iterable between processes one item at a time - particularly if the 
	iterable is large. However, turning the iterable into a list in order 
	to chunk it can have a very high memory cost, since the entire list 
	will need to be kept in memory.

IMAP -  doesn't turn the iterable you give it into a list, nor does 
	break it into chunks (by default). It will iterate over the iterable 
	one element at a time, and send them each to a worker process. 
	This means you don't take the memory hit of converting the whole 
	iterable to a list, but it also means the performance is slower for 
	large iterables, because of the lack of chunking. This can be 
	mitigated by passing a chunksize argument larger than default of 1, 
	however.

The other major difference between imap/imap_unordered and map/map_async, 
is that with imap/imap_unordered, you can start receiving results 
from workers as soon as they're ready, rather than having to wait for 
all of them to be finished. With map_async, an AsyncResult is returned 
right away, but you can't actually retrieve results from that object 
until all of them have been processed, at which points it returns the 
same list that map does (map is actually implemented internally as 
map_async(...).get()). There's no way to get partial results; 
you either have the entire result, or nothing.

imap and imap_unordered both return iterables right away. With imap, the results will be yielded from the iterable as soon as they're ready, while still preserving the ordering of the input iterable. With  imap_unordered, results will be yielded as soon as they're ready, regardless of the order of the input iterable. So, say you have this:

import multiprocessing
import time

def func(x):
    time.sleep(x)
    return x + 2

if __name__ == "__main__":    
    p = multiprocessing.Pool()
    start = time.time()
    for x in p.imap(func, [1,5,3]):
        print("{} (Time elapsed: {}s)".format(x, int(time.time() - start)))

This will output: (p.imap)
3 (Time elapsed: 1s)
7 (Time elapsed: 5s)
5 (Time elapsed: 5s)

If you use p.imap_unordered instead of p.imap, you'll see:
results are returned ASAP
3 (Time elapsed: 1s)
5 (Time elapsed: 3s)
7 (Time elapsed: 5s)

If you use p.map or p.map`_async().get(), you'll see:
- because map/map_async does not allow partial results
  each item in the array iteration will have to wait for
  the slowest one to finish (in this case 5secs) before
  it can aggregate all the data

3 (Time elapsed: 5s)
7 (Time elapsed: 5s)
5 (Time elapsed: 5s)

Primary reasons to use imap/imap_unordered over map_async are:
1) Your iterable is large enough that converting it to a list would cause 
	you to run out of/use too much memory.
2) You want to be able to start processing the results before all of them are completed.


'''
import time
import multiprocessing

# some function to simulate processing
def task(n):
	return n*n


# a more cpu intensive task
def task2(n):
	print("n: " + str(n))
	sum = 0
	for x in range(10):
		sum += x*x
		print(x)
	return sum



if __name__ == '__main__':
	# EXAMPLE 1
	array= [1,2,3,4,5]
	# Create pool object
	proc_pool = multiprocessing.Pool()

	# map() will divide the work among the available cores
	# and return the result
	# map(<function>, <args>)
	result = proc_pool.map(task, array)
	print(result)


	#EXAMPLE 2
	t1 = time.time()
	proc_pool2 = multiprocessing.Pool()
	result2 = proc_pool2.map(task2, range(3)) # run task2(n) fucntion passing for all total 0,1,2...n times

	#terminate the worker processes when
	proc_pool2.close()

	#wait for it to terminate
	proc_pool2.join()
	pool_time = (time.time()-t1)
	print(result2)


	#compare the time using traditional Serial processing method

	t2 = time.time()
	result_arr = []
	for x in range(10000):
		result.append(task2(x))

	# as processing load increases, pool will perform better and better
	print("Serial Processing Elaspsed time: {}".format(time.time() -t2))
	print("Elapsed pool processing time: {}".format(pool_time ))