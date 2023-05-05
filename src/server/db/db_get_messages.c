#include "server.h"

t_msg *mx_fill_msg(sqlite3_stmt *stmt) {
    t_msg *m = mx_memalloc(sizeof(t_msg));

    m->id = sqlite3_column_int(stmt, 0);
    m->group_id = sqlite3_column_int(stmt, 1);
    m->dialog_id = sqlite3_column_int(stmt, 2);
    m->sender = sqlite3_column_int(stmt, 3);
    if (sqlite3_column_text(stmt, 4) != NULL)
        m->msg = strdup((const char*)sqlite3_column_text(stmt, 4));
    m->time = sqlite3_column_int(stmt, 5);
    m->edited = sqlite3_column_int(stmt, 6);
    m->read = sqlite3_column_int(stmt, 7);
    if (sqlite3_column_text(stmt, 8) != NULL)
        m->file = strdup((const char*)sqlite3_column_text(stmt, 8));
    if (sqlite3_column_text(stmt, 9) != NULL)
        m->forwarded = strdup((const char*)sqlite3_column_text(stmt, 9));
    return m;
}

static t_msg *take_msg(sqlite3_stmt *stmt) {
    t_msg *m = NULL;
    int rv = 0;

    if ((rv = sqlite3_step(stmt)) != SQLITE_ROW) {
        if (rv == SQLITE_ERROR)
            return NULL;
        sqlite3_finalize(stmt);
        return NULL;
    }

    m = mx_fill_msg(stmt);

    sqlite3_finalize(stmt);

    return m;
}

t_msg *mx_get_msg_by_id(sqlite3 *db, int id) {
    sqlite3_stmt *stmt = NULL;
    int rv = sqlite3_prepare_v2(db, "SELECT * FROM MSG WHERE ID = ?1",
        -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);

    if (rv != SQLITE_OK)
        return NULL;

    return take_msg(stmt);
}

int mx_get_msg(sqlite3 *db, t_msg *m) {
    sqlite3_stmt *stmt = NULL;
    int id = -1;
    int rv = sqlite3_prepare_v2(db,
        "SELECT * FROM MSG WHERE SENDER = ?1 AND TIME = ?2", -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, m->sender);
    sqlite3_bind_int(stmt, 2, m->time);
    if (rv != SQLITE_OK)
        return -1;
    if ((rv = sqlite3_step(stmt)) != SQLITE_ROW)
        if (rv == SQLITE_ERROR)
            return -1;
    id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return id == 0 ? -1 : id;
}
