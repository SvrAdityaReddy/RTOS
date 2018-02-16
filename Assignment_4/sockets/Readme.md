# SOCKETS (Inter Process Communication Mechanism)

Here we are using UNIX sockets to implement a one way chat application and two way chat application in C language. <br>

Here we had written two codes namely "server.c" and "client.c". Here, client sends messages to server and what ever client send's message to server, it is displayed in server's console including client name and port client is using  incase of one way chat application and incase of two way chat application additionally the server will also send message to client and message from server get's displayed on client's console. <br>

The following are the api's used in "server.c"

```{C}

int sigemptyset(sigset_t *set);
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
sighandler_t signal(int signum, sighandler_t handler);
pid_t waitpid(pid_t pid, int *status, int options);
void *memset(void *s, int c, size_t n);
int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
void freeaddrinfo(struct addrinfo *res);
int socket(int domain, int type, int protocol);
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, socklen_t hostlen, char *serv, socklen_t servlen, int flags);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
ssize_t send(int sockfd, const void *buf, size_t len, int flags);

``` 

The following are the api's used in "client.c"

```{C}

sighandler_t signal(int signum, sighandler_t handler);
void *memset(void *s, int c, size_t n);
int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
void freeaddrinfo(struct addrinfo *res);
int socket(int domain, int type, int protocol);
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
ssize_t send(int sockfd, const void *buf, size_t len, int flags);

```

Now, we will discuss some of the details of implementation of one way and two way chat applications. 

# References

[1] [Man pages]() <br>
[2] [The Linux Programming Interface by Michael Kerrisk](https://moodle2.units.it/pluginfile.php/115306/mod_resource/content/1/The%20Linux%20Programming%20Interface-Michael%20Kerrisk.pdf) <br>