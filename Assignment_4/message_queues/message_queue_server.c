#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>

struct mq_attr;

int main(int argc, char *argv[]) {
    mqd_t mqd;
    struct mq_attr attr;
    int priority;
    void *buffer;
    mqd=mq_open("/server_queue",O_CREAT |O_RDONLY ,O_RDWR);
    if(mqd == (mqd_t) -1) {
        printf("Error in creating server's message queue\n");
        return 0;
    }
    if(mq_getattr(mqd,&attr)==-1) {
        printf("Error in getting message queue attributes\n");
        return 0;
    }
    buffer=malloc(attr.mq_msgsize);
    if(mq_receive(mqd,buffer, attr.mq_msgsize, &priority)==-1) {
        printf("Error in receiving message\n");
        return 0;
    }
    // printf(buffer);
    return 0;
}