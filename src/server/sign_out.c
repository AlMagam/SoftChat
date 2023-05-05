#include "server.h"

char *mx_sign_out(void *jobj, t_comm *connect) {
    json_object *j_id = NULL;
    int id = -1;

    json_object_object_get_ex(jobj, "id", &j_id);

    if (j_id && json_object_get_type(j_id) == json_type_int)
        id = json_object_get_int(j_id);
    else
        return mx_bad_request(NULL, NULL);

    if (mx_validate_token(connect->db, id, (json_object *)jobj))
        return mx_json_string_code_type(401, S_OUT);

    mx_remove_socket(connect->db, connect->fd, id);
    mx_pop_from_ssl_list(connect->ssl_list, connect->fd);

    return mx_json_string_code_type(200, S_OUT);
}
