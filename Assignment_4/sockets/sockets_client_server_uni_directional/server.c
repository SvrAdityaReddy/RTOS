#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>        
#include <sys/socket.h>
#include <netdb.h>

#define PORT_NUM "5000"
#define BACKLOG 50 // maximum length of queue of pending connections may grow
#define ADDR_STR_LEN (NI_MAXHOST+NI_MAXSERV+10)
#define MAX_DATA_SIZE 50

int main() {
    struct addrinfo hints;
    struct addrinfo *result,*rp;
    struct sockaddr_storage claddr;
    socklen_t addrlen;
    int lfd,optval,cfd;
    char host[NI_MAXHOST],service[NI_MAXSERV];
    char addr_str[ADDR_STR_LEN];
    // installing signal handler to ignore SIGPIPE signal
    if(signal(SIGPIPE,SIG_IGN)==SIG_ERR) {
        printf("Error in ignoring the SIGPIPE signal\n");
        return 0;
    }
    // to fill the sizeof(struct addrinfo) bytes of memory area pointed by &hints by zero
    memset(&hints,0,sizeof(struct addrinfo));
    // intialize hints structure of type addrinfo
    hints.ai_canonname=NULL;
    hints.ai_next=NULL;
    hints.ai_addr=NULL;
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_flags=AI_PASSIVE;
    if(getaddrinfo(NULL,PORT_NUM,&hints,&result)!=0) {
        printf("Error in getaddrinfo\n");
        return 0;
    }
    optval=1;
    for(rp=result;rp!=NULL;rp=rp->ai_next) {
        lfd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        if(lfd==-1) {
            printf("Error in getting file descriptor to a socket");
            continue; // try next address
        }
        if(setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval))==-1) {
            printf("Error in setsockopt\n");
            return 0;
        }
        if(bind(lfd,rp->ai_addr,rp->ai_addrlen)==0) {
            break; // on success
        }
        close(lfd); // try next address
    }
    if(rp==NULL) {
        printf("Could not bind socket to any address\n");
        return 0;
    }
    if(listen(lfd,BACKLOG)==-1) {
        printf("Error in listen\n");
        return 0;
    }
    freeaddrinfo(result);
    // to handle client requests
    for(;;) {
        addrlen=sizeof(claddr);
        // printf("Waiting for Connections\n");
        cfd=accept(lfd,(struct sockaddr *)&claddr,&addrlen);
        if(cfd==-1) {
            printf("Error in acccepting client's request");
            continue;
        }
        if(getnameinfo((struct sockaddr *)&claddr,addrlen,host,NI_MAXHOST,service,NI_MAXSERV,0)==0) {
            snprintf(addr_str,ADDR_STR_LEN,"(%s, %s)",host,service);
        }
        printf("Connection from %s\n",addr_str);
        // forking a child process to handle each request
        if(!fork()) {
            ssize_t num_bytes;
            char buffer[MAX_DATA_SIZE];
            for(;;) {
                if((num_bytes=recv(cfd,buffer,MAX_DATA_SIZE-1,0))==-1) {
                    printf("Error in receiving messages from client\n");
                    exit(1);
                }
                buffer[num_bytes]='\0';
                printf("Server: Message from %s: %s",host,buffer);
            }
        }
    }
    return 0;
}