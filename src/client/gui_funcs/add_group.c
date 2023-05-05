#include "client.h"

static void cancel_add_group(GtkWidget *w, t_glade *g) {
    gtk_entry_set_text(GTK_ENTRY(g->e_new_group_name), "");
    gtk_label_set_text(GTK_LABEL(g->err_group_name_label), "");

    gtk_widget_hide(g->d_add_group);

    (void)w;
}

static void prepare_add_group(GtkWidget *w, t_glade *g) {
    char *name = (char *)gtk_entry_get_text(GTK_ENTRY(g->e_new_group_name));
    char *request = NULL;

    if (name && strlen(name) >= 1) {
        request = mx_json_string_new_group(g->token, g->uid, name);
        SSL_write(g->ssl, request, strlen(request));
        mx_strdel(&request);
        gtk_label_set_text(GTK_LABEL(g->err_group_name_label), "");
        gtk_widget_hide(g->err_group_name_label);
        cancel_add_group(w, g);
    }

    else {
        gtk_label_set_text(GTK_LABEL(g->err_group_name_label),
            "Name of the group must be at least\n1 character long." \
            "Make another name!");
        gtk_widget_show(g->err_group_name_label);
    }

    (void)w;
}

static void destroy_dialog(GtkWidget *w, t_glade *g) {
    (void)w;
    (void)g;

    return;
}

static void reset_grop_subwindow(t_glade *g) {
    gtk_widget_hide(g->b_group_members);
    gtk_widget_hide(g->b_add_user);
    gtk_widget_hide(g->b_leave_group);
    gtk_widget_hide(g->box9);

    g->dgid = MX_MISTERY;
    g->group = false;
}

void mx_add_group(GtkWidget *w, t_glade *g) {
    gtk_notebook_set_current_page(GTK_NOTEBOOK(g->gc_notebook), 1);
    gtk_window_set_transient_for(GTK_WINDOW(g->d_add_group),
        GTK_WINDOW(g->window));
    gtk_window_set_position(GTK_WINDOW(g->d_add_group),
        GTK_WIN_POS_CENTER_ON_PARENT);
    g->b_add_group_ok = mx_get_gtk_obj(g, "b_add_group_ok");
    g->b_add_group_cancel = mx_get_gtk_obj(g, "b_add_group_cancel");
    g->e_new_group_name = mx_get_gtk_obj(g, "e_new_group_name");
    g->err_group_name_label = mx_get_gtk_obj(g, "err_group_name_label");
    g_signal_connect(g->b_add_group_ok, "clicked",
        G_CALLBACK(prepare_add_group), g);
    g_signal_connect(g->b_add_group_cancel, "clicked",
        G_CALLBACK(cancel_add_group), g);
    g_signal_connect(g->d_add_group, "delete-event",
        G_CALLBACK(destroy_dialog), g);
    gtk_widget_show_all(g->d_add_group);

    reset_grop_subwindow(g);

    (void)w;
}
