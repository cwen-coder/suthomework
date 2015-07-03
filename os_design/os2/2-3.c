/*************************************************************************
	> File Name: 2-3.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月03日 星期五 19时20分19秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#define MSGKEY 1234
struct msgform {
    long int mtype;
    char metexe[100];
}msg;
int msgqid,i;
void sender() {
    int i;
    msgqid = msgget(MSGKEY,0777|IPC_CREAT);
    for(i = 10; i >= 1; i--) {
        msg.mtype = i;
        printf("Sender sent\n");
        msgsnd(msgqid,&msg,1028,0);
    }
    exit(0);
}
void resever() {
    msgqid = msgget(MSGKEY,0777|IPC_CREAT);
    do {
        msgrcv(msgqid,&msg,1028,0,0);
        printf("Resever reseve\n");
    }while(msg.mtype != 1);
    msgctl(msgqid,IPC_CREAT,0);
}
int main() {
    if(fork()) {
        resever();
        wait(0);
    }else sender();
    return 0;
}
