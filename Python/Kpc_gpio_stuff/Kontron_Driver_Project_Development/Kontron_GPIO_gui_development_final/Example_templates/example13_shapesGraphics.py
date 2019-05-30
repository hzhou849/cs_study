'''
	Canvas is required for graphics and shapes
'''

from tkinter import *

root = Tk()

canvas = Canvas(root, width=200, height=100)
canvas.pack()

# (xpos, ypos, start x, end y) 
blackLine = canvas.create_line(0, 0, 200, 50)
redLine = canvas.create_line(0, 100, 200, 50, fill="#FF0000")

# (x-pos, y-pos,width, height  )
greenBox = canvas.create_rectangle(25, 25, 130, 60, fill="#00FF00")


# deletes canvas
canvas.delete(redLine)
canvas.delete(ALL)

root.title("GPIO Application v1.0")
root.mainloop()