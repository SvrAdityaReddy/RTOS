# PIPES (Inter Process Communnication Mechanism)

PIPES provide half duplex communication. <br>
The following api calls are used to use PIPE IPC mechanism to communicate between two processes. <br>

```{C}

int pipe(int pipefd[2]);
int close(int fd);

```

In this program, we are trying to pipe the output of one program to other. This is done in the following way. <br>

Let us assume that we are forking a child process to execute program on left side of the pipe. Now we change it's stdout file descriptor to write end of pipe (duplicate) and close read end of pipe. For parent process which has to read output of program on left side of pipe to execute the right end of pipe, it has to change it's stdin file descriptor to read end of pipe (duplicate) and close the write end of pipe. If we donot close write end of pipe, parent process waits for end of file since it tries to read until end of file. <br>

api used for duplication of file descriptors is as follow

```{C}

int dup(int oldfd);

```

# Reference

[1] [Man pages]() <br>
[2] [closing the unwanted file descriptors](https://unix.stackexchange.com/questions/132325/closing-the-unwanted-file-descriptors)
