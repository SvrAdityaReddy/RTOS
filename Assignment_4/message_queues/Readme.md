# MESSAGE QUEUES (Inter Process Communication Mechanism)

In Linux, message queues are implemented in two ways namely System V, POSIX. Here we will be create POSIX message queues. The following api calls are used to use message queue to communicate between processes.

```{C}

// to open a message queue which is already existing
mqd_t mq_open(const char *name, int oflag);

// to create a new message queue
mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);

// to write a message to message queue
int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);

// to read a message from message queue
ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);

```

Here we had tried to build the client server architecture using message queues. Server will have it's message queue named "/server_queue". The clients will have their message queues as "/client1_queue", "/client2_queue" etc. The clients will send the basic mathematical expression to be solved to server's message queue. The server will process the data from it's message queue and evaluates the mathematical expression and send it to the respective clients message queues. The client sends the message in the following format.

```{sh}

// client1 1+2
clientid expression 

``` 

The message sent by client in above format helps the server to decide from which client it had received and sends the response to respective client using the information "clientid" present in the message. <br>

The following is one of the assumptions made by server about client. <br>

The client's message queue is named as "/clientid_queue"

# Reference

[1] [The Linux Programming Interface by Michael Kerrisk](https://moodle2.units.it/pluginfile.php/115306/mod_resource/content/1/The%20Linux%20Programming%20Interface-Michael%20Kerrisk.pdf) <br>
[2] [How to split a string in C/C++, Python and Java?](https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/) <br>
[3] [C Library - <limits.h>](https://www.tutorialspoint.com/c_standard_library/limits_h.htm) <br>