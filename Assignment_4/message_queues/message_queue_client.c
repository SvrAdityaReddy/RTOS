#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>

#define SERVER_MQ_NAME "/server_queue" // server message queue name
#define CLIENT_MQ_NAME "/client1_queue" // client message queue name
#define CLIENT_NAME "client1" // client name
#define MAX_MESSAGES 10 // maximum no. of messages in message queue
#define MAX_MSG_SIZE 256 // maximum size of each message in message queue

int main(int argc, char *argv[]) {
    mqd_t mqd,smqd;
    struct mq_attr attr;
    char *buffer,*message,*temp;
    // to control number of arguments passed to program
    if(argc!=2) {
        printf("Usage: %s simple_expression(like 1+2)\n",argv[0]);
        exit(0);
    }
    attr.mq_flags = 0; 
    attr.mq_maxmsg = MAX_MESSAGES; 
    attr.mq_msgsize = MAX_MSG_SIZE; 
    attr.mq_curmsgs = 0;
    // to remove the entry of client's message queue in /dev/mqueue/ directory
    mq_unlink(CLIENT_MQ_NAME);
    // creation and opening of client's message queue
    mqd=mq_open(CLIENT_MQ_NAME,O_CREAT|O_RDWR, 0664,&attr); // mqd is client's message queue descriptor
    // opening of server's message queue
    smqd=mq_open(SERVER_MQ_NAME,O_WRONLY); // smqd is server's message queue descriptor
    if(mqd==(mqd_t)-1) {
        printf("Error in creating client's message queue\n");
        return 0;
    }
    if(smqd==(mqd_t)-1) {
        printf("Error in opening server's message queue\n");
        return 0;
    }
    /*
    construction of message to be sent to server which is of format
    clientid a+b
    */
    message=(char *)malloc(sizeof(char)*(strlen(CLIENT_NAME)+strlen(argv[1])+1));
    temp=(char *)malloc(sizeof(char)*(strlen(CLIENT_NAME)+2));
    strncat(temp,CLIENT_NAME,strlen(CLIENT_NAME));
    strncat(temp," \0",2);
    strncat(message,temp,strlen(temp));
    strncat(message,argv[1],strlen(argv[1]));
    if(mq_send(smqd,message,strlen(message),0)==-1) {
        mq_close(smqd);
        mq_unlink(CLIENT_MQ_NAME);
        printf("Error in sending message\n");
    }
    // reading message from client's message queue i.e reading server's response written to client's message queue
    buffer=malloc(sizeof(char)*attr.mq_msgsize); 
    // reading message from client's message queue
    if(mq_receive(mqd,buffer, attr.mq_msgsize, NULL)==-1) {
        printf("Error in receiving message from server\n");
        free(buffer);
        free(message);
        free(temp);
        mq_close(mqd);
        mq_close(smqd);
        // to remove the entry of client's message queue in /dev/mqueue/ directory
        mq_unlink(CLIENT_MQ_NAME);
        return 0;
    }
    printf("Response from server evaluation of Expression %s is %s\n",argv[1],buffer);
    free(buffer);
    free(message);
    free(temp);
    mq_close(mqd);
    mq_close(smqd);
    // to remove the entry of client's message queue in /dev/mqueue/ directory
    mq_unlink(CLIENT_MQ_NAME);
    return 0;
}