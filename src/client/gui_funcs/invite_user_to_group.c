#include "client.h"

static void search_user(GtkWidget *w, t_glade *g) {
    char *input = (char *)gtk_entry_get_text(GTK_ENTRY(g->e_user_search));
    char *request = NULL;

    mx_delete_childs(g->box10);

    if (input && strlen(input) > 0) {
        request = mx_json_string_search_user(g->token, g->uid, input, INV);

        SSL_write(g->ssl, request, strlen(request));

        mx_strdel(&request);
    }

    (void)w;
}

static void cancel_add_user(GtkWidget *w, t_glade *g) {
    gtk_entry_set_text(GTK_ENTRY(g->e_user_search), "");

    gtk_widget_hide(g->l_invite_user_error);
    gtk_widget_hide(g->l_invite_user_success);
    gtk_widget_hide(g->d_add_user);

    mx_delete_childs(g->box10);

    (void)w;
}

static void destroy_dialog(GtkWidget *w, t_glade *g) {
    (void)w;
    (void)g;

    return;
}

void mx_invite_user_to_group(GtkWidget *w, t_glade *g) {
    GtkWidget *parent = gtk_widget_get_parent(w);
    GList *childs = gtk_container_get_children(GTK_CONTAINER(parent));
    GtkWidget *l_uid = GTK_WIDGET(g_list_nth_data(childs, 0));
    char *request = mx_json_string_invite_user_to_group(g->token, g->uid,
        g->dgid, mx_atoi(gtk_label_get_text(GTK_LABEL(l_uid))));

    SSL_write(g->ssl, request, strlen(request));

    mx_strdel(&request);

    g_list_free(childs);
    childs = NULL;

    (void)g;
}

void mx_invite_user(GtkWidget *w, t_glade *g) {
    gtk_window_set_transient_for(GTK_WINDOW(g->d_add_user),
        GTK_WINDOW(g->window));
    gtk_window_set_position(GTK_WINDOW(g->d_add_user),
        GTK_WIN_POS_CENTER_ON_PARENT);

    g->b_add_user_cancel = mx_get_gtk_obj(g, "b_add_user_cancel");
    g->e_user_search = mx_get_gtk_obj(g, "e_user_search");
    g_signal_connect(g->b_add_user_cancel, "clicked",
        G_CALLBACK(cancel_add_user), g);
    g_signal_connect(g->d_add_user, "delete-event",
        G_CALLBACK(destroy_dialog), g);
    g_signal_connect(g->e_user_search, "changed",
        G_CALLBACK(search_user), g);
    mx_delete_childs(g->box10);
    gtk_entry_set_text(GTK_ENTRY(g->e_user_search), "");
    gtk_widget_show_all(g->d_add_user);

    gtk_widget_hide(g->l_invite_user_error);
    gtk_widget_hide(g->l_invite_user_success);
    (void)w;
}

