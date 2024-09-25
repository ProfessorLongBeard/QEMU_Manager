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

    //css_load_from_file("config/gui_styles.css");
    builder_load_from_file("config/gui_config.glade");

    builder_load_widget("main_win");
    g_signal_connect(widget_get_widget_by_name("main_win"), "destroy", G_CALLBACK(cb_exit), NULL);

    builder_load_widget("main_fixed");

    gtk_widget_show_all(GTK_WIDGET(widget_get_widget_by_name("main_win")));
    gtk_main();
    return 0;
}