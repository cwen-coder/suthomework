/*************************************************************************
	> File Name: 2-1.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月03日 星期五 10时50分05秒
 ************************************************************************/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void waiting();
void stop();
void alarming();
int wait_mark;
int main() {
    int p1,p2;
    if( p1 = fork() ) {
        if(p2 = fork()) {
            wait_mark = 1;
            signal(SIGINT,stop);
            signal(SIGALRM,alarming);
            waiting();
            kill(p1,16);
            kill(p2,17);
            wait(0);
            wait(0);
            printf("父进程被杀死！\n");
            exit(0);
        }else {
            wait_mark = 1;
            signal(17,stop);
            signal(SIGINT,SIG_IGN);
            while(wait_mark != 0);
            lockf(1,1,0);
            printf("子进程2被父进程杀死！\n");
            lockf(1,0,0);
            exit(0);
        }
    }else {
            wait_mark = 1;
            signal(16,stop);
            signal(SIGINT,SIG_IGN);
            while(wait_mark != 0);
            lockf(1,1,0);
            printf("子进程1被父进程杀死！\n");
            lockf(1,0,0);
            exit(0);
      
    }
}
void waiting() {
    while(wait_mark != 0);
}
void stop() {
    wait_mark = 0;
}
void alarming() {
    wait_mark = 0;
}
