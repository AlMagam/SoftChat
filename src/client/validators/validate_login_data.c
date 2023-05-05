#include "client.h"

int mx_validate_login_data(t_glade *g) {
    char *username = g->log;
    char *password = g->pass;

    if ((!username || !password) || (!strlen(username) || !strlen(password))) {
        gtk_label_set_text(GTK_LABEL(g->l_login_error),
             "One of the fields or both fields is empty\n" \
             "Fill the fields\nTry again!");
        gtk_widget_show(g->l_login_error);
        return -1;
    }

    return MX_SUCCESS;
}
