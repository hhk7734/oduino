#!/usr/bin/python3

import tkinter as tk
import logging
import os
import sys

import threading
import queue
import subprocess
import shlex
import fcntl
import time

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
            log.error("Failed to find executable file.")
            sys.exit()
        self.quit_button["fg"] = "red"

        self.img_label.grid(row=0, column=0)
        self.quit_button.grid(row=1, column=0)


class MainWindow(UiMainWindow):
    def __init__(self, master=None):
        super().__init__(master=master)
        self.setup_ui()

        self.oduino = OduinoProcess(self)
        self.oduino.start()

        '''
        기능
        bind, command
        '''
        self.quit_button.bind("<Button-1>", self.quit_oduino)

    def quit_oduino(self, event):
        self.oduino.terminate_oduion()
        self.master.destroy()


class OduinoProcess(threading.Thread):
    def __init__(self, main):
        super().__init__()
        self.daemon = True
        self.main = main
        self._in_queue = queue.Queue()

    def run(self):
        command_line = sys.argv[1]
        self.popen = subprocess.Popen(shlex.split(command_line),
                                      stdin=subprocess.PIPE,
                                      stdout=subprocess.PIPE,
                                      stderr=subprocess.STDOUT)

        fd = self.popen.stdout.fileno()
        fl = fcntl.fcntl(fd, fcntl.F_GETFL)
        fcntl.fcntl(fd, fcntl.F_SETFL, fl | os.O_NONBLOCK)

        old_stdout = b''
        while self.popen.poll() is None:
            if not self._in_queue.empty():
                stdin = self._in_queue.get()
                log.debug("stdin: {}".format(stdin))
                stdin = stdin + "\n"
                self.popen.stdin.write(stdin.encode())

            stdout = self.popen.stdout.readline()
            if stdout != b'' and stdout != old_stdout:
                old_stdout = stdout
                stdout = stdout.decode()
                log.debug("stdout: {}".format(stdout[:-1]))

            time.sleep(0.1)

        log.debug("Oduino subprocess finished.")

    def write_stdin(self, msg):
        self._in_queue.put(msg)

    def terminate_oduion(self):
        self.popen.terminate()
        time.sleep(0.5)


wpid = os.fork()
if wpid == 0:
    app = tk.Tk()
    main_window = MainWindow(app)
    app.mainloop()
