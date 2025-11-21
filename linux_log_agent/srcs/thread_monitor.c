#include "../include/bash_agent.h"


#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ))


/*void *print_path(void *data)
{
    char *path;
    path = (char *)data;
    printf("thread for path %s\n", path);
    sleep(5);
    pthread_exit(NULL);
}
*/

int clean_thread(pthread_t *thread, int idx)
{
    int i;

    i = 0;
    while (i < idx)
    {
        pthread_exit(&thread[i]);
        i++;
    }
    return(i);
}


void *monitor_directory(void *data)
{
    int fd;
    char *path;
    char buffer[EVENT_BUF_LEN];
    struct inotify_event *event;

    path = (char *)data;
    fd = inotify_init();
    if(fd < 0) {perror("inotify error"); return(NULL);}
    int watch_d;
    memset(&event, 0 ,sizeof(struct inotify_event *));

    watch_d = inotify_add_watch(fd, path, IN_CREATE | IN_DELETE | IN_ATTRIB | IN_MOVED_TO | IN_MOVED_FROM | IN_MODIFY);
    if(watch_d < 0) {perror("inotify error"); return(NULL);}
    while (1)
    {
        int b = read(fd, buffer, EVENT_BUF_LEN);
        if(b <= 0){perror("read error"); return(NULL);}
        printf("read\n");
        if(b > 0)
        {
            event = (struct inotify_event *)buffer;
            print_event(event, data);
        }
    }

}

void *monitor_file(void *d)
{
    int fd;
    char *path;
    t_log_file *data;
    char buffer[EVENT_BUF_LEN];
    struct inotify_event *event;
    
    data = (t_log_file *)d;
    printf("START THREAD ID:%d\n", data->id);
    path = data->path;
    printf("voici file %s\n", path);
    fd = inotify_init();
    if(fd < 0) {perror("inotify error"); return(NULL);}
    int watch_d;
    memset(&event, 0 ,sizeof(struct inotify_event *));

    watch_d = inotify_add_watch(fd, path, IN_CREATE | IN_DELETE | IN_ATTRIB | IN_MOVED_TO | IN_MOVED_FROM | IN_MODIFY);
    if(watch_d < 0) {printf("%s ", path);perror("inotify error"); return(NULL);}
    while (1)
    {
        int b = read(fd, buffer, EVENT_BUF_LEN);
        if(b <= 0){perror("read error"); return(NULL);}
        printf("read\n");
        if(b > 0)
        {
            event = (struct inotify_event *)buffer;
            print_event(event, d);
        }
    }
}


int start_thread(pthread_t *threads, t_log_file **files, size_t size)
{

    size_t i;

    i = 0;
    if(!files || !*files)
        return(-1);
    memset(threads, 0, sizeof(pthread_t) * 2);
    while (i < size)
    {
        if(pthread_create(&threads[i], NULL, monitor_file, files[i]) < 0)
        {
            perror("%s\n");
            perror("Error thread creation");
            return(-1);
        }
        i++;
    }
    return(0);
}

int stop_thread(pthread_t *threads, t_log_file **files, size_t size)
{

    size_t i;

    i = 0;
    while (i < size)
    {
        pthread_join(threads[i],NULL);
        printf("Tread N°%d is back, nice\n", files[i]->id);
        i++;
    }
    return(0);
}