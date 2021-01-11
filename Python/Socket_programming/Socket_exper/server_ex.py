#! /usr/bin/python3

'''
server_exper.py

HOST 

Experimental Socket data traffic test

kill command?
sudo lsof -t -i tcp:8000 | xargs kill -9


Socket Programming Tutorial

Application to connect to CLIENT via Socket and Controll the shell

NOTE Sockets created using socket.SOCK_STREAM are TCP sockets
                     using socket.SOCK_DGRAM  are UDP sockets
					 
					 AF_INET = IPV4
					 AF_INET6 = IPV6

Host - Host IP
Port - Port created to establish socket connection

SERVER
 socket -> bind -> listen -> accept   ^->recv/send v        ^->recv(closing msg) --> close
Client
                   socket -> connect  ^ ->send/rcv v->close ^


Check port is open
ip=("127.0.0.1", 9999)
check = a_socket.connnect_ex(ip)

if check == 0:
	# Port open
else:
	# Port closed.

'''

import socket
import sys

class Server_socket(object):

	def __init__(self):
		'''
		Constructor
		'''
		# self.HOST = ""   #Server is blank
		self.HOST = socket.gethostname()
		self.PORT = 9999
		self.conn = None
		self.address = None

		print("Host name [{}]".format(self.HOST), flush=True)

		# (ipv4, TCP/IP protocol)
		try:
			self.m_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		except socket.error as error_msg:
			print("SOCKET Create ERROR: [{}]".fomrat(error_msg))
	


	def bind_socket(self):
		'''
		Binding the socket instance to listen for connections
		'''
		
		try:
			# Bind the socket to IP and PORT#
			self.m_socket.bind( (self.HOST, self.PORT) )

			# Listen on the socket and timeout allowed of 'bad connections' 
			self.m_socket.listen(5)
			print("Binding port: [{}]".format(self.PORT))
		
		except socket.error as error_msg:
			print("Socket Binding Error: [{}] retrying...".format(error_msg))
			bind_socket()

		print("BINDING PORT....OK")



	def conn_socket_accept(self):
		'''
		Establish connection with client (socket must be listening to work)

			returns:  socket <conn>
		'''
		# set the timeout time <seconds>
		# self.m_socket.settimeout(2)
		to_counter = 0

		# while True:
			# try:
				# Returns connected socket, client IP address
		self.conn, self.address = self.m_socket.accept()
		print("Connection has been established!!\t IP:{} | PORT: {}".format(self.address[0], self.address[1]))
			# except socket.timeout:

			# 	if to_counter % 4 == 0:
			# 		print("failed    {}".format(to_counter), end='\r')
			# 	elif to_counter % 3 == 0:
			# 		print("failed.   {}".format(to_counter), end='\r')
			# 	elif to_counter % 2 == 0:
			# 		print("failed..  {}".format(to_counter), end='\r')	
			# 	elif to_counter % 1 == 0:
			# 		print("failed... {}".format(to_counter), end='\r')
			# 		# to_counter = 0
			# 	to_counter += 1
			# 	continue
			# break

		# Send a command to the client computer
		self.send_command()

		# Terminate connection after send_command() has completed.
		self.conn.close()


	def send_command(self):
		'''
		Sends a command to the client system
		'''

		while True:
			# Store the string comamnnd, data send over sockets must be encoded to bytes.
			cmd = input()

			if cmd == 'qc':
				self.conn.close()
				self.m_socket.close()
				sys.exit()

			if cmd == 'quit':
				self.conn.send(str.encode('KILL_CODE'))
				client_response = str(self.conn.recv(4096 ), "utf-8")
				
				if 'KILL' in str(client_response) :
					self.conn.close()
					self.m_socket.close()

				# close the command prompt shell
				sys.exit()

			if cmd == 'test':
				self.conn.send(str.encode('START_TEST'))
				client_response = str(self.conn.recv(4096), "utf-8")

				print("Client response: {}".format(client_response))



	def close_connection(conn):
		'''
		Close out the connected socket
		
			Args: Socket conn
		'''
		conn.close()


if __name__ == '__main__':

	# Create Socket
	m_obj = Server_socket()

	# Bind the socket()
	m_obj.bind_socket()

	# Listen/Accept incoming socket connection
	m_obj.conn_socket_accept()


