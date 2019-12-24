#!/usr/bin/python3

import tkinter as tk
import logging
import os

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


class MainWindow(UiMainWindow):
    def __init__(self, master=None):
        super().__init__(master=master)
        self.setup_ui()

        '''
        기능
        bind, command
        '''


wpid = os.fork()
if wpid == 0:
    app = tk.Tk()
    main_window = MainWindow(app)
    app.mainloop()
