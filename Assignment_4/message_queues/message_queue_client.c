#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>

int main(int argc, char *argv[]) {
    mqd_t mqd;
    mqd=mq_open("server_queue",O_WRONLY);
    if(mqd == (mqd_t) -1) {
        printf("Error in creating server's message queue\n");
        return 0;
    }
    if(mq_send(mqd,argv[1],strlen(argv[1]),0)==-1) {
        printf("Error in sending message\n");
    }
    return 0;
}