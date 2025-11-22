#ifndef BASH_AGENT_H
#define BASH_AGENT_H

#define IP "127.0.0.1"
#define PORT 8000


#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/inotify.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <assert.h>
#include "libft.h"
#include "../get_next_line/get_next_line_bonus.h"

typedef struct s_log_file
{
    char *path;
    int *tube;
    int idx;
    int id;
    int fd;
    int *socket_fd;

} t_log_file;

void *monitor_directory(void *data);
void *monitor_file(void *d);
void print_event(struct inotify_event *event, void *d);
int stop_thread(pthread_t *threads, t_log_file **files, size_t size);
int start_thread(pthread_t *threads, t_log_file **files, size_t size);
int send_log(int *sock_fd, char *log);
int open_and_connect_socket_and_send(char *log);

char  *process_message(char *line, char *path);
#endif