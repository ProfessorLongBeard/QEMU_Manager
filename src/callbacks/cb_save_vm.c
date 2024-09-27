#include <qmgr.h>







void cb_save_vm(GtkWidget *btn, gpointer data) {
    gint ret = 0;
    GtkTreeIter iter;
    GtkTreeModel *model = NULL;
    GtkWidget *arch = NULL, *machine = NULL, *cpu = NULL, *cores = NULL;
    gint mem_size = 0;
    const gchar *mem_size_str = NULL;
    gint active_machine_idx = -1, active_core_idx = -1, active_arch_idx = -1, active_cpu_idx = -1;
    gint qemu_cores_count = 0;
    const gchar *qemu_arch = NULL, *qemu_machine = NULL, *qemu_cpu = NULL, *qemu_cores = NULL;
    GtkWidget *dialog = NULL;
    GtkFileChooser *chooser = NULL;
    const gchar *vm_config_path = NULL, *model_tmp = NULL;
    char tmp[1024];
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;











    if (!btn) {
        return;
    }

    model = gtk_combo_box_get_model(GTK_COMBO_BOX(widget_get_widget_by_name("qemu_arch_dropdown")));

    if (!model) {
        msgbox_err("Failed to get QEMU arch model!\n");
        return;
    }

    // Save QEMU selected arch
    gtk_combo_box_get_active_iter(GTK_COMBO_BOX(widget_get_widget_by_name("qemu_arch_dropdown")), &iter);
    gtk_tree_model_get(model, &iter, 0, &model_tmp, -1);
    json_object_object_add(mgr->vm_config, "QEMU_ARCH", json_object_new_string(model_tmp));

    model = gtk_combo_box_get_model(GTK_COMBO_BOX(widget_get_widget_by_name("qemu_machine_dropdown")));

    if (!model) {
        msgbox_err("Failed to get QEMU machine model!\n");
        return;
    }

    gtk_combo_box_get_active_iter(GTK_COMBO_BOX(widget_get_widget_by_name("qemu_machine_dropdown")), &iter);
    gtk_tree_model_get(model, &iter, 0, &model_tmp, -1);
    json_object_object_add(mgr->vm_config, "QEMU_MACHINE", json_object_new_string(model_tmp));

    model = gtk_combo_box_get_model(GTK_COMBO_BOX(widget_get_widget_by_name("qemu_cpu_dropdown")));

    if (!model) {
        msgbox_err("Failed to get QEMU cpu model!\n");
        return;
    }

    gtk_combo_box_get_active_iter(GTK_COMBO_BOX(widget_get_widget_by_name("qemu_cpu_dropdown")), &iter);
    gtk_tree_model_get(model, &iter, 0, &model_tmp, -1);
    json_object_object_add(mgr->vm_config, "QEMU_CPU", json_object_new_string(model_tmp));

    model = gtk_combo_box_get_model(GTK_COMBO_BOX(widget_get_widget_by_name("qemu_cpu_cores_dropdown")));

    if (!model) {
        msgbox_err("Failed to get QEMU cpu cores model!\n");
        return;
    }

    gtk_combo_box_get_active_iter(GTK_COMBO_BOX(widget_get_widget_by_name("qemu_cpu_cores_dropdown")), &iter);
    gtk_tree_model_get(model, &iter, 0, &model_tmp, -1);
    json_object_object_add(mgr->vm_config, "QEMU_CPU_SMP", json_object_new_int(strtol(model_tmp, NULL, 10)));

    mem_size_str = gtk_entry_get_text(GTK_ENTRY(widget_get_widget_by_name("qemu_memory_entry")));

    if (!mem_size_str) {
        msgbox_err("Failed to get QEMU memory size entry!\n");
        return;
    }

    mem_size = strtol(mem_size_str, NULL, 10);
    json_object_object_add(mgr->vm_config, "QEMU_MEMORY_SIZE", json_object_new_int(mem_size)); 

    dialog = gtk_file_chooser_dialog_new("Save VM config",
        GTK_WINDOW(widget_get_widget_by_name("main_win")),
            action,
            ("Cancel"),
            GTK_RESPONSE_CANCEL,
            ("Save"),
            GTK_RESPONSE_ACCEPT,
            NULL);

    if (!dialog) {
        msgbox_err("Failed to create QEMU save vm dialog!\n");
        return;
    }

    chooser = GTK_FILE_CHOOSER(dialog);

    if (!chooser) {
        msgbox_err("Failed to get QEMU save vm file chooser!\n");
        return;
    }

    gtk_file_chooser_set_current_name(chooser, "Untitled");

    ret = gtk_dialog_run(GTK_DIALOG(dialog));

    if (ret == GTK_RESPONSE_CANCEL || ret == GTK_RESPONSE_DELETE_EVENT || ret != GTK_RESPONSE_ACCEPT) {
        widget_destroy(dialog);
        return;
    }

    vm_config_path = gtk_file_chooser_get_filename(chooser);
    
    if (!vm_config_path) {
        msgbox_err("Failed to get VM config save path!\n");
        return;
    }

    widget_destroy(dialog);
    
    g_snprintf(tmp, sizeof(tmp), "%s.json", vm_config_path);
    gtk_entry_set_text(GTK_ENTRY(widget_get_widget_by_name("qemu_save_vm_entry")), tmp);

    json_object_to_file(tmp, mgr->vm_config);
    msgbox_info("Saved QEMU VM config!\n");
}