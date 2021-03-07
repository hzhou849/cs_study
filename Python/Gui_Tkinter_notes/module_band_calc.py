#! /usr/bin/python3
'''
Class module for handling bandwidth calculation
'''
import subprocess
from subprocess import Popen, PIPE
import time
import os
import errno
import string

#Multithreading packages
import threading
import multiprocessing
from multiprocessing import Process, Queue

#import other modules
import module_get_config

# move into class as self.xxxxx to prevent use of global variables
global ethernet_dev_list; ethernet_dev_list= module_get_config.get_eth_devices('pc1') 


class band_calc_thread(threading.Thread):
	def __init__(self, queue):
		threading.Thread.__init__(self)
		self.queue = queue

	def get_band_values(self,direction):
		dev_traffic={}
		if direction == 'rx':
			value = '$2'
		elif direction == 'tx':
			value = '$10'
		else:
			raise Exception("Bandwidth traffic direction error")
		#get Eth RX receive bandwidth
		for i in ethernet_dev_list:
			# print("iteration: "+i)
			cmd1 = subprocess.Popen("cat /proc/net/dev",shell=True, stdout = subprocess.PIPE)
			cmd2 = subprocess.Popen("grep "+i, shell=True, stdin = cmd1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
			
			cmd3 = subprocess.Popen("awk '{print "+value+"}'", shell = True, stdin = cmd2.stdout, stdout=subprocess.PIPE, stderr = subprocess.PIPE)
			
			cmd1.stdout.close()
			cmd2.stdout.close()

			traffic_band_bytes,err = cmd3.communicate()
			traffic_band_bytes = str(traffic_band_bytes.decode('ascii').strip('\n'))
			if traffic_band_bytes:
				dev_traffic[i] = float(traffic_band_bytes)
			else:
				dev_traffic[i]=float(0)
			# print(str(traffic_band_bytes) + " :"+str(i))

		return dev_traffic


	def calc_bw_individual(self, bytes_previous, bytes_current):
		'''
		calculate the bandwidth individually by the interfaces 

		returns:
			totalbytes_by_iface {eth0 : <value>,
								eth1 : <value>, 
								eth2 : <value>,
								eth3 : <value>}  
		'''
		total_bytes_by_iface ={}

		for x in ethernet_dev_list:
			temp = 0
			temp = bytes_current[x] - bytes_previous[x]

			# multiply by 8 to get bits
			temp = temp * 8 
			# divide by 1000 to kb
			temp = temp / 1000

			total_bytes_by_iface[x] = temp

		return total_bytes_by_iface

	def calc_bandwidth(self,bytes_previous, bytes_current):
		'''
		Args:
			bytes_previous: the 'before' network traffic bytes
			bytes_current: the 'after' network traffic bytes 

			Calculation takes the difference between the 'before' and 'after' bandwidth bytes over  a sec
			to get bits/second
		'''
		total_bytes_sec = 0

		for x in  ethernet_dev_list:
			temp=0 

			# print(str(x)+ " "+str(bytes_previous[x]))
			# print(str(x)+" "+str(bytes_current[x]))

			# temp = bytes_current[x] - bytes_previous[x] 
		
		
			# print (str(x)+"- old: "+str(bytes_previous[x]))
			# print(str(x)+"-current: " +str(bytes_current[x]))
			temp = (bytes_current[x]-bytes_previous[x])
			# print(str(x)+"-temp: " +str(temp))
			total_bytes_sec = total_bytes_sec + temp 
			# print ("round total:" + str(total_bytes_sec))

			#convert to bits

		# print ("total:" + str(total_bytes_sec))
		total_bytes_sec = total_bytes_sec * 8 
		# print ("bit convert-total:" + str(total_bytes_sec))
			
		total_bytes_sec = total_bytes_sec /1000
		# print ("%.2f Kbit/S" % total_bytes_sec)
		# print(total_bytes_sec)

		return total_bytes_sec

	def run(self):
		'''
		NOTE: delays here can impact the queue and stall the GUI if not synced properly with GUI updater time.
		get bandwidth values. 

		return :
			self.queue.put([rx_total_bytes_sec -total received bandwidth,
							tx_total_bytes_sec, - total transmit bandwidth
							{ind_iface_bw_rx} = , - individual interface bandwidth receive
							{ind_iface_bw_tx}  - individual interface bandwidth transmit
							])
		'''
	
		#try for each device independently?
		
		rx_total_bytes_sec = 0
		tx_total_bytes_sec = 0
		
		try:
		
			# Variables for Receive traffic

			rx_previous=self.get_band_values('rx')
			time.sleep(1)
			rx_current=self.get_band_values('rx')
			

			tx_previous = self.get_band_values('tx')
			time.sleep(1)
			tx_current = self.get_band_values('tx')

			rx_total_bytes_sec = self.calc_bandwidth(rx_previous, rx_current)
			tx_total_bytes_sec = self.calc_bandwidth(tx_previous, tx_current)

			ind_iface_bw_rx = self.calc_bw_individual(rx_previous, rx_current)
			ind_iface_bw_tx = self.calc_bw_individual(tx_previous, tx_current)
			self.queue.put([rx_total_bytes_sec,tx_total_bytes_sec, ind_iface_bw_rx, ind_iface_bw_tx])

			# print(ind_iface_bw_rx)
			
		
		except Exception as e:
			print("Error Detected:")
			print(e)
			self.queue.put('Error')



#main execution
if __name__ == '__main__':
	# q = Queue()
	# band_calc_thread(q).start()
	print("main execution" )