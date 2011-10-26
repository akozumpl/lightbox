#ifndef LBLIB_H
#define LBLIB_H

#include <gtk/gtk.h>

gchar * lb_mylib_get_constant1 (void);

GtkWindow *lb_show_over(GtkWindow *window);
void lb_destroy(GtkWindow *lb);

#endif
