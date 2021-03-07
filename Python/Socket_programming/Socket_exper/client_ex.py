#! /usr/bin/python3

'''
client_ex.py

CLIENT

Experimental Socket data traffic test

Kill command in terminal:
sudo lsof -t -i tcp:<port_number> | xargs kill -9


'''

import socket
import os
import subprocess



class Client_socket(object):

	def __init__(self):
		'''
		Constructor
		'''
		# self.HOST = "10.113.137.1"
		# self.HOST = socket.gethostname()
		self.HOST = "192.168.1.1"
		self.PORT = 9999
		self.M_SOCKET = socket.socket(socket.AF_INET,socket.SOCK_STREAM)



	def connect(self):

		# try:
		self.M_SOCKET.connect( (self.HOST, self.PORT) )

		# except socket.error as error_msg:
		# 	print("Socket connect error [{}]".format(error_msg))

		FULL_BUFFER = ['*'] * 4096

		while True:
			# Create Data Buffer
			data_buffer = self.M_SOCKET.recv(4096)

			# Get the first two characters
			if data_buffer[:2].decode("utf-8") == 'qc':
				self.M_SOCKET.sendall(str.encode("Quiting Client side"))
				self.M_SOCKET.close()
				exit()

			elif str(data_buffer.decode("utf-8")) == 'KILL_CODE':
				self.M_SOCKET.sendall(str.encode("KILL code received on client"))
				self.M_SOCKET.close()
				exit()

			elif str(data_buffer.decode("utf-8")) == 'START_TEST':
				for i in range (0, 10):
					print("sending packet[{}]".format(i))
					self.M_SOCKET.sendall(str.encode(str(FULL_BUFFER)))

if __name__ == '__main__':
	c_socket = Client_socket()
	c_socket.connect()
