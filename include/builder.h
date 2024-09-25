#ifndef BUILDER_H
#define BUILDER_H

#include <gtk/gtk.h>








gint builder_load_from_file(const gchar *glade_file);
gint builder_load_widget(const gchar *widget_name);

#endif