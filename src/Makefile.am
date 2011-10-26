lib_LTLIBRARIES = liblb.la
liblb_la_CFLAGS = $(GTK_CFLAGS)

bin_PROGRAMS = lb

lb_CFLAGS = $(GTK_CFLAGS)
lb_LDADD = $(GTK_LIBS) liblb.la
lb_SOURCES = lb_test.c

MAINTAINERCLEANFILES = Makefile.in
