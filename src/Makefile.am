lib_LTLIBRARIES = liblb.la
liblb_la_CFLAGS = $(GTK_CFLAGS)

bin_PROGRAMS = lb

lb_CFLAGS = $(GTK_CFLAGS)
lb_LDADD = $(GTK_LIBS) liblb.la
lb_SOURCES = lb_test.c

MAINTAINERCLEANFILES = Makefile.in

# deal with introspection
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --identifier-prefix=lb --warn-all --include=Gtk-3.0
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION
introspection_sources = $(liblb_la_SOURCES) liblb.h

lb-1.0.gir: liblb.la
lb_1_0_gir_INCLUDES = GObject-2.0
lb_1_0_gir_CFLAGS = $(GTK_LIBS) $(GTK_CFLAGS)
lb_1_0_gir_LIBS = liblb.la gtk-3
lb_1_0_gir_FILES = $(introspection_sources)
INTROSPECTION_GIRS += lb-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES = $(gir_DATA) $(typelib_DATA)
endif
