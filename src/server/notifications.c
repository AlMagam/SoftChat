#include "server.h"

void mx_notify_add_to_group(t_comm *connect, json_object *arr, int gid) {
    json_object *j_uid = NULL;
    char *gr_name = mx_get_group_name_by_id(connect->db, gid);
    char *response = mx_json_string_notify_gr(gid, gr_name, NOTIF_ADD_TO_GR);
    int uid = -1;

    for (size_t i = 0; i < json_object_array_length(arr); i++) {
        j_uid = json_object_array_get_idx(arr, i);
        uid = json_object_get_int(j_uid);
        mx_send_to_all_clients(connect, response, uid);
    }

    mx_strdel(&gr_name);

}

void mx_notify_group_renamed(t_comm *connect, int gid, char *name) {
    t_list *members = mx_get_all_group_members(connect->db, gid);
    t_list *clean_members = members;
    t_gr_members *member = NULL;
    char *response = mx_json_string_notify_gr(gid, name, NOTIF_GR_RENAMED);

    while (members) {
        member = members->data;
        mx_send_to_all_clients(connect, response, member->user_id);
        members = members->next;
    }

    while (clean_members) {
        member = clean_members->data;
        free(member);
        clean_members = clean_members->next;
    }
}
