#! /usr/bin/python3


'''
Class syntax

inheritance, 

'''

class Test_module:
	#the constructor can accept args ie (n, 0)
	def __init__(self,n, o): #self is 'this' refering to this instance
		self.field1 = n
		self.field2 = o
	
	def function(self): #need to pass self to accept self members
		if self.field2 == "o":
			print(self.field1)
		else:
			print("something else")


#Creating the object
t = Test_module("foo", 1)
t.function()