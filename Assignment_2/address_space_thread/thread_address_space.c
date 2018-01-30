#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int a, b, c;

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

int main() {
    pthread_t t1, t2, t3;
    a=2;
    b=4;
    c=6;
    pthread_create(&t1,NULL,thread1_proc,NULL);
    pthread_create(&t2,NULL,thread2_proc,NULL);
    pthread_create(&t3,NULL,thread3_proc,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    return 0;
}