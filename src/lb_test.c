#include <gtk/gtk.h>
#include "liblb.h"
#include <stdio.h>

static void cb_button(GtkButton *b, GtkWindow *main_window)
{
    GtkWidget *dialog;
    GtkWindow *lightbox = lb_show_over(main_window);
    dialog = gtk_message_dialog_new(GTK_WINDOW (lightbox), GTK_DIALOG_MODAL,
                                    GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                    "Woo, subdialog");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    lb_destroy(lightbox);
}

int main (int argc, char **argv)
{
    GtkWidget *main_window, *vbox, *button;
    gtk_init (&argc, &argv);

    main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(main_window), vbox);
    gtk_box_pack_start(GTK_BOX(vbox),
                       gtk_label_new("I'm the installer"), TRUE, FALSE, 0);

    button = gtk_button_new_with_label("Show dialog");
    g_signal_connect(button, "clicked", G_CALLBACK (cb_button), main_window);
    g_signal_connect(main_window, "delete-event",
                     G_CALLBACK(gtk_main_quit),  NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    gtk_widget_show_all(main_window);
    gtk_main();
    return 0;
}
