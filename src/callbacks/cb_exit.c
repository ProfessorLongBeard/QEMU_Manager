#include <qmgr.h>







void cb_exit(GtkWidget *widget, gpointer data) {
    if (mgr) {
        if (mgr->builder) {
            g_object_unref(mgr->builder);
        }

        if (mgr->widgets) {
            g_hash_table_destroy(mgr->widgets);
        }

        g_free(mgr);
    }

    gtk_main_quit();
}