#CFLAGS=-Wall `pkg-config --cflags --libs gtk+-3.0 gdk-3.0`

CFLAGS=-Wall `pkg-config --cflags --libs gtk+-2.0 gdk-2.0`


all : lightbox


xfsm-fadeout.o : xfsm-fadeout.c

lightbox : lightbox.c xfsm-fadeout.o
