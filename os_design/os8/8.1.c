/*************************************************************************
	> File Name: 8.1.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月04日 星期六 20时25分01秒
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
int Wait(int a);
int main() {
    pid_t p;
    while((p = fork()) != -1);
    if(p == 0) {
        while(1);
    }else {
        wait(0);
        printf("父进程！\n");
    }
    return 0;
}
