#include <qmgr.h>







gint msgbox_info(const gchar *msg, ...) {
    gint ret = 0;
    va_list args;
    gchar *msg_tmp = NULL;
    GtkWidget *msg_info = NULL, *content = NULL, *label = NULL;






    if (!msg) {
        return -1;
    }

    msg_tmp = g_malloc(strlen(msg) + 1024);

    if (!msg_tmp) {
        g_print("Failed to allocate info message buffer!\n");
        return -1;
    }

    va_start(args, msg);
    ret = g_vsnprintf(msg_tmp, strlen(msg) + 1024, msg, args);
    va_end(args);

    msg_info = gtk_message_dialog_new(GTK_WINDOW(widget_get_widget_by_name("main_win")),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        NULL);

    gtk_window_set_title(GTK_WINDOW(msg_info), "Information");
    gtk_window_set_deletable(GTK_WINDOW(msg_info), false);
    gtk_window_set_default_size(GTK_WINDOW(msg_info), 500, 100);

    content = gtk_message_dialog_get_message_area(GTK_MESSAGE_DIALOG(msg_info));

    if (!content) {
        g_print("Failed to get info message box content!\n");

        g_free((void *)msg_tmp);
        return -1;
    }

    label = gtk_label_new(msg_tmp);

    if (!label) {
        g_print("Failed to create new info message box label!\n");

        g_free((void *)msg_tmp);
        return -1;
    }

    gtk_label_set_line_wrap(GTK_LABEL(label), true);
    gtk_label_set_xalign(GTK_LABEL(label), 0);

    gtk_widget_set_vexpand(label, true);
    gtk_widget_set_hexpand(label, true);

    gtk_container_add(GTK_CONTAINER(content), label);
    gtk_widget_show_all(msg_info);

    gtk_dialog_run(GTK_DIALOG(msg_info));

    widget_destroy(msg_info);
    g_free((void *)msg_tmp);
    return ret;
}

gint msgbox_err(const gchar *msg, ...) {
    gint ret = 0;
    va_list args;
    gchar *msg_tmp = NULL;
    GtkWidget *msg_err = NULL, *content = NULL, *label = NULL;





    if (!msg) {
        return -1;
    }

    msg_tmp = g_malloc(strlen(msg) + 1024);

    if (!msg_tmp) {
        g_print("Failed to allocate err message buffer!\n");
        return -1;
    }

    va_start(args, msg);
    ret = g_vsnprintf(msg_tmp, strlen(msg) + 1024, msg, args);
    va_end(args);

    msg_err = gtk_message_dialog_new(GTK_WINDOW(widget_get_widget_by_name("main_win")),
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK,
        "%s", msg_tmp);

    gtk_window_set_title(GTK_WINDOW(msg_err), "Error");
    gtk_window_set_deletable(GTK_WINDOW(msg_err), false);
    gtk_window_set_default_size(GTK_WINDOW(msg_err), 500, 100);

    content = gtk_message_dialog_get_message_area(GTK_MESSAGE_DIALOG(msg_err));

    if (!content) {
        g_print("Failed to get err message box content!\n");

        g_free((void *)msg_tmp);
        return -1;
    }

    label = gtk_label_new(msg_tmp);

    if (!label) {
        g_print("Failed to create new err message box label!\n");

        g_free((void *)msg_tmp);
        return -1;
    }

    gtk_label_set_line_wrap(GTK_LABEL(label), true);
    gtk_label_set_xalign(GTK_LABEL(label), 0);

    gtk_widget_set_vexpand(label, true);
    gtk_widget_set_hexpand(label, true);

    gtk_container_add(GTK_CONTAINER(content), label);
    gtk_widget_show_all(msg_err);

    gtk_dialog_run(GTK_DIALOG(msg_err));

    widget_destroy(msg_err);
    g_free((void *)msg_tmp);
    return ret;
}