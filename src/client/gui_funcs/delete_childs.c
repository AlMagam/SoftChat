#include "client.h"

static void delete_child(void *child, void *data) {
    if (child)
        gtk_widget_destroy(GTK_WIDGET(child));

    (void)data;
}

void mx_delete_childs(GtkWidget *w) {
    GList *childs = NULL;

    if (w) {
        childs = gtk_container_get_children(GTK_CONTAINER(w));

        if (childs) {
            g_list_foreach(childs, (GFunc)delete_child, NULL);

            g_list_free(childs);
            childs = NULL;
        }
    }
}
