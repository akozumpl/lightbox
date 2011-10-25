CFLAGS=-Wall `pkg-config --cflags --libs gtk+-2.0 gdk-2.0`
CFLAGS_GTK3=-Wall `pkg-config --cflags --libs gtk+-3.0 gdk-3.0`



all : lightbox lightbox2


xfsm-fadeout.o : xfsm-fadeout.c

lightbox : lightbox.c xfsm-fadeout.o

lightbox2 : lightbox2.c
	$(CC) $(CFLAGS_GTK3) $^ -o $@
