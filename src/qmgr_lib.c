#include <sys/stat.h>
#include <sys/types.h>
#include <qmgr.h>





qmgr_t *mgr = NULL;






gint qmgr_init(qmgr_t **mgr) {
    qmgr_t *m = NULL;


    m = g_malloc(sizeof(qmgr_t));

    if (!m) {
        return -1;
    }

    m->widgets = g_hash_table_new(g_str_hash, g_str_equal);

    if (!m->widgets) {
        g_free(m);
        return -1;
    }

    *mgr = m;
    return 0;
}

void qmgr_cleanup(qmgr_t *mgr) {
    if (mgr) {
        g_object_unref(mgr->builder);


        if (mgr->widgets) {
            g_hash_table_destroy(mgr->widgets);
        }

        g_free(mgr);
    }
}