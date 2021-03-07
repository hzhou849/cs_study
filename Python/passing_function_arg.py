def add_task(self, func, *args, **kargs):
		'''
		add tasks to queue
		Args: take function(args)
		'''
		self.qtasks.put((func, args, kargs))	
	