#! /usr/bin/python3

'''
Inheritance

'''

class Base:
	def display(self):
		print("display Base class")

class Derived(Base):
	def __init__(self):
		print ("Derived Object created")
		self.der_value1 = 1
		self.der_name = "Derived 1"
	
	#will override base method if the name is 'display'
	def ddisplay(self):
		print("Derivived display {0} {1}".format(self.der_value1, self.der_name))
	

class Derived2(Base):
	def __init__(self):
		print("Derived2 Object created")
		self.der_value1 =2 
		self.der_name = "Derived 2"
	
	#will override base method if the name is 'display'
	def ddisplay(self):
		print("Derived display {0} {1}".format(self.der_value1, self.der_name))



if __name__ == '__main__':
	baseObj = Base()
	baseObj.display()

	d1 = Derived()
	d1.ddisplay()

	d2 = Derived2()
	d2.ddisplay()
	d2.display()


	base2 = Base()
	dervived2 = Derived()

	#check if if c is an object of Base
	print(isinstance(base2,Base))

	#check inheritance
	print(issubclass(Derived, Base))