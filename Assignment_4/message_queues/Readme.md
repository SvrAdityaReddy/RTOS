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

# Reference

[1] [The Linux Programming Interface](https://moodle2.units.it/pluginfile.php/115306/mod_resource/content/1/The%20Linux%20Programming%20Interface-Michael%20Kerrisk.pdf) <br>
[2] [How to split a string in C/C++, Python and Java?](https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/) <br>
[3] [C Library - <limits.h>](https://www.tutorialspoint.com/c_standard_library/limits_h.htm) <br>