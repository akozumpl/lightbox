/**
 * based on an example by Ray Strode <rstrode@redhat.com>
 */

#include <cairo.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>

GtkWidget *w, *box, *l, *b, *m;

static void
move_window_to_parent(GtkWidget *w, GtkWidget *p)
{
    GdkWindow *p_window, *w_window;
    int pwidth, pheight, width, height, px, py, x, y, nx, ny;

    p_window = gtk_widget_get_window (p);
    pwidth = gdk_window_get_width (p_window);
    pheight = gdk_window_get_height (p_window);
    gdk_window_get_position(p_window, &px, &py);

    w_window = gtk_widget_get_window (w);
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

static void
on_configure_event (GtkWidget *p,
                    GdkEventConfigure *e,
                    GtkWidget *w)
{
    move_window_to_parent(w, p);
}

static GtkWidget *
show_lightbox(GtkWidget *w)
{
    GtkWidget *lightbox;
    GdkWindow *w_window;
    GdkWindow *l_window;
    int width, height;
    cairo_t *cr;
    cairo_pattern_t *pattern;
    cairo_surface_t *surface;

    lightbox = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_transient_for(GTK_WINDOW (lightbox), GTK_WINDOW (w));
    gtk_window_set_decorated(GTK_WINDOW (lightbox), FALSE);
    gtk_window_set_position(GTK_WINDOW (lightbox), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_type_hint (GTK_WINDOW (lightbox), GDK_WINDOW_TYPE_HINT_SPLASHSCREEN);
    gtk_widget_set_app_paintable(lightbox, TRUE);

    w_window = gtk_widget_get_window (w);
    width = gdk_window_get_width(w_window);
    height = gdk_window_get_height(w_window);
    gtk_window_set_default_size(GTK_WINDOW (lightbox), width, height);
    g_signal_connect(w, "configure-event", G_CALLBACK (on_configure_event), lightbox);
    gtk_widget_realize(lightbox);
    l_window = gtk_widget_get_window (lightbox);
    gdk_window_set_background_pattern (l_window, NULL);
    gtk_widget_show(lightbox);
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

    return lightbox;
}

static void
show_message_dialog(GtkWidget *l)
{
    m = gtk_message_dialog_new(GTK_WINDOW (l), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Woo, subdialog");
    gtk_window_set_position(GTK_WINDOW (m), GTK_WIN_POS_CENTER_ON_PARENT);
    g_signal_connect(l, "configure-event", G_CALLBACK (on_configure_event), m);
    gtk_dialog_run(GTK_DIALOG (m));
    gtk_main_quit();
}

static void
on_clicked(GtkButton *b, GtkWidget *w)
{
    l = show_lightbox(w);
    show_message_dialog(l);
}

int
main (int argc, char **argv)
{
    gtk_init (&argc, &argv);

    w = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(w), 800, 600);
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(w), box);
    l = gtk_label_new("I'm the installer");
    gtk_box_pack_start(GTK_BOX(box), l, TRUE, FALSE, 0);

    b = gtk_button_new_with_label("Show dialog");
    g_signal_connect(b, "clicked", G_CALLBACK (on_clicked), w);
    gtk_box_pack_start(GTK_BOX(box), b, FALSE, FALSE, 0);

    gtk_widget_show_all(w);
    gtk_main();
    return 0;
}
