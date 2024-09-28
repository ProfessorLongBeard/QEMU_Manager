#include <qmgr.h>







void cb_uefi_mode(GtkWidget *check_box, gpointer data) {
    struct json_object *uefi_config_array = NULL, *uefi_config = NULL, *uefi_enabled = NULL;
    struct json_object *rom_config_array = NULL, *rom_config = NULL;





    if (!check_box) {
        return;
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_box)) == true) {
        // Enable UEFI widget entry and button 
        widget_set_active(widget_get_widget_by_name("qemu_uefi_bios_entry"), true);
        widget_set_active(widget_get_widget_by_name("qemu_open_fd_btn"), true);
        
        json_object_object_get_ex(mgr->vm_config, "QEMU_UEFI_CONFIG", &uefi_config_array);

        if (!uefi_config_array) {
            uefi_config_array = json_object_new_array();
            uefi_config = json_object_new_object();

            json_object_object_add(uefi_config, "UEFI_ENABLED", json_object_new_string("true"));
            json_object_object_add(uefi_config, "UEFI_FW", json_object_new_string("None"));

            json_object_array_add(uefi_config_array, uefi_config);
            json_object_object_add(mgr->vm_config, "QEMU_UEFI_CONFIG", uefi_config_array);

        }

        uefi_config = json_object_array_get_idx(uefi_config_array, 0);
        json_object_object_add(uefi_config, "UEFI_ENABLED", json_object_new_string("true"));

        // Disable ROM widget entry and button
        widget_set_active(widget_get_widget_by_name("qemu_rom_bios_entry"), false);
        widget_set_active(widget_get_widget_by_name("qemu_open_rom_btn"), false);

        json_object_object_get_ex(mgr->vm_config, "QEMU_ROM_CONFIG", &rom_config_array);

        if (!rom_config_array) {
            rom_config_array = json_object_new_array();
            rom_config = json_object_new_object();

            json_object_object_add(rom_config, "ROM_ENABLED", json_object_new_string("false"));
            json_object_object_add(rom_config, "ROM_FW", json_object_new_string("None"));

            json_object_array_add(rom_config_array, rom_config);
            json_object_object_add(mgr->vm_config, "QEMU_ROM_CONFIG", rom_config_array);
        }

        rom_config = json_object_array_get_idx(rom_config_array, 0);
        json_object_object_add(rom_config, "ROM_ENABLED", json_object_new_string("false"));

    } else {
        // Disable UEFI widget entry and button
        widget_set_active(widget_get_widget_by_name("qemu_uefi_bios_entry"), false);
        widget_set_active(widget_get_widget_by_name("qemu_open_fd_btn"), false);

        json_object_object_get_ex(mgr->vm_config, "QEMU_UEFI_CONFIG", &uefi_config_array);

        if (!uefi_config_array) {
            uefi_config_array = json_object_new_array();
            uefi_config = json_object_new_object();

            json_object_object_add(uefi_config, "UEFI_ENABLED", json_object_new_string("false"));
            json_object_object_add(uefi_config, "UEFI_FW", json_object_new_string("None"));

            json_object_array_add(uefi_config_array, uefi_config);
            json_object_object_add(mgr->vm_config, "QEMU_UEFI_CONFIG", uefi_config_array);
        }

        uefi_config = json_object_array_get_idx(uefi_config_array, 0);
        json_object_object_add(uefi_config, "UEFI_ENABLED", json_object_new_string("false"));

        // Enable ROM widget entry and button
        widget_set_active(widget_get_widget_by_name("qemu_rom_bios_entry"), true);
        widget_set_active(widget_get_widget_by_name("qemu_open_rom_btn"), true);

        json_object_object_get_ex(mgr->vm_config, "QEMU_ROM_CONFIG", &rom_config_array);

        if (!rom_config_array) {
            rom_config_array = json_object_new_array();
            rom_config = json_object_new_object();

            json_object_object_add(rom_config, "ROM_ENABLED", json_object_new_string("true"));
            json_object_object_add(rom_config, "ROM_FW", json_object_new_string("None"));

            json_object_array_add(rom_config_array, rom_config);
            json_object_object_add(mgr->vm_config, "QEMU_ROM_CONFIG", rom_config_array);
        }

        rom_config = json_object_array_get_idx(rom_config_array, 0);
        json_object_object_add(rom_config, "ROM_ENABLED", json_object_new_string("true"));
    }
}