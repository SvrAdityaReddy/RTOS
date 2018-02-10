# SHARED MEMORY (Inter Process Communication Mechanism)

In Linux, shared memory is implemented in two ways namely System V, POSIX. Here we will use POSIX shared memory. The following api calls are used to communicate between parent and child process.

```{C}

int shm_open(const char *name, int oflag, mode_t mode);
int shm_unlink(const char *name);
int ftruncate(int fd, off_t length);

```

When we are using above api calls we should link -lrt while compiling.

There might be inconsistency when data is read by child process and data is written by parent process in shared memory location. To counter this, we use semaphores. In linux there are two kind of semaphores namely System V, POSIX. Here we will use POSIX semaphores. The following api calls are used.

```{C}

sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
sem_t *sem_open(const char *name, int oflag);
int sem_close(sem_t *sem);
int sem_unlink(const char *name);

``` 

When we are using above api calls we should link -pthread while compiling. <br>

The code related to on how to use shared memory to communicate between parent and child process is [shared_memory.c](https://github.com/SvrAdityaReddy/RTOS/blob/master/Assignment_4/shared_memory/shared_memory.c). <br> 
The code related to on how to use shared memory to communicate between parent and child process with semaphores is [shared_memory_semaphore.c](https://github.com/SvrAdityaReddy/RTOS/blob/master/Assignment_4/shared_memory/shared_memory_semaphore.c).

# Reference

[1] [Man pages]() <br>
[2] [The Linux Programming Interface by Michael Kerrisk](https://moodle2.units.it/pluginfile.php/115306/mod_resource/content/1/The%20Linux%20Programming%20Interface-Michael%20Kerrisk.pdf) <br>