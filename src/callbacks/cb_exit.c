#include <qmgr.h>







void cb_exit(GtkWidget *widget, gpointer data) {
    qmgr_cleanup(mgr);
    gtk_main_quit();
}