#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <qmgr.h>









int main(int argc, char *argv[]) {
    int ret = 0;
    struct stat st;


    if (stat("config", &st) < 0) {
        printf("Config path not found!\n");
        return -1;
    }

    gtk_init(&argc, &argv);

    if (qmgr_init(&mgr) < 0) {
        printf("Failed to initialize qmgr!\n");
        return -1;
    }

    css_load_from_file("config/gui_styles.css");
    builder_load_from_file("config/gui_config.glade");

    builder_load_widget("main_win");
    g_signal_connect(widget_get_widget_by_name("main_win"), "destroy", G_CALLBACK(cb_exit), NULL);

    builder_load_widget("main_notebook");

    // General tab
    builder_load_widget("general_tab");
    builder_load_widget("general_tab_fixed");
    builder_load_widget("qemu_arch_dropdown");
    builder_load_widget("qemu_machine_dropdown");
    builder_load_widget("qemu_cpu_dropdown");
    builder_load_widget("qemu_cpu_cores_dropdown");
    builder_load_widget("qemu_save_vm_entry");
    builder_load_widget("qemu_memory_entry");

    builder_load_widget("qemu_save_vm_btn");
    g_signal_connect(GTK_WIDGET(widget_get_widget_by_name("qemu_save_vm_btn")), "clicked", G_CALLBACK(cb_save_vm), NULL);

    builder_load_widget("qemu_load_vm_btn");
    builder_load_widget("qemu_start_vm_btn");

    // HDD tab
    builder_load_widget("hdd_tab");
    builder_load_widget("hdd_tab_fixed");
    builder_load_widget("qemu_hdd_format_dropdown");
    builder_load_widget("qemu_hdd_size_entry");
    builder_load_widget("qemu_hdd_path_entry");

    builder_load_widget("qemu_create_hdd_btn");
    g_signal_connect(GTK_WIDGET(widget_get_widget_by_name("qemu_create_hdd_btn")), "clicked", G_CALLBACK(cb_hdd_create), NULL);

    // BIOS tab
    builder_load_widget("bios_tab");
    builder_load_widget("bios_tab_fixed");
    
    builder_load_widget("qemu_uefi_bios_entry");
    builder_load_widget("qemu_open_fd_btn");
    g_signal_connect(GTK_WIDGET(widget_get_widget_by_name("qemu_open_fd_btn")), "clicked", G_CALLBACK(cb_open_fd), NULL);

    builder_load_widget("qemu_rom_bios_entry");
    builder_load_widget("qemu_open_rom_btn");
    g_signal_connect(GTK_WIDGET(widget_get_widget_by_name("qemu_open_rom_btn")), "clicked", G_CALLBACK(cb_open_rom), NULL);

    builder_load_widget("qemu_uefi_bios_check");
    g_signal_connect(GTK_WIDGET(widget_get_widget_by_name("qemu_uefi_bios_check")), "toggled", G_CALLBACK(cb_uefi_mode), NULL);

    gtk_widget_show_all(GTK_WIDGET(widget_get_widget_by_name("main_win")));
    gtk_main();
    return 0;
}