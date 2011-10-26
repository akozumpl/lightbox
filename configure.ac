AC_PREREQ([2.63])
AC_INIT([lightbox], [0.1], [akozumpl@redhat.com])

AC_CONFIG_MACRO_DIR([/usr/share/aclocal])
AM_INIT_AUTOMAKE([-Wno-portability])

PKG_CHECK_MODULES([GTK], [gtk+-3.0 >= 3.2.0])
GOBJECT_INTROSPECTION_CHECK([1.30.0])

AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT
