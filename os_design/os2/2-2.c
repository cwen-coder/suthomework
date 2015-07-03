/*************************************************************************
	> File Name: 2-2.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月03日 星期五 17时51分14秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
int pid1,pid2;
int  main() {
    int fd[2];
    char outpipe[100],inpipe[100];
    pipe(fd);
    while((pid1 = fork()) == -1) ;
    if(pid1 == 0) {
        lockf(fd[1],1,0);
        sprintf(outpipe,"Message from Child 1! ");
        write(fd[1],outpipe,50);
        sleep(5);
        lockf(fd[1],0,0);
        exit(0);
    }else {
        while((pid2 = fork()) == -1);
        if(pid2 == 0) {
            lockf(fd[1],1,0);
            sprintf(outpipe,"Message from Child 2! ");
            write(fd[1],outpipe,50);
            sleep(5);
            lockf(fd[1],0,0);
            exit(0);
        }else {
            wait(0);
            read(fd[0],inpipe,50);
            printf("%s\n",inpipe);
            wait(0);
            read(fd[0],inpipe,50);
            printf("%s\n",inpipe);
            exit(0);
        }
    }
}
