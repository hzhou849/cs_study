#! /usr/bin/python3

'''
AsyncIO - Python3.5+

Event loop that manages and tracks I/O events and switches
and pauses taskes as needed. Saves processing time over threads/processes
as it will not need to iterate/poll to check if a thread is done - it knows.


Sync: Blocking operations.
Async: Non blocking operations.
Concurrency: Making progress together.
Parallelism: Making progress in parallel.
'''


import asyncio
import datetime
import random
import time

#Example 1
# async def my_sleep_func():
# 	await asyncio.sleep(random.randint(0,5))

# async def display_date(num, loop):
# 	end_time = loop.time() + 10.0
# 	while True:
# 		print("Loop: {} Time: {}".format(num, datetime.datetime.now()))
# 		if (loop.time() +1.0) >= end_time:
# 			break
# 		await my_sleep_func()

# loop = asyncio.get_event_loop()

# asyncio.ensure_future(display_date(1, loop))
# asyncio.ensure_future(display_date(2, loop))

# loop.run_until_complete()

# loop.close()


# Example 2
async def firstWorker():
	while True:
		await asyncio.sleep(1)
		print("First worker executed.")

async def secondWorker():
	while True:
		await asyncio.sleep(1)
		print("Second worker executed")

loop = asyncio.get_event_loop()

try:
	asyncio.ensure_future(firstWorker())
	asyncio.ensure_future(secondWorker())
	loop.run_forever()
except KeyboardInterrupt:
	pass
finally:
	print("Closing loop")
	loop.close()
