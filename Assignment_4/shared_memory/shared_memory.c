#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define SHM_NAME "/sh_mem"

int main(int argc, char *argv[]) {
    pid_t child_pid;
    int fd;
    void *addr;
    int status;
    size_t length;
    fd=shm_open(SHM_NAME,O_CREAT|O_RDWR,0664);
    if(fd==-1) {
        printf("Error in open shared memory descriptor");
        return 0;
    }
    length=(size_t)strlen(argv[1]);
    if(ftruncate(fd,length)==-1) {
        printf("Error in trucating shared memory size\n");
        close(fd);
        shm_unlink(SHM_NAME);
        return 0;
    }
    addr=mmap(NULL,length,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(addr==MAP_FAILED) {
        printf("Error in creating memory mapped region");
        close(fd);
        shm_unlink(SHM_NAME);
        return 0;
    }
    memcpy(addr,argv[1],length);
    child_pid=fork();
    if(child_pid==-1) {
        printf("Error in creating child process\n");
        return 0;
    }
    else {
        // for child process
        if(child_pid==0) {
            struct stat sb;
            fd=shm_open(SHM_NAME,O_RDONLY,0);
            fstat(fd,&sb);
            addr=mmap(NULL,sb.st_size,PROT_READ,MAP_SHARED,fd,0);
            if(addr==MAP_FAILED) {
                printf("Error in creating memory mapped region\n");
                close(fd);
                shm_unlink(SHM_NAME);
                return 0;
            }
            printf("Child: Parent wrote: %s\n",(char*)addr);
            close(fd);
            shm_unlink(SHM_NAME);
        }
        // for parent process
        else {
            exit(status);
        }
    }
    return 0;
}