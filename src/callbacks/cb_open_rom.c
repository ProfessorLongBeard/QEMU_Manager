#include <qmgr.h>






void cb_open_rom(GtkWidget *btn, gpointer data) {
    gint ret = 0;
    const gchar *rom_file = NULL;
    GtkWidget *dialog = NULL;
    GtkFileChooser *chooser = NULL;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;





    if (!btn) {
        return;
    }

    dialog = gtk_file_chooser_dialog_new("Select ROM",
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

    rom_file = gtk_file_chooser_get_filename(chooser);

    if (!rom_file) {
        msgbox_err("Failed to get FD file path!\n");
        widget_destroy(dialog);
        return;
    }

    widget_destroy(dialog);
    gtk_entry_set_text(GTK_ENTRY(widget_get_widget_by_name("qemu_rom_bios_entry")), rom_file);
    g_free((void *)rom_file);
}