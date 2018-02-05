#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fd[2];
    pipe(fd);
    pid_t child_pid;
    child_pid=fork();
    if(child_pid==-1) {
        printf("Error in forking a child process");
    }
    else {
        // for child process
        if(child_pid==0) {
            // closing stdout file descriptor
            if(close(1)==-1) {
                printf("Error in closing standard output file descriptor");
                return 0;
            }
            // duplicating fd[1] i.e write end of pipe as stdout
            dup(fd[1]);
            // closing fd[0] read end of file
            if(close(fd[0])==-1) {
                printf("Error in closing read file descriptor");
                return 0;
            }
            execlp("ls","ls","-1",NULL);
        }
        // for parent process
        else {
            int status;
            // close the stdin file descriptor
            if(close(0)==-1) {
                printf("Error in closing standard input file descriptor");
                return 0;
            }
            // duplicating fd[0] i.e read end of pipe as stdin
            dup(fd[0]);
            // closing fd[1] write end of pipe
            if(close(fd[1])==-1) {
                printf("Error in closing write file descriptor");
                return 0;
            }
            execlp("grep","grep",argv[1],NULL);
        }
    }
    return 0;
}
