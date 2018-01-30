#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// global variables
int g_first=1, g_second=3, g_third=4;

void print_variable() {
    int j, k, l;
    g_first=5;
    g_second=8;
    g_third=9;
    printf("Address of local variable: j is %p\n",&j);
    printf("Address of local variable: k is %p\n",&k);
    printf("Address of local variable: l is %p\n",&l);
    printf("Address of global variable: g_first is %p\n",&g_first);
    printf("Address of global variable: g_second is %p\n",&g_second);
    printf("Address of global variable: g_third is %p\n",&g_third);
    printf("Global Value g_first: %d\n",g_first);
    printf("Global Value g_second: %d\n",g_second);
    printf("Global Value g_third: %d\n",g_third);
    return;
}

int main() {
    // local variables
    int a, b, c;
    printf("Address of local variable: a is %p\n",&a);
    printf("Address of local variable: b is %p\n",&b);
    printf("Address of local variable: c is %p\n",&c);
    printf("Address of global variable: g_first is %p\n",&g_first);
    printf("Address of global variable: g_second is %p\n",&g_second);
    printf("Address of global variable: g_third is %p\n",&g_third);
    printf("Global Value g_first: %d\n",g_first);
    printf("Global Value g_second: %d\n",g_second);
    printf("Global Value g_third: %d\n",g_third);
    pid_t child_pid;
    int i;
    for(i=0;i<3;i++) {
        child_pid=fork();
        if(child_pid==0) {
            break;
        }
    }
    if(child_pid >=0) {
        if(child_pid==0) {
            FILE *in;
            char name_string[10];
            char file_name_string[10];
            sprintf(name_string,"%d",i);
            in=fopen(strncat(strncat(strncpy(file_name_string,"child",5),name_string,1),".sh",3),"w");
            fprintf(in,"kill -9 %d\n",getpid());
            fprintf(in,"rm -rf $0");
            fclose(in);
            print_variable();
            while(1) {

            }
        }
        else {
            FILE *in;
            int status;
            in=fopen("parent.sh","w");
            fprintf(in,"kill -9 %d\n",getpid());
            fprintf(in,"rm -rf $0");
            fclose(in);
            while(1) {
                wait(&status);
            }
        }
    }
    return 0;
}