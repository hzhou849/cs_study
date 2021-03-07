def close_window(self):
		'''
			Terminate windows on clicking 'x' close button
		'''
		global continueThreadExec_rx
		global continueThreadExec_tx
		global p, p2

		# self.popup_thread_wait()

		if messagebox.askokcancel("Quit", "Are you sure you want to quit?"):
		
			try:
				os.system("echo 'terminating processess.'")
			except:
				print("termination failed")

			print("shutdown successful.")
			continueThreadExec_rx = False
			continueThreadExec_tx = False
			self.start_test_running = True # spoof this flag to trick the hot plug detect handler to not restart

			
			try: 
				# p.kill()
				# p2.kill()
				if (self.q_bandwidth[0] > 500.0) or (self.q_bandwidth[1] > 500.0):
					self.iperf_thread = module_iperf.iperf_thread(self.iperf_thread_q,'kill').start()
				# os.system('clear')

				#wait for serial connection for hot_plug_detect to close
				self.wait_hpd_thread_close()
				print("1589 - start test running?: " + str(self.start_test_running))

				#Log the successful closure of appliation
				module_logger.write_to_log("Application successfully exited.")
				print("")
				print("Application successfully closed. Press Ctrl-c to return to terminal")
			except Exception as e:
				print ("caught condition - OK failed kill:" + str(e))
			self.main.destroy()


#=======================Main loop =======================================

def main():
	
	root = Tk()
	root.resizable(width=False, height=False)
	root.geometry("950x600+100+100")
	root.attributes("-topmost",True)
	# root.attributes("-disabled', True")
	app=App_Frame(root)
	

#call function on call or disable closing to keep open
	root.protocol("WM_DELETE_WINDOW", DISABLED) #re-route back from main to self
	root.protocol("WM_DELETE_WINDOW", app.close_window) #re-route back from main to self

	# os.system('clear')

	
	root.mainloop()

if __name__ == '__main__':
	main()