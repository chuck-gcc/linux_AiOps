#include "../include/bash_agent.h"

int main(void)
{
    

    char *ll = process_message("hello world connard","/home/cc/gpu_lab/log_agent");

    printf("%s\n",ll);
    

    return(0);
}