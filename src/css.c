#include <qmgr.h>
#include <sys/stat.h>
#include <sys/types.h>










gint css_load_from_file(const gchar *css_file) {
    gint ret = 0;
    struct stat st;


    if (stat(css_file, &st) < 0) {
        g_print("Failed to stat() %s!\n", css_file);
        return -1;
    }

    mgr->css_provider = gtk_css_provider_new();

    if (!mgr->css_provider) {
        g_print("Failed to initialize CSS provider!\n");
        return -1;
    }

    ret = gtk_css_provider_load_from_path(mgr->css_provider, css_file, &mgr->err);

    if (ret < 0) {
        g_print("Failed to load CSS file %s!\n", css_file);

        g_object_unref(mgr->css_provider);
        return ret;
    }

    mgr->display = gdk_display_get_default();

    if (!mgr->display) {
        g_print("Failed to get default GDK display!\n");
        g_object_unref(mgr->css_provider);
        return -1;
    }

    mgr->screen = gdk_display_get_default_screen(mgr->display);

    if (!mgr->screen) {
        g_print("Failed to get GDK screen from default display!\n");
    
        g_object_unref(mgr->css_provider);
        return -1;
    }

    gtk_style_context_add_provider_for_screen(mgr->screen, GTK_STYLE_PROVIDER(mgr->css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    return 0;
}