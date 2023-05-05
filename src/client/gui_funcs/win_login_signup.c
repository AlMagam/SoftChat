#include "client.h"

static void entry_visibility(GtkButton *b, t_glade *g) {
    (void)b;

    if (gtk_entry_get_visibility(GTK_ENTRY(g->r_epass)) &&
        gtk_entry_get_visibility(GTK_ENTRY(g->r_repass))) {
        gtk_entry_set_visibility(GTK_ENTRY(g->r_epass), false);
        gtk_entry_set_visibility(GTK_ENTRY(g->r_repass), false);
    }

    else {
        gtk_entry_set_visibility(GTK_ENTRY(g->r_epass), true);
        gtk_entry_set_visibility(GTK_ENTRY(g->r_repass), true);
    }
}

void mx_open_logwin(GtkWidget *sender, t_glade *g) {
    (void)sender;

    mx_clear_signup_inputs(g);

    gtk_label_set_text(GTK_LABEL(g->l_login_error), "");
    gtk_widget_hide(g->l_login_error);

    gtk_widget_hide(g->w_reg);
    gtk_widget_hide(g->w_chat);

    gtk_widget_show_all(g->w_log);
}

void mx_open_regwin(GtkWidget *sender, t_glade *g) {
    (void)sender;

    mx_clear_login_inputs(g);

    gtk_label_set_text(GTK_LABEL(g->l_signup_error), "");
    gtk_widget_hide(g->l_signup_error);

    gtk_widget_hide(g->w_log);
    gtk_widget_hide(g->w_chat);

    gtk_widget_show_all(g->w_reg);
}

void mx_create_win_reg(t_glade *g) {
    g->w_reg = mx_get_gtk_obj(g, "w_signup");
    g->b_reg_login = mx_get_gtk_obj(g, "b_reg_login");
    g->r_ename = mx_get_gtk_obj(g, "reg_elogin");
    g->r_epass = mx_get_gtk_obj(g, "reg_epass");
    g->r_repass = mx_get_gtk_obj(g, "reg_erepeat");
    g->b_reg_login = mx_get_gtk_obj(g, "b_reg_login");
    g->b_reg_back = mx_get_gtk_obj(g, "b_reg_back");
    g->b_reye = mx_get_gtk_obj(g, "b_reye");
    g->l_signup_error = mx_get_gtk_obj(g, "l_signup_error");

    g_signal_connect(g->b_reg_back, "clicked", G_CALLBACK(mx_open_logwin), g);
    g_signal_connect(g->b_reg_login, "clicked", G_CALLBACK(mx_b_reg_log), g);
    g_signal_connect(g->b_reye, "clicked", G_CALLBACK(entry_visibility), g);
}

void mx_create_win_log(t_glade *g) {
    g->window = mx_get_gtk_obj(g, "win_chat");
    g->w_log = mx_get_gtk_obj(g, "w_login");
    g->e_name = mx_get_gtk_obj(g, "name_entry");
    g->e_pass = mx_get_gtk_obj(g, "pass_entry");
    g->b_log_in = mx_get_gtk_obj(g, "b_login");
    g->b_reg = mx_get_gtk_obj(g, "b_reg");
    g->b_eye = mx_get_gtk_obj(g, "b_eye");
    g->l_login_error = mx_get_gtk_obj(g, "l_login_error");

    g_signal_connect(g->window, "destroy", G_CALLBACK(mx_gtk_quit), g);
    g_signal_connect(g->b_reg, "clicked", G_CALLBACK(mx_open_regwin), g);
    g_signal_connect(g->b_log_in, "clicked", G_CALLBACK(mx_b_log), g);
    g_signal_connect(g->b_eye, "clicked",
                     G_CALLBACK(mx_entry_visibility), g->e_pass);
}
