#!/usr/bin/python3

import tkinter as tk
import logging
import os
import sys

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

logging.basicConfig(
    format='[%(levelname)-8s] %(lineno) 4d line : %(message)s',
    level=logging.CRITICAL)
log = logging.getLogger(__name__)
log.setLevel(logging.DEBUG)


class UiMainWindow(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master=master)
        self.pack()

    def setup_ui(self):
        self.master.title("ODUINO")
        self.master.resizable(False, False)

        '''
        UI 설정
        '''
        self.img = tk.PhotoImage(file=os.path.join(
            BASE_DIR, "hardkernel-200.png"))
        self.img_label = tk.Label(self)
        self.img_label["image"] = self.img

        self.quit_button = tk.Button(self)
        if len(sys.argv) > 1:
            self.quit_button["text"] = "QUIT\n" + sys.argv[1]
        else:
            sys.exit()
        self.quit_button["fg"] = "red"

        self.img_label.grid(row=0, column=0)
        self.quit_button.grid(row=1, column=0)


class MainWindow(UiMainWindow):
    def __init__(self, master=None):
        super().__init__(master=master)
        self.setup_ui()

        '''
        기능
        bind, command
        '''
        self.quit_button.bind("<Button-1>", self.quit_oduino)

    def quit_oduino(self, event):
        self.master.destroy()

wpid = os.fork()
if wpid == 0:
    app = tk.Tk()
    main_window = MainWindow(app)
    app.mainloop()
