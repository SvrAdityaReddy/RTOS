#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>  
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>      
#include <sys/stat.h>        
#include <semaphore.h>

#define SEM_NAME "/sem_shm" // name of the semaphore
#define SHM_NAME "/sh_mem" // name of the shared memory portion

int main() {
    sem_t *sem;
    pid_t child_pid;
    int fd,length;
    void *addr;
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_NAME);
    sem=sem_open(SEM_NAME,O_CREAT,0664,1); // sem is the address of named semaphore
    if(sem==SEM_FAILED) {
        printf("Error in creating named semaphore\n");

    }
    fd=shm_open(SHM_NAME,O_CREAT|O_RDWR,0664); // fd is shared memory file descriptor
    if(fd==-1) {
        printf("Error in open shared memory descriptor");
        sem_close(sem);
        sem_unlink(SEM_NAME);
        return 0;
    }
    // size of shared memory block
    length=10;
    // to truncate file to a specified length
    if(ftruncate(fd,length)==-1) {
        printf("Error in truncating shared memory size\n");
        close(fd);
        sem_close(sem);
        sem_unlink(SEM_NAME);
        shm_unlink(SHM_NAME);
        return 0;
    }
    // to map file to memory
    addr=mmap(NULL,length,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(addr==MAP_FAILED) {
        printf("Error in creating memory mapped region");
        close(fd);
        sem_close(sem);
        sem_unlink(SEM_NAME);
        shm_unlink(SHM_NAME);
        return 0;
    }
    // to lock the semaphore
    sem_wait(sem);
    memcpy(addr,"hi",2);
    // to unlock the semaphore
    sem_post(sem);
    child_pid=fork();
    if(child_pid==-1) {
        printf("Error in creating child process\n");
        close(fd);
        sem_close(sem);
        sem_unlink(SEM_NAME);
        shm_unlink(SHM_NAME);
        return 0;
    }
    else {
        // for child process
        if(child_pid==0) {
            sem_wait(sem);
            struct stat sb;
            int i=0;
            fd=shm_open(SHM_NAME,O_RDONLY,0);
            // to determine the size of shared memory
            fstat(fd,&sb);
            addr=mmap(NULL,sb.st_size,PROT_READ,MAP_SHARED,fd,0);
            if(addr==MAP_FAILED) {
                printf("Error in creating memory mapped region\n");
                close(fd);
                shm_unlink(SHM_NAME);
                return 0;
            }
            printf("Child: Parent wrote: %s\n",(char*)addr);
            sem_post(sem);
            for(i=0;i<3;i++) {
                sleep(2);
                sem_wait(sem);
                printf("Child: Parent wrote: %s\n",(char*)addr);
                sem_post(sem);
            }
            close(fd);
            sem_close(sem);
            shm_unlink(SHM_NAME);
            sem_unlink(SEM_NAME);
            return 0;
        }
        // for parent process
        else {
            int i=0;
            char *message[3]={"child","you are","awesome"};
            for(i=0;i<3;i++) {
                sleep(2);
                sem_wait(sem);
                memcpy(addr,message[i],strlen(message[i]));
                sem_post(sem);
            }
            close(fd);
            sem_close(sem);
            shm_unlink(SHM_NAME);
            sem_unlink(SEM_NAME);
        }
    }
    return 0;
}