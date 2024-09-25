#include <qmgr.h>
#include <sys/stat.h>
#include <sys/types.h>








gint builder_load_from_file(const gchar *glade_file) {
    gint ret = 0;
    struct stat st;



    if (stat(glade_file, &st) < 0) {
        printf("Failed to stat() Glade file %s!\n", glade_file);
        return -1;
    }

    mgr->builder = gtk_builder_new();

    if (!mgr->builder) {
        printf("Failed to initialize GTK builder!\n");
        return -1;
    }

    ret = gtk_builder_add_from_file(mgr->builder, glade_file, NULL);

    if (ret != 1) {
        printf("Failed to load Glade file %s! (%s)\n", glade_file, mgr->err->message);

        g_free(mgr->err);
        g_object_unref(mgr->builder);
        return ret;
    }

    gtk_builder_connect_signals(mgr->builder, NULL);

    return 0;
}

gint builder_load_widget(const gchar *widget_name) {
    gint ret = 0;
    GtkWidget *widget = NULL;


    if (!widget_name) {
        return -1;
    }

    widget = GTK_WIDGET(gtk_builder_get_object(mgr->builder, widget_name));

    if (!widget) {
        g_print("Failed to get widget %s!\n", widget_name);
        return -1;
    }

    if (g_hash_table_insert(mgr->widgets, (gpointer *)widget_name, widget) == false) {
        g_print("Failed to load widget %s!\n", widget_name);
        return -1;
    }

    return 0;
}