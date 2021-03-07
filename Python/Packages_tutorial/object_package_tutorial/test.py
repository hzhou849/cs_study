#!/usr/bin/python3

#if using import sys, you must re-declare the path to your projects each execution.
# Don't worry, the path is not stored permanently, just for the instance of the execution
import sys
# sys.path.append("./m_package")
# Import Classes from your brand new packages
print (sys.path)
from m_package import Mammals
from m_package import Birds


# Create and object of Mammals class and call a method of it
# If you did not import the class name in the __init__.py file, this is the syntax
# m_mammal = Mammals.Mammals()
# m_birds = Birds.Birds()

# If you imported the class names in the __init__.py file, you have direct acccess to
# the class names
m_mammal = Mammals()
m_birds = Birds()

m_mammal.printMembers()
m_birds.printMembers()