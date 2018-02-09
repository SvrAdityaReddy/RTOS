#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>

#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256

int evaluate(char *buffer) {
    int length_buffer=strlen(buffer);
    char *r = strndup(buffer,length_buffer);
    char *tok = r;
    /*
    operator array
    '~' refers to invalid operator
    */
    char *delimiter[5]={"+","-","*","/","~"};
    char delimiter_position=0;
    int a,b,i,result;
    int values[2]={0,0};
    i=0;
    // while(tok != NULL) {
    //     strsep(&end, delimiter[delimiter_position]);
    //     printf("%s\n",tok);
    //     if(strncmp(tok,buffer,length_buffer)==0) {
    //         delimiter_position=delimiter_position+1;
    //         if(delimiter_position==5) {
    //             break;
    //         }
    //     }
    //     else {
    //         values[i]=atoi(tok);
    //         i=i+1;
    //     }
    //     tok = end;
    // }
    // printf("%d %d\n",values[0],values[1]);
    // printf("%d\n",delimiter_position);
    // free(r);
    char *token = strtok(r, delimiter[delimiter_position]);
   
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token!=NULL) {
        // printf("%s\n", token);
        if(strncmp(token,buffer,length_buffer)==0) {
            delimiter_position=delimiter_position+1;
            token = strtok(r, delimiter[delimiter_position]);
            if(delimiter_position==5) {
                break;
            }
        }
        else {
            values[i]=atoi(token);
            i=i+1;
            token = strtok(NULL, delimiter[delimiter_position]);
        }
    }
    // printf("%d\n",delimiter_position);
    if(delimiter[delimiter_position]=="+") {
        result=values[0]+values[1];
    }
    else {
        if(delimiter[delimiter_position]=="-") {
            result=values[0]-values[1];
        }
        else {
            if(delimiter[delimiter_position]=="*") {
                result=values[0]*values[1];
            }
            else {
                if(delimiter[delimiter_position]=="/") {
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
    mqd_t mqd;
    struct mq_attr attr;
    char *buffer;
    int i=0,result=0;
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
        printf("Data received from Client: %s\n",buffer);
        // Simple expression evaluation
        result=evaluate(buffer);
        if(result==INT_MIN) {
            printf("Invalid Operator\n");
        }
        else {
            printf("Expression %s is evaluated to %d\n",buffer,result);
        }
    }
    free(buffer);
    mq_unlink("/server_queue");
    return 0;
}