#include <qmgr.h>






void cb_open_fd(GtkWidget *btn, gpointer data) {
    gint ret = 0;
    const gchar *fd_file = NULL;
    GtkWidget *dialog = NULL;
    GtkFileChooser *chooser = NULL;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;





    if (!btn) {
        return;
    }

    dialog = gtk_file_chooser_dialog_new("Select UEFI ROM",
        GTK_WINDOW(widget_get_widget_by_name("main_win")),
        action,
        ("Cancel"),
        GTK_RESPONSE_CANCEL,
        ("Select"),
        GTK_RESPONSE_ACCEPT,
        NULL);

    if (!dialog) {
        msgbox_err("Failed to intialize FileChooserDialog!\n");
        return;
    }

    ret = gtk_dialog_run(GTK_DIALOG(dialog));

    if (ret == GTK_RESPONSE_CANCEL || ret == GTK_RESPONSE_DELETE_EVENT || ret != GTK_RESPONSE_ACCEPT) {
        widget_destroy(dialog);
        return;
    }

    chooser = GTK_FILE_CHOOSER(dialog);

    if (!chooser) {
        msgbox_err("Failed to get FileChooser!\n");
        widget_destroy(dialog);
        return;
    }

    fd_file = gtk_file_chooser_get_filename(chooser);

    if (!fd_file) {
        msgbox_err("Failed to get FD file path!\n");
        widget_destroy(dialog);
        return;
    }

    widget_destroy(dialog);
    gtk_entry_set_text(GTK_ENTRY(widget_get_widget_by_name("qemu_uefi_bios_entry")), fd_file);

    struct json_object *uefi_config_array = json_object_new_array();
    struct json_object *uefi_config = json_object_new_object();

    if (!uefi_config || !uefi_config_array) {
        msgbox_err("Failed to create UEFI JSON config!\n");
        return;
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget_get_widget_by_name("qemu_uefi_bios_check"))) == true) {
        json_object_object_add(uefi_config, "UEFI_ENABLED", json_object_new_string("true"));
    } else {
        json_object_object_add(uefi_config, "UEFI_ENABLED", json_object_new_string("false"));
    }

    json_object_object_add(uefi_config, "UEFI_FW", json_object_new_string(fd_file));
 
    json_object_array_add(uefi_config_array, uefi_config);
    json_object_object_add(mgr->vm_config, "QEMU_UEFI_CONFIG", uefi_config_array);
}