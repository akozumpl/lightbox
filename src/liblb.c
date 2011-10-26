/**
 * based on an example by Ray Strode <rstrode@redhat.com>
 */

#include <cairo.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>

#include "liblb.h"

/**
 * mylib_get_constant1:
 *
 * Return value: (transfer full): a constant, free when you used it
 */
gchar *
lb_mylib_get_constant1 (void)
{
   return g_strdup("a constant");
}

static void lb_move_window_to_parent(GtkWidget *parent,
                                  GdkEventConfigure *e,
                                  GtkWindow *window)
{
    GdkWindow *p_window, *w_window;
    int pwidth, pheight, width, height, px, py, x, y, nx, ny;

    p_window = gtk_widget_get_window (parent);
    pwidth = gdk_window_get_width (p_window);
    pheight = gdk_window_get_height (p_window);
    gdk_window_get_position(p_window, &px, &py);

    w_window = gtk_widget_get_window (window);
    width = gdk_window_get_width (w_window);
    height = gdk_window_get_height (w_window);
    gdk_window_get_position(w_window, &x, &y);

    nx = px + pwidth / 2 - width / 2; ny = py + pheight / 2 - height / 2;

    if (x != nx || y != ny)
    {
        gdk_window_move (w_window, nx, ny);
        gdk_window_restack(w_window, p_window, TRUE);
    }
}

/**
 * lb_show_over:
 *
 * @window: (in)
 *
 * Show lightbox over window.
 *
 * Returns: (transfero full)
 */
GtkWindow *lb_show_over(GtkWindow *window)
{
    GtkWindow *lightbox;
    GdkWindow *w_window;
    GdkWindow *l_window;
    int width, height;
    cairo_t *cr;
    cairo_pattern_t *pattern;
    cairo_surface_t *surface;

    lightbox = (GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL)));
    gtk_window_set_transient_for(lightbox, window);
    gtk_window_set_decorated(lightbox, FALSE);
    gtk_window_set_position(lightbox, GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_type_hint (lightbox, GDK_WINDOW_TYPE_HINT_SPLASHSCREEN);
    gtk_widget_set_app_paintable(GTK_WIDGET(lightbox), TRUE);

    w_window = gtk_widget_get_window (GTK_WIDGET(window));
    width = gdk_window_get_width(w_window);
    height = gdk_window_get_height(w_window);
    gtk_window_set_default_size(lightbox, width, height);
    gtk_widget_realize(GTK_WIDGET(lightbox));
    l_window = gtk_widget_get_window (GTK_WIDGET(lightbox));
    gdk_window_set_background_pattern (l_window, NULL);
    gtk_widget_show(GTK_WIDGET(lightbox));
    surface = gdk_window_create_similar_surface(l_window,
                                                CAIRO_CONTENT_COLOR_ALPHA,
                                                width, height);

    cr = cairo_create (surface);
    gdk_cairo_set_source_window(cr, w_window, 0, 0);
    cairo_paint(cr);
    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.5);
    cairo_paint(cr);
    cairo_destroy(cr);

    pattern = cairo_pattern_create_for_surface (surface);
    gdk_window_set_background_pattern(l_window, pattern);
    cairo_pattern_destroy (pattern);

    /* make the shade move with the parent window */
    g_signal_connect(window, "configure-event",
                     G_CALLBACK (lb_move_window_to_parent), lightbox);

    return lightbox;
}

void lb_destroy(GtkWindow *lightbox)
{
    gtk_widget_destroy(GTK_WIDGET(lightbox));
}
