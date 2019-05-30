#!/usr/bin/python3

'''
filters out and converts string to int
'''

cleanedNumber= ''
number = "123,245,6678,8982,1729,88989"
for i in range(0, len(number)):
	if number[i] in '123':
		cleanedNumber = cleanedNumber + number[i]
		print("Number: {}".format(number[i]))
newNumber = int(cleanedNumber)
print("final conversion: {}".format(newNumber))
