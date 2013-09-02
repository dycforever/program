#!/usr/bin/python
from gi.repository import Gtk, Pango

class InspectorMainWin(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Inspector")
#        self.set_default_geometry(400, 400);
        self.set_default_size(400, 400)
        self.set_position(Gtk.WindowPosition.CENTER)


win = InspectorMainWin()
win.connect("delete-event", Gtk.main_quit)
win.show_all()
Gtk.main()
