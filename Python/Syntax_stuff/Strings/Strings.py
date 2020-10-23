#!/usr/bin/python3

#new and best way to print multiple values
print("value: {} {} {}".format(value1, value2, value3)
print("Replacement values: {0} {1}, {2}, {3}".format(value, value2, value3, 677))

# noinspection PyUnresolvedReferences
'''
Convert byte to Ascii
'''
#response =ser.read(bytes_var)
#response = response.decode('ascii')

'''
No new line after print
'''
print("blah", end='') # default end = '\n'

'''
String array syntax
'''
parrot = "Norewgian Blue"
print(parrot)
print(parrot[0])  # N
print(parrot[0:6]) #Norweg
print(parrot[6:]) #ian Blue. will print the end automatically
print(parrot[-1]) # 'e' goes back and overflows.
print(parrot[0:6:2]) #skip 2 characters at a time




'''
======================================================================
substring
======================================================================

'''

number = "9,233,372,036,854,775,807"
print(number[1::4]) # start at cell[1] and skip 4 characters prints only commas ,,,,, *should test

number2 = '1, 2, 3, 4, 5'
print(number2[0::3]) #12345 extracted out the numbers


print("Hello" * 5) # prints statement five times


today = 'friday'
print("day" in today) #returns true. substring day is in the var today 

''' 
======================================================================
Format specifiers LEFT justify
======================================================================

'''
i=20
print("No. {0:2} squared is {1:<4} and cubed is {2:<4}".format(i, i**2, i**3)) #left justified


''' 
======================================================================
Format specifiers *deprecated from PYTHON 2
======================================================================

'''
var = 31
var_str = 'blaharg'
print("\nFormat specifier some line %d" % var)
print ("Format specifier %d, %s, %d\n" % (var, var_str, 32))

#2d 4d means how many max characters allowed
for i in range(1, 12):
	print("No. %2d squared is %4d and cubed is %4d" %(i, i**2, i**3))


print("%12.50f" %(22/7)) #12 is how many chars main number, and 50 char after decimal 
print("pi is approx: {0:12.50f}".format(22/7)) # NEW PYTHON 3 style

for i in range (1,12): #{a:b} b is how wide we want to allocate space for.
	print("No. {0:2} squared is {1:<4} and cubed is {2:<4}".format(i, i**2, i**3))

print("\n")
''' 
======================================================================
Replacement Fields - used in PYTHON3
use {num} and '.format' to use as a place hodler for multiple values
======================================================================
'''
value = 1234
value2 = 'VALUE2'
value3 = 888
print ("something is {0} blah blah".format(value))
print("Replacement values: {0} {1}, {2}, {3}".format(value, value2, value3, 677))


''' 
======================================================================
Triple Quotes """ means data on multiple lines
======================================================================
'''

print (""" value: {0}
value: {1}
value2:{2}
""".format('A', 'B', 'C'))
