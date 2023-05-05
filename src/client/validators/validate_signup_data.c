#include "client.h"

static bool check_password_strength(const char *password) {
    int n_upper = 0;
    int n_lower = 0;
    int n_digit = 0;
    int n_special = 0;

    for (size_t i = 0; i < strlen(password); ++i) {
        if (isupper(password[i]))
            ++n_upper;
        else if (islower(password[i]))
            ++n_lower;
        else if (isdigit(password[i]))
            ++n_digit;
        else if (ispunct(password[i]))
            ++n_special;
        else continue;
   }

   return n_upper && n_lower && n_digit && n_special && strlen(password) >= 8;
}

static int check_password_regex(t_glade *g, const char *password) {
    if (!check_password_strength(password)) {
        gtk_label_set_text(GTK_LABEL(g->l_signup_error),
            "Password does not match pattern!\n" \
            "Rules:\n" \
            "- password must be 8 or more characters long.\n" \
            "- password must contain at least one lowercase letter.\n" \
            "- password must contain at least one uppercase letter.\n" \
            "- password must contain at least one digit.\n" \
            "- password must contain at least one special character.\n");
        gtk_widget_show(g->l_signup_error);
        return -1;
    }

    return MX_SUCCESS;
}

int mx_validate_signup_data(t_glade *g, char *repeat) {
    char *username = g->log;
    char *password = g->pass;

    if ((!username || !password || !repeat)
         || (!strlen(username) || !strlen(password) || !strlen(repeat))) {
        gtk_label_set_text(GTK_LABEL(g->l_signup_error),
                           "One of the fields or both fields is empty\n" \
             "Fill the fields\nTry again!");
        gtk_widget_show(g->l_signup_error);
        return -1;
    }
    if (strcmp(password, repeat)) {
        gtk_label_set_text(GTK_LABEL(g->l_signup_error),
            "Password and repeat password must be the same\n" \
            "Try again!");
        gtk_widget_show(g->l_signup_error);
        return -1;
    }

    return check_password_regex(g, password);
}
