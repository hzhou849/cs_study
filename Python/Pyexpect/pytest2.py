#!/usr/bin/python3
import pexpect
import sys

# User variables
user='root'
ip='169.254.30.33'
password='Medtronic'
PROMPT='sra01:/root# '
PROMPT2='sra01:/# '



'''
Create an SSH session with remote computer
'''
# ssh = pexpect.spawn("ssh %s@%s" % (user,ip))
ssh=pexpect.spawn('ssh root@169.254.30.33', echo=True)
ssh.setecho(True)
#what is popenSpawn?
# print(ssh)



def displayOut():
	'''
	Display all termninal output before and after
	the commands passed during the expect session.
	''' 
	print(ssh.before.decode(encoding="ascii", errors="ignore"))
	print(ssh.after.decode(encoding="ascii", errors="ignore"))
	# print(ssh.read())


try:
	# expect one of these args
	i = ssh.expect(['password:', 'continue connecting (yes/no)?', PROMPT ],timeout=5)
	if i==0:
		ssh.sendline(password)
	elif i== 1:
		ssh.sendline('yes')
		print("made it this far")
		# ssh.sendline('ls')
	elif i == 2: # connection successful
		print('\nConnection successful!...')
		displayOut()  #helper function to display terminal output
		ssh.sendline('ls  -l')
		ssh.sendline('cd ..')
		ssh.expect('sra01:/# ', timeout=120)
		ssh.sendline('ls')
		ssh.expect('sra01:/# ') # must give the expected prompt for code to work
		ssh.sendline('cd /app/QnxStressTest_ver1.0')

		'''
		if output matches the options, continue to execute other commands
		else quit
		'''
		result = ssh.expect(['sra01:/app/QnxStressTest_ver1.0#.* ', '.*No such file or directory.*'])
		if result == 0:
			print("passed")
			ssh.sendline('./cpu_stress_test.sh')
			# ssh.sendline('ping -c1 -i2 169.254.30.9')
			displayOut()

		elif result ==1:
			print("failed.")
		displayOut()

		print('test')
		print(ssh.read)
		ssh.sendline('exit')
		ssh.sendline('exit')

		displayOut()
		ssh.interact()
		ssh.logfile=sys.stdout

		
		'''
		if the child exited normally then exitstatus will store the exit return code and signalstatus 
		will be None. If the child was terminated abnormally with a signal then signalstatus will 
		store the signal value and exitstatus will be None:
		- Requires ssh.close() to work.
		'''
		ssh.close()
		print(ssh.exitstatus, ssh.signalstatus) #

	else:
		print("nothing")


except pexpect.EOF:
	print("EOF")
except pexpect.TIMEOUT:
	print("TIMEOUT")
# else:
# 		r=ssh.read()
# 		print(r)
# ssh.close()

