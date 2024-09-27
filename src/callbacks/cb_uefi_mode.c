#include <qmgr.h>






void cb_uefi_mode(GtkWidget *check_box, gpointer data) {
    if (!check_box) {
        return;
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_box)) == true) {
        // Enable UEFI widget entry and button 
        widget_set_active(widget_get_widget_by_name("qemu_uefi_bios_entry"), true);
        widget_set_active(widget_get_widget_by_name("qemu_open_fd_btn"), true);

        // Disable ROM widget entry and button
        widget_set_active(widget_get_widget_by_name("qemu_rom_bios_entry"), false);
        widget_set_active(widget_get_widget_by_name("qemu_open_rom_btn"), false);

    } else {
        // Disable UEFI widget entry and button
        widget_set_active(widget_get_widget_by_name("qemu_uefi_bios_entry"), false);
        widget_set_active(widget_get_widget_by_name("qemu_open_fd_btn"), false);

        // Enable ROM widget entry and button
        widget_set_active(widget_get_widget_by_name("qemu_rom_bios_entry"), true);
        widget_set_active(widget_get_widget_by_name("qemu_open_rom_btn"), true);
    }
}