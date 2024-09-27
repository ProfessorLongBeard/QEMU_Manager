#include <qmgr.h>









void cb_hdd_create(GtkWidget *btn, gpointer data) {
    gint ret = 0;
    GtkWidget *disk_format = NULL;
    gint active_format_idx = 0;
    const gchar *disk_type = NULL, *disk_size_str = NULL;
    guint disk_size = 0;
    GtkTreeIter iter;
    GtkTreeModel *model = NULL;
    GtkWidget *dialog = NULL;
    GtkFileChooser *chooser = NULL;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gchar tmp[1024];
    const gchar *disk_path = NULL;







    if (!btn) {
        return;
    }

    active_format_idx = gtk_combo_box_get_active(GTK_COMBO_BOX(widget_get_widget_by_name("qemu_hdd_format_dropdown")));

    if (active_format_idx < 0) {
        msgbox_info("Invalid HDD format dropdown index %d!\n", active_format_idx);
        return;
    }

    model = gtk_combo_box_get_model(GTK_COMBO_BOX(widget_get_widget_by_name("qemu_hdd_format_dropdown")));

    if (!model) {
        msgbox_info("Failed to get HDD format dropdown model!\n");
        return;
    }

    if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(widget_get_widget_by_name("qemu_hdd_format_dropdown")), &iter)) {
        gtk_tree_model_get(model, &iter, 0, &disk_type, -1);

        if (!disk_type) {
            msgbox_err("Failed to get disk format type!\n");
            return;
        }
    }

    disk_size_str = gtk_entry_get_text(GTK_ENTRY(widget_get_widget_by_name("qemu_hdd_size_entry")));

    if (!disk_size_str) {
        msgbox_err("Failed to get HDD size entry!\n");
        return;
    }

    disk_size = strtoull(disk_size_str, NULL, 10);

    dialog = gtk_file_chooser_dialog_new("Save HDD",
        GTK_WINDOW(widget_get_widget_by_name("main_win")),
        action,
        ("Cancel"),
        GTK_RESPONSE_CANCEL,
        ("Save"),
        GTK_RESPONSE_ACCEPT,
        NULL);

    chooser = GTK_FILE_CHOOSER(dialog);

    if (!chooser) {
        msgbox_err("Failed to get HDD save file chooser!\n");
        widget_destroy(dialog);
        return;
    }

    gtk_file_chooser_set_current_name(chooser, "Untitled");

    ret = gtk_dialog_run(GTK_DIALOG(dialog));

    if (ret == GTK_RESPONSE_CANCEL || ret == GTK_RESPONSE_DELETE_EVENT || ret != GTK_RESPONSE_ACCEPT) {
        widget_destroy(dialog);
        return;
    }

    disk_path = gtk_file_chooser_get_filename(chooser);
    widget_destroy(dialog);

    g_snprintf(tmp, sizeof(tmp), "%s.%s", disk_path, disk_type);
    gtk_entry_set_text(GTK_ENTRY(widget_get_widget_by_name("qemu_hdd_path_entry")), tmp);

    struct json_object *hdd_cfg_array = json_object_new_array();
    struct json_object *hdd_cfg = json_object_new_object();

    if (!hdd_cfg || !hdd_cfg_array) {
        msgbox_err("Failed to create QEMU HDD JSON config!\n");
        return;
    }

    json_object_object_add(hdd_cfg, "HDD_SIZE", json_object_new_int(disk_size));
    json_object_object_add(hdd_cfg, "HDD_PATH", json_object_new_string(disk_path));

    json_object_array_add(hdd_cfg_array, hdd_cfg);
    json_object_object_add(mgr->vm_config, "QEMU_HDD_CONFIG", hdd_cfg_array);
}