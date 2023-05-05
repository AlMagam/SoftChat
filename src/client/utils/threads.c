#include "client.h"

void mx_client_thread_manager(t_glade *glade, SSL *ssl) {
    pthread_t thread_id;
    t_thread_data *data = malloc(sizeof(t_thread_data));

    pthread_mutex_init(&glade->mutex, NULL);
    pthread_mutex_init(&glade->recorder_mutex, NULL);

    data->ssl = ssl;
    data->glade = glade;

    pthread_create(&thread_id, NULL, mx_listen_server, (void *)data);

    glade->listener = thread_id;
}
