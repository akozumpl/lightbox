#ifndef LBLIB_H
#define LBLIB_H

#include <gtk/gtk.h>

gchar * lb_get_test_value(void);

GtkWindow *lb_show_over(GtkWindow *window);
void lb_destroy(GtkWindow *lb);

#endif
