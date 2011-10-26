CFLAGS_GTK2=-Wall `pkg-config --cflags --libs gtk+-2.0 gdk-2.0`
CFLAGS=-Wall `pkg-config --cflags --libs gtk+-3.0 gdk-3.0`

all : lightbox lightbox2

xfsm-fadeout.o : xfsm-fadeout.c
	$(CC) $(CFLAGS_GTK2) $^ -c -o $@

lightbox : lightbox.c xfsm-fadeout.o
	$(CC) $(CFLAGS_GTK2) $^ -o $@

lightbox2 : lightbox2.c

clean:
	rm *.o
	rm lightbox
	rm lightbox2
