'''
Implementation self.after()

Setup and termination of self.after GUI updater

'''

def tester(self):
	'''
	Setup the self-updating loop
	'''

		print(self.rbValue.get())

		# assing the PID of the loop
		self.loop_id=self.after(200, self.tester)

		

def onExit(self):
	'''
	terminate the GUI and the self.after scheduled
	loops
	'''
	print(self.loop_id)

	
	'''
	Method 1 - kill the scheduled self updating function
	'''
	# self.master.after_cancel(self.tester) # kill the scheduled self.after loop
	
	#kills the GUI
	self.master.destroy()
	
	
	'''
	Method 2 - kill the scheduled loop PID *must be done after you
				destry the GUI window
	'''
	self.master.after_cancel(self.loop_id)
