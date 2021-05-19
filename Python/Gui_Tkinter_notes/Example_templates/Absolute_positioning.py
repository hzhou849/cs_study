#!/usr/bin/env python3

from PIL import Image, ImageTk
from tkinter import Tk, BOTH
from tkinter.ttk import Frame, Label, Style

class Application(Frame):

	def __init__(self):
		super().__init__()

		self.initUI()

	def initUI(self):
		
		self.master.title("GPIO Tester")
		self.pack(fill=BOTH, expand=1)

		Style().configure("TFrame", background="#0F0F0F")
		
		img_analytics = Image.open("analytics.png")
		image1 = ImageTk.PhotoImage(img_analytics)
		label1 = Label(self, image=image1)
		label1.image=image1
		label1.place(x=20, y=20)

		img_tools = Image.open("tools.png")
		image2 = ImageTk.PhotoImage(img_tools)
		label2 = Label(self, image=image2)
		label2.image = image2
		label2.place(x=40, y=160)

def main():

	root = Tk()
	root.geometry("300x280+300+300")
	app = Application()
	root.mainloop()

if __name__ == '__main__':
	main()


# **************Button placement ******************
# #!/usr/bin/env python3

from tkinter import Tk, RIGHT, BOTH, RAISED
from tkinter.ttk import Frame, Button, Style

class GPIO_Application(Frame):

	def __init__(self):
		super().__init__()

		self.initUI()

	def initUI(self):
		self.master.title("GPIO Tester")
		self.style = Style()
		self.style.theme_use("default")

		frame = Frame(self, relief=RAISED, borderwidth=1)
		frame.pack(fill=BOTH, expand=True)
		
		self.pack(fill=BOTH, expand=True)

		closeButton = Button(self, text="Close", command=self.quit)
		closeButton.pack(side=RIGHT, padx=5, pady=5)
		okButton = Button(self, text="OK")
		okButton.pack(side=RIGHT)

def main():
	root = Tk()
	root.geometry("300x200+300+300")
	app = GPIO_Application()
	root.mainloop()

if __name__ == '__main__':
	main()	