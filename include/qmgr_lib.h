#ifndef QMGR_LIB_H
#define QMGR_LIB_H

#include <stdint.h>
#include <gtk/gtk.h>



typedef struct {
    GError          *err;
    GtkBuilder      *builder;
    GHashTable      *widgets;

    GtkCssProvider  *css_provider;
    GdkDisplay      *display;
    GdkScreen       *screen;
} qmgr_t;


extern qmgr_t *mgr;








gint qmgr_init(qmgr_t **mgr);
void qmgr_cleanup(qmgr_t *mgr);

#endif