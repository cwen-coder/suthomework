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
    int p1,p2;
    while((p1 = fork()) == -1);
    if( p1 > 0) {
        while( (p2 = fork()) == -1 );
        if(p2 > 0) {
            wait_mark = 1;
            signal(SIGINT,stop);
            waiting();
            kill(p1,3);
            kill(p2,5);
            //kill(stdout,7);
            wait(0);
            wait(0);
            //sleep(1);
            printf("父进程被杀死！\n");
            //sleep(1);
            exit(0);
        }
    }else {
            wait_mark = 1;
            signal(SIGINT,stop);
            wait(0);
            lockf(1,1,0);
            printf("子进程被父进程杀死！\n");
            lockf(1,0,0);
            exit(0);
      
    }
    return 0;
}
void waiting() {
    while(wait_mark != 0); 
}
void stop() {
    wait_mark = 0;
}
