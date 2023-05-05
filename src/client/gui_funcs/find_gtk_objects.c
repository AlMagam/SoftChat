#include "client.h"

void mx_find_gtk_objects_1(t_glade *g) {
    g->w_chat = mx_get_gtk_obj(g, "w_chat");
    g->b_logout = mx_get_gtk_obj(g, "b_logout");
    g->b_send_msg = mx_get_gtk_obj(g, "b_send_msg");
    g->b_username = mx_get_gtk_obj(g, "b_username");
    g->common_area = mx_get_gtk_obj(g, "common_area");
    g->messages_area = mx_get_gtk_obj(g, "messages_area");
    g->profile_area = mx_get_gtk_obj(g, "profile_area");
    g->box_message = mx_get_gtk_obj(g, "box_message");
    g->b_close_profile = mx_get_gtk_obj(g, "b_close_profile");
    g->e_search = mx_get_gtk_obj(g, "e_search");
    g->e_message = mx_get_gtk_obj(g, "e_message");
    g->b_attach_file = mx_get_gtk_obj(g, "b_attach_file");
    g->l_select_chat = mx_get_gtk_obj(g, "l_select_chat");
    g->b_add_chat = mx_get_gtk_obj(g, "b_add_chat");
    g->b_add_group = mx_get_gtk_obj(g, "b_add_group");
    g->b_save_profile = mx_get_gtk_obj(g, "b_save_profile");
    g->d_add_chat = mx_get_gtk_obj(g, "d_add_chat");
    g->d_add_group = mx_get_gtk_obj(g, "d_add_group");
    g->gc_notebook = mx_get_gtk_obj(g, "gc_notebook");
    g->e_country = mx_get_gtk_obj(g, "e_country");
}

void mx_find_gtk_objects_2(t_glade *g) {
    g->e_birthday = mx_get_gtk_obj(g, "e_birthday");
    g->e_email = mx_get_gtk_obj(g, "e_email");
    g->e_profile_name = mx_get_gtk_obj(g, "e_profile_name");
    g->e_status = mx_get_gtk_obj(g, "e_status");
    g->l_chat_name = mx_get_gtk_obj(g, "l_chat_name");
    g->scrolledwindow1 = mx_get_gtk_obj(g, "scrolledwindow1");
    g->box9 = mx_get_gtk_obj(g, "box9");
    g->box8 = mx_get_gtk_obj(g, "box8");
    g->box10 = mx_get_gtk_obj(g, "box10");
    g->dialogs_box = mx_get_gtk_obj(g, "dialogs_box");
    g->groups_box = mx_get_gtk_obj(g, "groups_box");
    g->b_add_user = mx_get_gtk_obj(g, "b_add_user");
    g->d_add_user = mx_get_gtk_obj(g, "d_add_user");
    g->b_audio = mx_get_gtk_obj(g, "b_audio");
    g->l_invite_user_error = mx_get_gtk_obj(g, "l_invite_user_error");
    g->l_invite_user_success = mx_get_gtk_obj(g, "l_invite_user_success");
    g->b_leave_group = mx_get_gtk_obj(g, "b_leave_group");
    g->b_delete_account = mx_get_gtk_obj(g, "b_delete_account");
    g->b_change_theme = mx_get_gtk_obj(g, "b_change_theme");
    g->b_group_members = mx_get_gtk_obj(g, "b_show_group_members");
}

void mx_find_gtk_objects_3(t_glade *g) {
    g->d_show_group_members = mx_get_gtk_obj(g, "d_show_group_members");
    g->b_close_members = mx_get_gtk_obj(g, "b_close_members");
    g->box13 = mx_get_gtk_obj(g, "box13");
}
