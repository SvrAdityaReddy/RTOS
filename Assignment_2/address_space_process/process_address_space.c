#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// global variables
int g_first, g_second, g_third;

void print_variable(int *a, int *b, int *c) {
    printf("Address of local variable: a is %p\n",&a);
    printf("Address of local variable: b is %p\n",&b);
    printf("Address of local variable: c is %p\n",&c);
    printf("Address of global variable: g_first is %p\n",&g_first);
    printf("Address of global variable: g_second is %p\n",&g_second);
    printf("Address of global variable: g_third is %p\n",&g_third);
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
            print_variable(&a,&b,&c);
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