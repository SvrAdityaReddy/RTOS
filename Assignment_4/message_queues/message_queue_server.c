#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>

#define SERVER_MQ_NAME "/server_queue"
#define MAX_MESSAGES 10 // maximum no. of messages in message queue
#define MAX_MSG_SIZE 256 // maximum size of each message in message queue

int evaluate(char *buffer) {
    int length_buffer=strlen(buffer);
    char *r = strndup(buffer,length_buffer);
    /*
    operator array
    '~' refers to invalid operator
    */
    char *delimiter[5]={"+","-","*","/","~"};
    int delimiter_position=0;
    int i,result;
    int values[2]={0,0};
    i=0;
    char *token = strtok(r, delimiter[delimiter_position]);
    while (token!=NULL) {
        if(strncmp(token,buffer,length_buffer)==0) {
            delimiter_position=delimiter_position+1;
            if(delimiter_position==4) {
                break;
            }
            token = strtok(r, delimiter[delimiter_position]);
        }
        else {
            values[i]=atoi(token);
            i=i+1;
            token = strtok(NULL, delimiter[delimiter_position]);
        }
    }
    if(strncmp(delimiter[delimiter_position],"+",1)==0) {
        result=values[0]+values[1];
    }
    else {
        if(strncmp(delimiter[delimiter_position],"-",1)==0) {
            result=values[0]-values[1];
        }
        else {
            if(strncmp(delimiter[delimiter_position],"*",1)==0) {
                result=values[0]*values[1];
            }
            else {
                if(strncmp(delimiter[delimiter_position],"/",1)==0) {
                    result=values[0]/values[1];
                }
                else {
                    // Invalid Operator                    
                    result=INT_MIN;
                }
            }
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    mqd_t mqd,cmqd;
    struct mq_attr attr;
    char *buffer,*client_name,*token,*client_q_name,*message;
    int result=0;
    attr.mq_flags = 0; 
    attr.mq_maxmsg = MAX_MESSAGES; 
    attr.mq_msgsize = MAX_MSG_SIZE; 
    attr.mq_curmsgs = 0;
    // to remove the entry of client's message queue in /dev/mqueue/ directory
    mq_unlink(SERVER_MQ_NAME);
    // creation and opening of server's message queue
    mqd=mq_open(SERVER_MQ_NAME,O_CREAT|O_RDWR, 0664,&attr); // mqd is server's message queue descriptor
    if(mqd == (mqd_t) -1) {
        printf("Error in creating server's message queue\n");
        return 0;
    }
    buffer=malloc(sizeof(char)*attr.mq_msgsize);    
    while(1) {
        // reading message from server's message queue
        if(mq_receive(mqd,buffer, attr.mq_msgsize, NULL)==-1) {
            mq_unlink(SERVER_MQ_NAME);
            free(buffer);
            printf("Error in receiving message\n");
            return 0;
        }
        // construction of client's message queue name
        client_name = strtok(buffer, " ");
        token=strtok(NULL, " ");
        printf("Data received from %s is %s\n",client_name,token);
        client_q_name=(char *)malloc(sizeof(char)*(sizeof(strlen(client_name)+8)));
        strncat(client_q_name,"/\0",2);
        strncat(client_q_name,client_name,strlen(client_name));
        strncat(client_q_name,"_queue",7);
        // opening of client's message queue
        cmqd=mq_open(client_q_name,O_WRONLY); // cmqd is client's message queue descriptor
        if(cmqd == (mqd_t) -1) {
            printf("Error in opening %s message queue\n",client_name);
            mq_unlink(SERVER_MQ_NAME);
            return 0;
        }
        // Simple expression evaluation
        result=evaluate(token);
        // check for invalid operator
        if(result==INT_MIN) {
            printf("Invalid Operator\n");
        }
        else {
            printf("%s Expression %s is evaluated to %d\n",client_name,token,result);
        }
        // conversion of result to string
        message=(char *)malloc(sizeof(char)*100);
        if(result==INT_MIN) {
            snprintf(message,100,"%s","Invalid operator is present");
        } 
        else {
            snprintf(message,100,"%d",result);
        }
        // writing message to client's message queue
        if(mq_send(cmqd,message,100,0)==-1) {
            mq_close(cmqd);
            printf("Error in sending message to %s\n",client_name);
        }
    }
    free(buffer);
    free(client_name);
    free(token);
    free(client_q_name);
    free(message);
    mq_close(cmqd);
    mq_close(mqd);
    // to remove the entry of server's message queue in /dev/mqueue/ directory
    mq_unlink(SERVER_MQ_NAME);
    return 0;
}