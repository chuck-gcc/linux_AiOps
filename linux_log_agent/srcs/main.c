#include "../include/bash_agent.h"

void signalHandler(int sig)
{
    
    printf("voici %d\n", sig);

    write(2,"0",1);
}

void clean_struct(t_log_file **files, int idx)
{
    int i;

    i = 0;
    while(i < idx)
    {
        close(*(files[i]->socket_fd));
        free(files[i]->socket_fd);
        close(files[i]->fd);
        free(files[i]);
        i++;
    }
}

int path_verification(char **argv)
{
    char **ptr;

    ptr = argv;
    if(!argv || !*argv)
        return(1);
    while (*ptr)
    {
        if(access(*ptr, F_OK))
        {
            perror("Le fichier n'existe pas\n");
            return(1);
        }
        ptr++;
    }
    return(0);
}


t_log_file **init_struct(int argc, char **argv)
{
    int i;
    int j;
    char *line;
    int tube[2];
    t_log_file **files;
    t_log_file *file;

    if(path_verification(argv)){printf("Path error\n"); return(NULL);}
    files = malloc(sizeof(t_log_file *) * argc);
    i = 0;
    while (argv[i])
    {
        file = malloc(sizeof(t_log_file));
        if(!file)
        {
            clean_struct(files, i);
            free(files);
            return(NULL);

        }
        file->fd = open(argv[i], O_RDONLY);
        if(file->fd < 0)
        {
            clean_struct(files, i);
            free(files);
            return(NULL);
        }
        file->path = ft_strdup(argv[i]);
        j = 0;
        while ((line = get_next_line(file->fd)) != NULL)
        {
            j++;
            free(line);
        }
        printf("voici l'index du fichier %d\n",j);
        file->idx = j;
        file->id = i+1;
        files[i] = file;
        
        i++;
    }
    files[i] = NULL;
    printf("voici %s\n", files[0]->path);

    return(files);
}


int main(int argc, char **argv) 
{
    
    int i;
    pthread_t threads[argc - 1];
    t_log_file **files;
    //char *path[3] = {"/var/log/kern.log", "/var/log/auth.log", NULL};
    
    files = init_struct(argc, &argv[1]);
    if(!files){printf("error init struct\n"); return(1);}
    if(start_thread(threads,files,argc - 1) < 0)
    {
        clean_struct(files, argc -1);
        return(1);
    }

    stop_thread(threads, files, argc - 1);
    clean_struct(files, argc);
    return 0;
}