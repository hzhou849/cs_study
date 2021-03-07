#! /usr/bin/python3

'''
Bandwidth calculator modified standalone version

This application will retrieve the bandwidth for the desired port
'''

import sys							# handle command line arguments
import os
import getopt						# parse for command line options arguments
import subprocess
import queue						# shared queue
import time


class Module_bw_calc:
	# constructor (can accept args ie (n, o)
	def __init__(self, ethDevName, queue):
		''' Constructor 
			
			Args:
				ethDevName(str):	Ethernet device name ie "eth0, eth1 ...eth[n]"
		'''
		self.eth_dev_list = {'eth0'}
		self.ethDevName = ethDevName
		self.queue = queue

	def get_bandw_values (self, direction):
		''' Get bandwidth values - Retrieves the bandwidth values from the OS

			Args:	
				self:			The instance of this object and all its instance variables
				direction(str): 	tx - Transmit
									rx - Receive
				
			Returns: 
				dev_traffic {eth0 : <value>,
								eth1 : <value>, 
								eth2 : <value>,
								eth3 : <value>}  
		'''
		dev_traffic={}								# Create an empty dictionary list
		if direction == 'rx':
			value = '$2'
		elif direction == 'tx':
			value = '$10'
		else:
			raise Exception("Bandwidth traffic direction no specified.")

		#Get Eth RX receive bandwidth
		# Using subprocess, each command | gets piped into the next command and stacked.
		cmd1 = subprocess.Popen("cat /proc/net/dev", shell=True, stdout=subprocess.PIPE)
		cmd2 = subprocess.Popen("grep " +self.ethDevName, shell=True, stdin=cmd1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		cmd3 = subprocess.Popen("awk '{print " + value + "}'", shell=True, stdin=cmd2.stdout, stdout=subprocess.PIPE, stderr= subprocess.PIPE)

		#close the unused pipes
		cmd1.stdout.close()
		cmd2.stdout.close()

		traffic_bw_bytes,err = cmd3.communicate()								# communicate the subprocesses must include ',err'
		traffic_bw_bytes = str(traffic_bw_bytes.decode('ascii').strip('\n'))	# parse the data
		
		# cast the data to a float 
		if traffic_bw_bytes:
			dev_traffic[self.ethDevName] = float(traffic_bw_bytes)
		else:
			dev_traffic[self.ethDevName] = float(0)
		
		return dev_traffic

	
	def calc_indiv_bw( self, bytes_previous, bytes_current): 
		''' Calcute the bandwidth individually by the interfaces
			Args: 
				bytes_previous{str: float} - "older" bandwidth value
				bytes_current {str: float}-  "newer" bandwidth value

			returns:
				totalBytes_iface {eth[x] : <value>}
		'''

		totalBytes_iface={}

		for x in self.eth_dev_list:
			temp = 0

			# get the differnce (abosolute value)
			temp = abs(bytes_current[x] - bytes_previous[x])


			# multiply by 8 to get bits, then divide 1000 for kb		
			temp = (temp * 8) / 1000

			totalBytes_iface[x] = temp

			return totalBytes_iface

	
	def calc_total_bw( self, bytes_prev, bytes_current):
		''' Calculate the Total bandwidth of all interfaces
			
			Args: 
				bytes_previous{str: float} - "older" bandwidth value
				bytes_current{str: float}-  "newer" bandwidth value

			returns:
				total_bytes_sec 
		'''

		total_bytes_sec = 0

		for x in self.eth_dev_list:
			temp = 0

			temp = abs(bytes_current[x] - bytes_prev[x])		# get absolute non-negative value
			total_bytes_sec = total_bytes_sec + temp			# accumulate the values

			total_bytes_sec = (total_bytes_sec * 8) / 1000		# get bits and divide by 1000 for kb/s

			return total_bytes_sec


	def run(self):
		''' NOTE: delays here can significantly impact the queue and stall the GUI if no properly synced.

		return:
			self.queue.put([ rx_total_bps		- total bytes/sec recieved bandwidth
							 tx_total_bps		- total bytes/sec transmit bandwidth
							 {ind_iface_bw_rx}	- individual interface bandwidth received
							 {ind_iface_bw_tx}	- individual interface bandwidth transmit
							])
			"ERROR"(str)						- Error code
		'''
		rx_total_bps = 0
		tx_total_bps = 0

		try:
			# Get the rx/tx total bandwidth values for before and after
			rx_previous = self.get_bandw_values('rx')
			time.sleep(1)				# wait 1 second for the next value to calculate bandwidth per second
			rx_current = self.get_bandw_values('rx')

			tx_previous=self.get_bandw_values('tx')
			time.sleep(1)
			tx_current = self.get_bandw_values('tx')

			# sum up the totals
			rx_total_bps = self.calc_total_bw(rx_previous, rx_current)
			tx_total_bps = self.calc_total_bw(tx_previous, tx_current)

			# calculate bw by the individual interfaces
			ind_iface_bw_rx = self.calc_indiv_bw(rx_previous, rx_current)
			ind_iface_bw_tx = self.calc_indiv_bw(tx_previous, tx_current)

			# Pipe results back into the shared queue
			# 1 item as an array
			self.queue.put( [rx_total_bps, tx_total_bps, ind_iface_bw_rx, ind_iface_bw_tx] )

		except Exception as e:
			print("Error detected:" + str(e))
			self.queue.put("ERROR")




def main(argv):
	inputfile = ''
	outputfile = ''

	try:
		opts,args = getopt.getopt(argv, "hi:o:", ["ifile=", "ofile="]) # if option requires arg use ":" ie 'i' and 'o' both do

	except getopt.GetoptError:
		print ('Usage: module_band_calc_sas.py -i <inputfile> -o <outputfile>')
		sys.exit(2)
		
	for opt, arg in opts:

		if opt == '-h':
			print ('help guide: run with args')
			print ('Usage: module_band_calc_sas.py -i <inputfile> -o <outputfile>')
			sys.exit()
		elif opt in ("-i", "--ifile"):
			inputfile = arg
		elif opt in ("-o", "--ofile"):
			outputfile = arg
		print("opt: " + str(opt))
		
	print('Input file is "', inputfile)
	print('Output file is "', outputfile)

if __name__ == "__main__":
	main(sys.argv[1:])

