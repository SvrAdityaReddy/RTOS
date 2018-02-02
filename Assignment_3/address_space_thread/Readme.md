# Thread Address Space

The program will create three threads. Each thread modifies local variables, global variables.

# Observations

thread1 will call following function on creation

```{c}

void * thread1_proc() {
    int i=5, j=8, k=9;
    a=5;
    b=8;
    c=9;
    printf("Address of local variable: i is %p\n",&i);
    printf("Address of local variable: j is %p\n",&j);
    printf("Address of local variable: k is %p\n",&k);
    printf("Address of global variable: a is %p\n",&a);
    printf("Address of global variable: b is %p\n",&b);
    printf("Address of global variable: c is %p\n",&c);
    while(1) {
        printf("Thread 1 Global Value a: %d\n",a);
        printf("Thread 1 Global Value b: %d\n",b);
        printf("Thread 1 Global Value c: %d\n",c);
        printf("Thread 1 local Value i: %d\n",i);
        printf("Thread 1 local Value j: %d\n",j);
        printf("Thread 1 local Value k: %d\n",k);
    }
}

```

thread2 will call the following function on creation

```{c}

void * thread2_proc() {
    int i=10, j=12, k=14;   
    a=10;
    b=12;
    c=14;
    printf("Address of local variable: i is %p\n",&i);
    printf("Address of local variable: j is %p\n",&j);
    printf("Address of local variable: k is %p\n",&k);
    printf("Address of global variable: a is %p\n",&a);
    printf("Address of global variable: b is %p\n",&b);
    printf("Address of global variable: c is %p\n",&c);
    while(1) {
        printf("Thread 2 Global Value a: %d\n",a);
        printf("Thread 2 Global Value b: %d\n",b);
        printf("Thread 2 Global Value c: %d\n",c);
        printf("Thread 2 local Value i: %d\n",i);
        printf("Thread 2 local Value j: %d\n",j);
        printf("Thread 2 local Value k: %d\n",k);
    }
}

```

thread3 will call the following function on creation

```{c}

void * thread3_proc() {
    int i=16, j=18, k=20;    
    a=16;
    b=18;
    c=20;
    printf("Address of local variable: i is %p\n",&i);
    printf("Address of local variable: j is %p\n",&j);
    printf("Address of local variable: k is %p\n",&k);
    printf("Address of global variable: a is %p\n",&a);
    printf("Address of global variable: b is %p\n",&b);
    printf("Address of global variable: c is %p\n",&c);
    while(1) {
        printf("Thread 3 Global Value a: %d\n",a);
        printf("Thread 3 Global Value b: %d\n",b);
        printf("Thread 3 Global Value c: %d\n",c);
        printf("Thread 3 local Value i: %d\n",i);
        printf("Thread 3 local Value j: %d\n",j);
        printf("Thread 3 local Value k: %d\n",k);
    }
}

```

part of output of program is as follow

```{sh}

Thread 1 local Value i: 5
Thread 1 local Value j: 8
Thread 1 local Value k: 9
Thread 1 Global Value a: 16
Thread 1 Global Value b: 18
Thread 1 Global Value c: 20

```

From the above output of program we had observed that thread1 has modified global variables a, b, c to 5, 8, 9 respectively but prints values of a, b, c as 16, 18, 20 which are the values written by thread 3 because global variables are in data segment of a program which is shared accross all threads.<br>
Whereas thread1 modifies local variables i, j ,k to 5, 8, 9 respectively and prints the same because the local variables are not shared, because local variables are in stack portion and thread has their own stack portion.