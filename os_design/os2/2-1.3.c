/*************************************************************************
	> File Name: 2-1.3.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月03日 星期五 16时10分40秒
 ************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
void ouch();
int temp = 0;
int main() {
    pid_t p1,p2;
    while((p1 = fork()) == -1);
    if( p1 == 0 ) {
        while(1);
    }else {
        while((p2 = fork()) == -1);
        if(p2 == 0) {
            while(1);
        }else {
            signal(SIGINT,ouch);
            if(temp == 1){
                kill(p1,16);
                kill(p2,17);
            }
        }
    }
    wait(0);
    printf("Child 1 Proeess 1 is Killed by Parent!\n ");
    printf("Child 2 Proeess 1 is Killed by Parent!\n ");
    printf("Parent Process is Killed!\n");
    return 0;
}
void ouch(int sig) {
    temp = 1;
}
