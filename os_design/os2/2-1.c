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
int wait_mark;
int main() {
    pid_t p1,p2;
    if(p1 = fork()) {
        if(p2 = fork()) {
            wait_mark = 1;
            signal(SIGINT,stop);
            waiting();
            //sleep(5);
            kill(p1,16);
            kill(p2,17);
            wait(0);
            wait(0);
            printf("父进程被杀死！\n");
            exit(0);
        }else {
            wait_mark = 1;
            signal(SIGINT,stop) ;
            wait(0);
            lockf(1,1,0);
            printf("子进2被父进程程被杀死！\n");
            lockf(1,0,0);
            exit(0);
        }

    }else {
        wait_mark = 1;
        signal(SIGINT,stop);
        wait(0);
        lockf(1,1,0);//锁定屏幕输出
        printf("子进1被父进程程被杀死！\n");
        lockf(1,0,0);
        sleep(5);
        exit(0);
      
    }
}
void waiting() {
    while(wait_mark != 0); 
}
void stop() {
    wait_mark = 0;
}
