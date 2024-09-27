#include <qmgr.h>







gint msgbox_info(const gchar *msg, ...) {
    gint ret = 0;
    va_list args;
    gchar *msg_tmp = NULL;
    GtkWidget *msg_info = NULL;





    if (!msg) {
        return -1;
    }

    msg_tmp = g_malloc(strlen(msg) + 1);

    if (!msg_tmp) {
        g_print("Failed to allocate info message buffer!\n");
        return -1;
    }

    va_start(args, msg);
    ret = g_vsnprintf(msg_tmp, strlen(msg) + 1, msg, args);
    va_end(args);

    msg_info = gtk_message_dialog_new(GTK_WINDOW(widget_get_widget_by_name("main_win")),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "%s", msg_tmp);

    gtk_window_set_title(GTK_WINDOW(msg_info), "Information");
        gtk_window_set_deletable(GTK_WINDOW(msg_info), false);

    gtk_dialog_run(GTK_DIALOG(msg_info));

    widget_destroy(msg_info);
    g_free((void *)msg_tmp);
    return ret;
}

gint msgbox_err(const gchar *msg, ...) {
    gint ret = 0;
    va_list args;
    gchar *msg_tmp = NULL;
    GtkWidget *msg_err = NULL;





    if (!msg) {
        return -1;
    }

    msg_tmp = g_malloc(strlen(msg) + 1);

    if (!msg_tmp) {
        g_print("Failed to allocate info message buffer!\n");
        return -1;
    }

    va_start(args, msg);
    ret = g_vsnprintf(msg_tmp, strlen(msg) + 1, msg, args);
    va_end(args);

    msg_err = gtk_message_dialog_new(GTK_WINDOW(widget_get_widget_by_name("main_win")),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK,
        "%s", msg_tmp);

    gtk_window_set_title(GTK_WINDOW(msg_err), "Error");
    gtk_window_set_deletable(GTK_WINDOW(msg_err), false);

    gtk_dialog_run(GTK_DIALOG(msg_err));

    widget_destroy(msg_err);
    g_free((void *)msg_tmp);
    return ret;
}