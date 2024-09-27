#ifndef QMGR_LIB_H
#define QMGR_LIB_H

#include <stdint.h>
#include <gtk/gtk.h>
#include <json-c/json.h>




typedef struct {
    GError              *err;
    GtkBuilder          *builder;
    GHashTable          *widgets;

    GtkCssProvider      *css_provider;
    GdkDisplay          *display;
    GdkScreen           *screen;

    struct json_object  *vm_config;
} qmgr_t;


extern qmgr_t *mgr;








gint qmgr_init(qmgr_t **mgr);
void qmgr_cleanup(qmgr_t *mgr);

#endif