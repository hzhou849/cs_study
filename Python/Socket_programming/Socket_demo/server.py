#! /usr/bin/python3

'''
server.py

HOST

kill command?
sudo lsof -t -i tcp:8000 | xargs kill -9


Socket Programming Tutorial

Application to connect to CLIENT via Socket and Controll the shell

NOTE Sockets created using socket.SOCK_STREAM are TCP sockets
                     using socket.SOCK_DGRAM  are UDP sockets


Host - Host IP
Port - Port created to establish socket connection

SERVER
 socket -> bind -> listen -> accept   ^->recv/send v        ^->recv(closing msg) --> close
Client
                   socket -> connect  ^ ->send/rcv v->close ^

'''

import socket
import sys

def create_socket():
	'''
	Create a Socket to connect 2 computers
	'''
	try:
		global host
		global port
		global m_socket

		# Leave blank for SERVER, not needed
		host = "" 	
		# port = 65432 # or 9999
		port = 9999 # Works for Medtronic network

		# Create the socket instance
		m_socket = socket.socket()



	except socket.error as error_msg:
		print("Socket Error [{}]".format(error_msg))



def bind_socket():
	'''
	Binding the socket and listening for connections
	'''
	try:
		global host
		global port
		global m_socket

		# Bind the socket to ip and port#
		# Server bind does not actually require a host ip as it will take the host ip itself?
		m_socket.bind( (host, port) )
		
		# Listen on the socket for a client connection 5 is the timeout of 'bad connections'
		# Connection cannot be established unless the listen() is established
		m_socket.listen(5)
		print("Biding the port: [{}]".format(port))
	
	except socket.error as error_msg:
		print("Socket Binding Error: [{}] retrying...".format(error_msg))
		bind_socket()



def socket_accept():
	'''
	Establish connection with a client (socket must be listening to work)
	'''
	# Two variables 
	# Connection object is stored in conn
	# IP address will be stored in address
	# Note accept() is blocking, next line of code will not run until this is established
	# Note that this new socket object 'conn' is a new object seperate from the m_socket 
	# to establish a connection
	conn, address = m_socket.accept()
	print("Connection has been established!!\t IP: {} | PORT: {}".format(address[0], address[1]))


	# Send a command on client computer
	send_command(conn)

	# Close the connection
	conn.close()



def send_command(conn):
	'''
	Sends a command(s) to client system

	Encoding string looks like this:
	The string is: pythön!
	The encoded version is: b'pyth\xc3\xb6n!'
	'''

	while True:
		# store the string command, data data sent over sockets must be encoded to bytes
		# data between computers are in format of bytes not strings. 
		cmd = input()  
		if cmd == 'quit':
			
			# Close
			conn.send(str.encode('qc'))
			client_response = str(conn.recv(1024), "utf-8")
			conn.close()
			m_socket.close()
			
			# close the command prompt shell window?
			sys.exit() 

		# Encode the string to bytes
		if len(str.encode(cmd)) > 0:
			print("Encoded command: [{}]".format(str.encode(cmd)))
			
			# Send the data to the client
			conn.send(str.encode(cmd))

			# Whenever date is received, it has to be converted back from byte format to string(Decode)
			# to be human readable.
			# recv( <max read buffer size- bytes>, <string_format> ) - *BLOCKING if no data is read
			client_response = str(conn.recv(1024), "utf-8")

			# You must add a new line at the end as this socket buffer might not 
			# have a string terminator embedded in it.
			print("Client response: {}".format(client_response), end="\n")



def main():
	create_socket()
	print("Creating socket...OK")

	bind_socket()
	print("BIND OK..")

	socket_accept()
	print("SOCKET_ACCEPT...OK")



if __name__ == '__main__':
	main()
