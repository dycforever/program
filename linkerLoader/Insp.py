#!/usr/bin/python3
'''
Created on 2 Sep 2013

@author: dyc
'''
import sys
import os
import subprocess
from gi.repository import Gtk, Pango


class PosTransfer:
    def __init__(self, textbuffer):
        self.textbuffer = textbuffer
        # leading address and two SPACE 
        self.ADDRLEN = 10
        # length of tailing |... BINARY CONTENTS ...|\n
        # 2 + 16 + 1 = 19
        self.CONTLEN = 19
        
        self.BYTES_PER_LINE = 16
        self.LINELEN = (self.ADDRLEN + self.CONTLEN + self.BYTES_PER_LINE * 3 + 2)
        self.HALF = 8
        
    def in_first_half(self, mod):
        return 1 if mod>self.HALF else 0
        
    def addr_to_off(self, addr):
        line_number = addr//self.BYTES_PER_LINE
        line_offset = self.ADDRLEN + addr%self.BYTES_PER_LINE*3 + self.in_first_half(addr%self.BYTES_PER_LINE)
        print("add[%d] at line[%d] offset[%d] ---> [%d]" % (addr, line_number, addr%self.BYTES_PER_LINE, line_number * self.LINELEN + line_offset))
        return (line_number * self.LINELEN + line_offset)
    
    def lower_bound (self, addr):
#        print("addr %d get lower bound %d" % (addr, (addr//self.BYTES_PER_LINE) * self.BYTES_PER_LINE) )
        return (addr//self.BYTES_PER_LINE) * self.BYTES_PER_LINE

    def upper_bound (self, addr):
#        print("addr %d get upper bound %d" % (addr, self.lower_bound(addr) + self.BYTES_PER_LINE - 1))
        return self.lower_bound(addr) + self.BYTES_PER_LINE - 1
    
    def in_same_line (self, addr_start, addr_end):
        return True if (addr_end//self.BYTES_PER_LINE == addr_start//self.BYTES_PER_LINE) else False
    
    def split_range(self, range_start, range_end):
        addr_range = []
        while range_start < range_end and self.in_same_line(range_start, range_end) == False :
            print("split line (%d %d)" %(range_start, range_end) )
            addr_range.append( (range_start, self.upper_bound(range_start)) )
            range_start = self.upper_bound(range_start) + 1
        addr_range.append( (range_start, range_end-1) )
        for a in addr_range:
            print("addr: %s" %(a.__str__()) )
        return addr_range
    
    def trans(self, range_start, range_end):
        addr_range = self.split_range(range_start, range_end)
        ret = []
        for r in addr_range :
            print("deal r %s of class %s" %(r.__str__(), r.__class__ ) )
            iter1 = self.textbuffer.get_start_iter().copy()
            iter2 = self.textbuffer.get_start_iter().copy()
            iter1.forward_chars( self.addr_to_off(r[0]))
            iter2.forward_chars( self.addr_to_off(r[1]) + 2)
            ret.append( (iter1, iter2) )
        return ret
            
        
        

    
    
    

class InspectorMainWin(Gtk.Window):
    def __init__(self, filename):
        Gtk.Window.__init__(self, title="Inspector")
#        self.set_default_geometry(400, 400);
        self.set_default_size(1000, 400)
        self.set_position(Gtk.WindowPosition.CENTER)
        
        self.textview = Gtk.TextView()
        cmd = "hexdump -C "+ filename + " | cut -c 11- | cut -d' ' -f1-18"
        cmd = "hexdump -C "+ filename 
        fileContent = subprocess.check_output(cmd, shell=True)
        self.textbuffer = self.textview.get_buffer()
        self.textbuffer.set_text(fileContent.decode("ascii"))
        
        self.grid = Gtk.Grid()
        self.add(self.grid)
        scrolledwindow = Gtk.ScrolledWindow()
        scrolledwindow.set_hexpand(True)
        scrolledwindow.set_vexpand(True)
        self.grid.attach(scrolledwindow, 0, 1, width=3, height=1)
        scrolledwindow.add(self.textview)
        
        button1 = Gtk.Button(label="Button 1")
        button2 = Gtk.Button(label="Button 2")
        button3 = Gtk.Button(label="Button 3")
        
        grid=self.grid
        #直接add貌似是右对齐的        grid.add(button1)
#        attach的单位很奇怪，不是像素点
        grid.attach(button2, 0, 0, 2, 1)


        cmd = "readelf -h "+ filename + " | head -2"
        headContent = subprocess.check_output(cmd, shell=True)
        label = Gtk.Label(headContent.decode("ascii"))
        grid.attach_next_to(label, scrolledwindow, Gtk.PositionType.RIGHT, 1, 2)
        
        head_tag = self.textbuffer.create_tag("elf head", foreground = "red")
        iter_start = self.textbuffer.get_start_iter()

        self.transfer = PosTransfer(self.textbuffer)
        iters = self.transfer.trans(34, 156)
        
        for it in iters:
            print("apply tag %s" %(it.__str__()))
            self.textbuffer.apply_tag(head_tag, it[0], it[1])
        
if __name__ == '__main__':
    if (len(sys.argv)<2):
        filename = "a.out"
    else:
        filename = sys.argv[1]
    win = InspectorMainWin(filename)
    win.connect("delete-event", Gtk.main_quit)
    win.show_all()
    Gtk.main()
