#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>

int main(int argc, char *argv[]) {
    mqd_t mqd;
    mqd=mq_open("/server_queue",O_WRONLY);
    if(mqd==(mqd_t)-1) {
        printf("Error in opening server's message queue\n");
        return 0;
    }
    if(mq_send(mqd,argv[1],strlen(argv[1]),0)==-1) {
        mq_close(mqd);
        printf("Error in sending message\n");
    }
    mq_close(mqd);
    return 0;
}