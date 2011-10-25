#include <stdio.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include "xfsm-fadeout.h"

XfsmFadeout *show_fadeout(void)
{
    GdkDisplay *display = gdk_display_get_default();
    return xfsm_fadeout_new(display);
}

void hide_fadeout(XfsmFadeout *fadeout)
{
    xfsm_fadeout_destroy(fadeout);
}

int main (int argc, char **argv)
{
    XfsmFadeout *fadeout;
    GtkWidget *window;

    gtk_init(&argc, &argv);
    fadeout = show_fadeout();

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show(window);

    gtk_main();
    hide_fadeout(fadeout);
    return 0;
}
