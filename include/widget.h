#ifndef WIDGET_H
#define WIDGET_H

#include <gtk/gtk.h>





GtkWidget *widget_get_widget_by_name(const gchar *widget_name);
gboolean widget_get_active(GtkWidget *widget);
void widget_set_active(GtkWidget *widget, gboolean active);
void widget_destroy(GtkWidget *widget);

#endif