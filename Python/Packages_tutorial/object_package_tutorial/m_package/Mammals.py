'''
Mammals Class
'''
class Mammals(object):
	
	def __init__(self):
		'''Constructor fro the class'''
		#Create some members stuff
		self.members = ['Tiger', 'Elephan', 'Wild Cat']
	
	def printMembers(self):
		print('Printing members of the Mammals class')
		for member in self.members:
			print('\t {}'.format(member))