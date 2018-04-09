#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>        
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>

#define PORT_NUM "5000"
#define BACKLOG 50 // maximum length of queue of pending connections may grow
#define ADDR_STR_LEN (NI_MAXHOST+NI_MAXSERV+10)
#define MAX_DATA_SIZE 50

int cfd;

void my_signal_handler(int sig_num) {
    char answer[2];
    if(sig_num==SIGINT) {
        printf("\nReceived SIGINT i.e ctrl+c\n");
        printf("Do you want to terminate the process (Y/N): ");
        scanf("%s",answer);
        if(strncmp(answer,"Y",1)==0) {
            close(cfd);
            exit(0);
        }
    }
}

void grim_reap(int sig) {
    while(waitpid(-1,NULL,WNOHANG)>0) {
        continue;
    }
}

int main(int argc, int *argv[]) {
    struct addrinfo hints;
    struct addrinfo *result,*rp;
    struct sockaddr_storage claddr;
    socklen_t addrlen;
    int lfd,optval;
    char host[NI_MAXHOST],service[NI_MAXSERV];
    char addr_str[ADDR_STR_LEN];
    ssize_t num_bytes;
    char message[MAX_DATA_SIZE];
    char buffer[MAX_DATA_SIZE];
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=SA_RESTART;
    sa.sa_handler=grim_reap;
    if(sigaction(SIGCHLD,&sa,NULL)==-1) {
        printf("Error in sigaction when trying to change action done on SIGCHLD\n");
        exit(0);
    }
    // installing signal handler to ignore SIGPIPE signal
    if(signal(SIGPIPE,SIG_IGN)==SIG_ERR) {
        printf("Error in ignoring the SIGPIPE signal\n");
        return 0;
    }
    // installing signal handler to handle SIGINT
    if(signal(SIGINT,my_signal_handler)==SIG_ERR) {
        printf("Error in handling the SIGINT signal\n");
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
            close(lfd);
            if(!fork()) {
                while((num_bytes=recv(cfd,buffer,MAX_DATA_SIZE-1,0))>0) {
                    buffer[num_bytes]='\0';
                    printf("Server: Message from %s: %s",host,buffer);      
                }
                exit(1);
            }
            else {
                while(fgets(message,MAX_DATA_SIZE,stdin)!=NULL) {
                    if(send(cfd,message,strlen(message),0)==-1) {
                        printf("Error in sending message to (%s, %s)\n",host,service);
                    }    
                }
                exit(1);
            }
            exit(1);
        }
    }
    return 0;
}