#!/usr/bin/bash


'''
Entry points


"if __name__ == "__main__":"

by default __name__ is a variable that will contain "__main__"
it is used as an entry point. Similar to main driver class in C

Calling functions:

example - if we have 2 python files:

[class1.py]
myFunc(string):
	print("message")
	return string

#this will only execute if you are running class1.py
if __name__ == "__main__":
	print("I am in class1.py")
	a=myFunc("something")
	print (a)

[caller_class.py]
import class1.py

class1.myFunc("blah")



'''

