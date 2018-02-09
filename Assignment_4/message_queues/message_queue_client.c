#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>

#define SERVER_MQ_NAME "/server_queue"
#define CLIENT_MQ_NAME "/client1_queue"
#define CLIENT_NAME "client1"
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256

int main(int argc, char *argv[]) {
    mqd_t mqd,smqd;
    struct mq_attr attr;
    char *buffer,*message,*temp;
    attr.mq_flags = 0; 
    attr.mq_maxmsg = MAX_MESSAGES; 
    attr.mq_msgsize = MAX_MSG_SIZE; 
    attr.mq_curmsgs = 0;
    mq_unlink(CLIENT_MQ_NAME);
    mqd=mq_open(CLIENT_MQ_NAME,O_CREAT|O_RDWR, 0664,&attr);
    smqd=mq_open(SERVER_MQ_NAME,O_WRONLY);
    if(mqd==(mqd_t)-1) {
        printf("Error in creating client's message queue\n");
        return 0;
    }
    if(smqd==(mqd_t)-1) {
        printf("Error in opening server's message queue\n");
        return 0;
    }
    message=(char *)malloc(sizeof(char)*(strlen(CLIENT_NAME)+strlen(argv[1])+1));
    temp=(char *)malloc(sizeof(char)*(strlen(CLIENT_NAME)+2));
    strncat(temp,CLIENT_NAME,strlen(CLIENT_NAME));
    strncat(temp," \0",2);
    // printf("%s\n",temp);
    strncat(message,temp,strlen(temp));
    // printf("%s\n",message);
    strncat(message,argv[1],strlen(argv[1]));
    // printf("%s\n",message);
    if(mq_send(smqd,message,strlen(message),0)==-1) {
        mq_close(smqd);
        mq_unlink(CLIENT_MQ_NAME);
        printf("Error in sending message\n");
    }
    buffer=malloc(sizeof(char)*attr.mq_msgsize);
    if(mq_receive(mqd,buffer, attr.mq_msgsize, NULL)==-1) {
        printf("Error in receiving message from server\n");
        free(buffer);
        free(message);
        free(temp);
        mq_close(mqd);
        mq_close(smqd);
        // mq_unlink(CLIENT_MQ_NAME);
        return 0;
    }
    printf("Response from server evaluation of Expression %s is %s\n",argv[1],buffer);
    free(buffer);
    free(message);
    free(temp);
    mq_close(mqd);
    mq_close(smqd);
    // mq_unlink(CLIENT_MQ_NAME);
    return 0;
}