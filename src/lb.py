#! /usr/bin/python

import glib
from gi.importer import DynamicImporter
from gi.repository import Gtk, Gdk

lb = DynamicImporter("lb").load_module(".lb")


main_loop = None


def cb_close(widget, data):
    main_loop.quit()

def cb_button(button, main_window):
    lightbox = lb.show_over(main_window)
    dialog = Gtk.MessageDialog(lightbox, Gtk.DialogFlags.MODAL,
                                Gtk.MessageType.INFO,
                                Gtk.ButtonsType.OK,
                                "Woo, subdialog")
    dialog.run()
    dialog.hide()
    lightbox.destroy()

if __name__ == "__main__":
    print "testing lb introspection: %s" % lb.get_test_value()

    main_window = Gtk.Window()
    main_window.set_default_size(800, 600)

    vbox = Gtk.VBox()
    main_window.add(vbox)
    vbox.pack_start(Gtk.Label("I'm the installer"), True, False , 0)

    button = Gtk.Button("Show dialog")
    vbox.pack_start(button, False, False, 0)
    button.connect("clicked", cb_button, main_window)

    main_window.connect("delete-event", cb_close)

    main_window.show_all()

    main_loop = glib.MainLoop()
    main_loop.run()
