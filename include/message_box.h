#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include <gtk/gtk.h>






gint msgbox_info(const gchar *msg, ...);
gint msgbox_err(const gchar *msg, ...);

#endif