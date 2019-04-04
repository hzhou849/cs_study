#!/usr/bin/python3
import tkinter as tk


class App(tk.Frame):
	def __init__(self, master):
		tk.Frame.__init__(self, master, height=42, width=42)
		self.entry=tk.Entry(self)
		self.entry.focus()
		self.entry.pack()
		self.clear_button = tk.Button(self, text="Clear text", command=self.clear_text)
		self.clear_button.pack()

	def clear_text(self):
		self.entry.delete(0,'end')

def main():
	root = tk.Tk()
	App(root).pack(expand=True, fill='both')
	root.mainloop()

if __name__ == "__main__":
	main()