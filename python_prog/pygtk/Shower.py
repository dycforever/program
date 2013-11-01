#!/usr/bin/python
import os
from gi.repository import Gtk, Pango

def readFile(lines):
    fp = os.popen("hexdump -C a.out")
    i=0
    for eachLine in fp:
        i+=1
        lines.append(eachLine)
        if i==10:
            break

def printList(lines):
    for l in lines:
        print(l, end='')

def main():
    headNumber = "          00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n"
    delimitorLine = "          ================================================\n"
    lines=[headNumber, delimitorLine]
    readFile(lines)
    print(headNumber)
    print(delimitorLine)
#    printList(lines)

    win = TextViewWindow(lines)
    win.connect("delete-event", Gtk.main_quit)
    win.show_all()
    Gtk.main()

class TextViewWindow(Gtk.Window):

    def __init__(self, lines):
        Gtk.Window.__init__(self, title="TextView Example")

        self.set_default_size(1000, 350)
        self.grid = Gtk.Grid()
        self.add(self.grid)
        self.lines = lines
        self.create_textview(lines)

    def create_textview(self, lines):
        scrolledwindow = Gtk.ScrolledWindow()
        scrolledwindow.set_hexpand(True)
        scrolledwindow.set_vexpand(True)
        self.grid.attach(scrolledwindow, 0, 1, 3, 1)

        self.textview = Gtk.TextView()

#        fontDesc = Pango.FontDescription("monospace 10")
#        self.textview.modify_font(fontDesc)
        self.textbuffer = self.textview.get_buffer()
        text_content = '<span foreground="blue" size="x-large">Blue text</span> is <i>cool</i>!\n'
        for l in lines:
            text_content = text_content + l

        self.textbuffer.set_text(text_content)
        scrolledwindow.add(self.textview)
 
#        for l in lines:
#            self.textbuffer.set_text(l)

main()

