#include "../include/bash_agent.h"

void print_event(struct inotify_event *event, void *d)
{
    t_log_file *file;

    file = (t_log_file *)d;

    if((event->mask & IN_CREATE) == IN_CREATE)
        printf("nouvelle object %s créer dans le repertoire\n", event->name);
    if(((event->mask & IN_DELETE) == IN_DELETE) ||((event->mask & IN_DELETE_SELF) == IN_DELETE_SELF))
        printf("object %s supprimmer du repertoire\n", event->name);
    if((event->mask & IN_MODIFY) == IN_MODIFY)
    {
        file->idx++;
        printf("fichier %s modifier dans le repertoire, idx : %d\n", file->path, file->idx);
        char *line = get_next_line(file->fd);
        printf("[LOG]: %s\n", line);
        open_and_connect_socket_and_send(line);
        free(line);

    }
    if((event->mask & IN_ACCESS) == IN_ACCESS)
        printf("object %s execution dans le repertoire\n", event->name);
    if(((event->mask & IN_MOVED_FROM) == IN_MOVED_FROM) ||((event->mask & IN_MOVED_TO) == IN_MOVED_TO))
        printf("object %s deplacé du repertoire\n", event->name);
}