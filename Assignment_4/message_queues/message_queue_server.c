#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>

#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256

int main(int argc, char *argv[]) {
    mqd_t mqd;
    struct mq_attr attr;
    char *buffer;
    attr.mq_flags = 0; 
    attr.mq_maxmsg = MAX_MESSAGES; 
    attr.mq_msgsize = MAX_MSG_SIZE; 
    attr.mq_curmsgs = 0;
    mq_unlink("/server_queue");
    mqd=mq_open("/server_queue",O_CREAT|O_RDWR, O_RDWR,&attr);
    if(mqd == (mqd_t) -1) {
        printf("Error in creating server's message queue\n");
        return 0;
    }
    buffer=malloc(sizeof(char)*attr.mq_msgsize);    
    while(1) {
        if(mq_receive(mqd,buffer, attr.mq_msgsize, NULL)==-1) {
            mq_unlink("/server_queue");
            free(buffer);
            printf("Error in receiving message\n");
            return 0;
        }
        // Expression evaluation
        printf("Data received from Client: %s\n",buffer);
    }
    free(buffer);
    mq_unlink("/server_queue");
    return 0;
}