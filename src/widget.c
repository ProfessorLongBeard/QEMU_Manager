#include <qmgr.h>












GtkWidget *widget_get_widget_by_name(const gchar *widget_name) {
    GtkWidget *widget = NULL;



    if (!widget_name) {
        return NULL;
    }

    widget = (GtkWidget *)g_hash_table_lookup(mgr->widgets, widget_name);

    if (!widget) {
        g_print("Failed to locate widget %s!\n", widget_name);
        return NULL;
    }

    return widget;
}

gboolean widget_get_active(GtkWidget *widget) {
    if (!widget) {
        return false;
    }

    if (gtk_widget_get_sensitive(widget) == true) {
        return true;
    }

    return false;
}

void widget_set_active(GtkWidget *widget, gboolean active) {
    if (!widget) {
        return;
    }

    gtk_widget_set_sensitive(widget, active);
}

void widget_destroy(GtkWidget *widget) {
    if (!widget) {
        return;
    }

    gtk_widget_destroy(widget);
}