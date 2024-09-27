#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <gtk/gtk.h>







gint notebook_get_max_pages(void);
gint notebook_get_current_page(void);
GtkWidget *notebook_get_page(gint page_num);
GList *notebook_get_page_children(GtkWidget *page);
GtkWidget *notebook_get_widget_from_page(gint page_num, const gchar *widget_name);

#endif