#include "../include/bash_agent.h"


char  *process_message(char *line, char *path)
{
    int len_1;
    int len_2;
    char *msg;

    if(!line || !path)
        return(NULL);
    len_1 = ft_strlen(path);
    len_2 = ft_strlen(line);
    msg = malloc(sizeof(char *) * (len_1 + len_2 + 2));
    if(!msg)
        return(NULL);
    memcpy(msg, path, ft_strlen(path));

    msg[len_1] = 32;
    memcpy(&msg[len_1 + 1], line, ft_strlen(line));
    msg[len_1 + len_2 + 1] = '\0';

    assert(ft_strlen(msg) == (size_t)(len_1 + len_2 +1));
    return(msg);
}

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
        char *message = process_message(line, file->path);
        free(line);
        open_and_connect_socket_and_send(message);
        printf("[LOG]: %s\n", message);
        free(message);

    }
    if((event->mask & IN_ACCESS) == IN_ACCESS)
        printf("object %s execution dans le repertoire\n", event->name);
    if(((event->mask & IN_MOVED_FROM) == IN_MOVED_FROM) ||((event->mask & IN_MOVED_TO) == IN_MOVED_TO))
        printf("object %s deplacé du repertoire\n", event->name);
}