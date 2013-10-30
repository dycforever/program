#!/usr/bin/python
from gi.repository import Gtk, Pango
from gi.repository import Gdk

class SearchDialog(Gtk.Dialog):

    def __init__(self, parent):
        Gtk.Dialog.__init__(self, "Search", parent,
                Gtk.DialogFlags.MODAL, buttons=(
                    Gtk.STOCK_FIND, Gtk.ResponseType.OK,
                    Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL))

        box = self.get_content_area()

        label = Gtk.Label("Insert text you want to search for:")
        box.add(label)

        self.entry = Gtk.Entry()
        box.add(self.entry)

        self.show_all()

class TextViewWindow(Gtk.Window):

    def __init__(self):
        Gtk.Window.__init__(self, title="TextView Example")

        self.set_default_size(400, 350)

        self.grid = Gtk.Grid()
        self.add(self.grid)

        self.create_textview()

    def create_textview(self):
        scrolledwindow = Gtk.ScrolledWindow()
        scrolledwindow.set_hexpand(True)
        scrolledwindow.set_vexpand(True)
        self.grid.attach(scrolledwindow, 0, 1, 3, 1)

        self.textview = Gtk.TextView()
        self.textbuffer = self.textview.get_buffer()
        self.textbuffer.set_text("This is some text inside of a Gtk.TextView. "
                + "Select text and click one of the buttons 'bold', 'italic', "
                + "or 'underline' to modify the text accordingly.")
        scrolledwindow.add(self.textview)

        self.tag_found = self.textbuffer.create_tag("found",
                background="yellow")
#        event= Gdk.Event(Gdk.GDK_NOTHING)
        event= Gdk.Event(1)
        isHandle = self.tag_found.event(self.textbuffer, event, self.textbuffer.get_start_iter())
        print("handle: %d\n" % isHandle)




win = TextViewWindow()
win.connect("delete-event", Gtk.main_quit)
win.show_all()
Gtk.main()
