#include "server.h"

int mx_delete_user_from_group(sqlite3 *db, int user_id, int group_id) {
    sqlite3_stmt *stmt = NULL;
    int rv = sqlite3_prepare_v2(db,
        "DELETE FROM GROUP_MEMBERS WHERE USER_ID = ?1"\
        " AND GROUP_ID = ?2", -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_int(stmt, 2, group_id);

    if (rv == SQLITE_ERROR)
        return -1;

    if ((rv = sqlite3_step(stmt)) != SQLITE_DONE)
        return -1;

    sqlite3_finalize(stmt);

    return 0;
}

int mx_change_admin_status(sqlite3 *db, int user_id, int group_id, bool adm) {
    sqlite3_stmt *stmt = NULL;
    int rv = 0;

    if (mx_check_group_member(db, user_id, group_id) < 0)
        return -2;
    rv = sqlite3_prepare_v2(db, "UPDATE GROUP_MEMBERS SET ADMIN = ?1 "\
        "WHERE USER_ID = ?2 AND GROUP_ID = ?3;", -1, &stmt, NULL);
    if (rv == SQLITE_ERROR)
        return -1;
    sqlite3_bind_int(stmt, 1, adm);
    sqlite3_bind_int(stmt, 2, user_id);
    sqlite3_bind_int(stmt, 3, group_id);

    if ((rv = sqlite3_step(stmt)) != SQLITE_DONE)
        return -1;

    sqlite3_finalize(stmt);
    return 0;
}

int mx_get_size_table(sqlite3 *db, char *table) {
    sqlite3_stmt *stmt;
    int size = 1;
    char *str = mx_strjoin("SELECT * FROM ", table);
    int rv;

    rv = sqlite3_prepare_v2(db, str, -1, &stmt, NULL);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        while (sqlite3_step(stmt) == SQLITE_ROW)
            size++;
    else
        size = -1;
    sqlite3_finalize(stmt);
    sqlite3_free(str);
    return size;
}

int mx_get_size_group_mem_by_group_id(sqlite3 *db, int group_id) {
    sqlite3_stmt *stmt;
    int size = 1;
    int rv = 0;

    rv = sqlite3_prepare_v2(db, "SELECT * FROM GROUP_MEMBERS \
        WHERE GROUP_ID = ?1", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, group_id);
    if (sqlite3_step(stmt) != SQLITE_DONE)
        while (sqlite3_step(stmt) == SQLITE_ROW)
            size++;
    else
        size = -1;
    sqlite3_finalize(stmt);
    return size;
}

int *mx_get_all_id_group_members(sqlite3 *db, int group_id) {
    sqlite3_stmt *stmt;
    int size = mx_get_size_group_mem_by_group_id(db, group_id);
    int *members = malloc((size + 1) * sizeof(int));
    int i = 0;

    if (size < 1) {
        members = realloc(members, (sizeof(int) * 1));
        members[i] = -1;
        return members;
    }
    sqlite3_prepare_v2(db, "SELECT * FROM GROUP_MEMBERS \
                       WHERE GROUP_ID = ?1", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, group_id);
    while(sqlite3_step(stmt) == SQLITE_ROW)
        members[i++] = sqlite3_column_int(stmt, 1);
    members[i] = -1;
    sqlite3_finalize(stmt);
    return members;
}
