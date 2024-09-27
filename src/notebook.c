#include <qmgr.h>




gint notebook_get_max_pages(void) {
    gint notebook_page_count = 0;


    notebook_page_count = gtk_notebook_get_n_pages(GTK_NOTEBOOK(widget_get_widget_by_name("main_notebook")));

    if (notebook_page_count < 0) {
        msgbox_err("Invalid max page count %d!\n", notebook_page_count);
        return -1;
    }

    return notebook_page_count;
}

gint notebook_get_current_page(void) {
    gint notebook_page_num = 0, notebook_max_pages = 0;


    notebook_max_pages = notebook_get_max_pages();

    if (notebook_max_pages < 0) {
        return -1;
    }

    notebook_page_num = gtk_notebook_get_current_page(GTK_NOTEBOOK(widget_get_widget_by_name("main_notebook")));

    if (notebook_page_num < 0 || notebook_page_num > notebook_max_pages) {
        msgbox_err("Invalid page %d!\n", notebook_page_num);
        return -1;
    }

    return notebook_page_num;
}

GtkWidget *notebook_get_page(gint page_num) {
    GtkWidget *page = NULL, *notebook_tmp = NULL;
    GtkNotebook *notebook = NULL;


    notebook_tmp = widget_get_widget_by_name("main_notebook");

    if (!notebook_tmp) {
        msgbox_err("Failed to get notebook widget!\n");
        return NULL;
    }

    if (GTK_IS_NOTEBOOK(notebook_tmp)) {
        notebook = GTK_NOTEBOOK(notebook_tmp);
    }

    page = gtk_notebook_get_nth_page(notebook, page_num);

    if (!page) {
        msgbox_err("Failed to get notebook page %d!\n", page_num);
        return NULL;
    }

    return page;
}

GList *notebook_get_page_children(GtkWidget *page) {
    GList *page_children_list = NULL;


    if (GTK_IS_CONTAINER(page) == false) {
        msgbox_err("Notebook page is not a container!\n");
        return NULL;
    }

    page_children_list = gtk_container_get_children(GTK_CONTAINER(page));

    if (!page_children_list) {
        msgbox_err("Failed to get notebook page children list!\n");
        return NULL;
    }

    return page_children_list;
}

GtkWidget *notebook_get_widget_from_page(gint page_num, const gchar *widget_name) {
    gint num_pages = 0;
    GList *page_widget_list = NULL;
    GtkWidget *page = NULL, *page_widget = NULL, *tmp_widget = NULL;

    
    if (!widget_name) {
        return NULL;
    }

    num_pages = notebook_get_max_pages();

    if (page_num < 0 || page_num > num_pages) {
        msgbox_err("Notebook page number %d invalid! (max page count %d)\n", page_num, num_pages);
        return NULL;
    }

    page = notebook_get_page(page_num);

    if (!page) {
        msgbox_err("Failed to get notebook page %d!\n", page_num);
        return NULL;
    }

    page_widget_list = notebook_get_page_children(page);

    if (!page_widget_list) {
        msgbox_err("Failed to get notebook page widget children!\n");
        return NULL;
    }

    tmp_widget = widget_get_widget_by_name(widget_name);

    if (!tmp_widget) {
        msgbox_err("Failed to get temp widget!\n");

        g_list_free(page_widget_list);
        return NULL;
    }

    for (GList *i = page_widget_list; i != NULL; i = i->next) {
        GtkWidget *widget = GTK_WIDGET(i->data);
        const gchar *name = gtk_widget_get_name(widget);

        if (g_strcmp0(name, widget_name) == 0) {
            page_widget = widget;
            break;
        }
    }

    if (!page_widget) {
        msgbox_err("Failed to get notebook widget %s!\n", widget_name);

        g_list_free(page_widget_list);
        return NULL;
    }

    g_list_free(page_widget_list);
    return page_widget;
}