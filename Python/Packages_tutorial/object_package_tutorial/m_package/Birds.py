'''
 Birds Class
'''

class Birds(object):

	def __init__(self):
		''' Constructor for this class '''
		#Create members
		self.members = ['Sparrow', 'Robin', 'Duck']

	def printMembers(self):
		print("Printing members:")
		for member in self.members:
			print("\t{}".format(member))

