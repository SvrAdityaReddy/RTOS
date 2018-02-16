#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>        
#include <sys/socket.h>
#include <netdb.h>

#define MAX_DATA_SIZE 50

int sfd;

void my_signal_handler(int sig_num) {
    char answer[2];
    if(sig_num==SIGINT) {
        printf("\nReceived SIGINT i.e ctrl+c\n");
        printf("Do you want to terminate the process (Y/N): ");
        scanf("%s",answer);
        if(strncmp(answer,"Y",1)==0) {
            close(sfd);
            exit(0);
        }
    }
}

int main(int argc, char *argv[]) {
    struct addrinfo hints;
    struct addrinfo *result,*rp;
    char message[MAX_DATA_SIZE];
    char buffer[MAX_DATA_SIZE];
    ssize_t num_bytes;
    // installing signal handler to handle SIGINT
    if(signal(SIGINT,my_signal_handler)==SIG_ERR) {
        printf("Error in handling the SIGINT signal\n");
        return 0;
    }
    // to fill the sizeof(struct addrinfo) bytes of memory area pointed by &hints by zero
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    if(getaddrinfo(argv[1],argv[2],&hints,&result)!=0) {
        printf("Error in getaddrinfo\n");
        return 0;
    }
    for(rp=result;rp!=NULL;rp=rp->ai_next) {
        sfd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        if(sfd==-1) {
            printf("Error in getting file descriptor to a socket");
            continue; // try next address
        }
        if(connect(sfd,rp->ai_addr,rp->ai_addrlen)==0) {
            break;
        }
        close(sfd); // try next address
    }
    if(rp==NULL) {
        printf("Could not connect to server\n");
        return 0;
    }
    freeaddrinfo(result);
    for(;;) {
        printf("Enter message to be sent to server: ");
        if(fgets(message,MAX_DATA_SIZE,stdin)==NULL) {
            printf("Error reading from stdin\n");
            continue;
        }
        if(send(sfd,message,strlen(message),0)==-1) {
            printf("Error in sending message to server\n");
        }
        else {
            if((num_bytes=recv(sfd,buffer,MAX_DATA_SIZE-1,0))>0) {
                buffer[num_bytes]='\0';
                printf("Client: Message from Server: %s",buffer);
            }
        }
    }
    return 0;
}