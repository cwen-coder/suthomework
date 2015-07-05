/*************************************************************************
	> File Name: 5.1.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月05日 星期日 01时10分54秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#define M 3
#define N 5
void output(int max[N][M],int allication[N][M],int need[N][M],int available[M],char name[N]);
int safety(int allication[N][M],int need[N][M],int available[M],char name[N]);
int banker(int max[N][M],int allication[N][M],int need[N][M],int available[M],char name[N]);
int main() {
    int available[M] = {3,3,2};
    int max[N][M] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}}; 
    int need[N][M],allication[N][M] = {{0,1,1},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    char name[N] = {'A','B','C','D','E'};
    int flag = 1;
    char ch;
    int i,j;
    for(i = 0; i < N; i++) 
        for(j = 0; j < M; j++)
            need[i][j] = max[i][j] - allication[i][j];
    output(max,allication,need,available,name);
    int safe = safety(allication,need,available,name);
    while(flag) {
        printf("继续提出申请？\ny 为是； n为否。\n");
        scanf("%c",&ch);
        switch(ch) {
            case 'y':
                safe = banker(max,allication,need,available,name);
                if(safe) output(max,allication,need,available,name);
                break;
            case 'n' :
                printf("退出\n");
                flag = 0;
                break;
            default:
                printf("输入有误，重新输入：\n");
        }
    }
    return 0;
}

void output(int max[N][M],int allication[N][M],int need[N][M],int available[M],char name[N]) {
    int i,j;
    printf("\n\t  Max   \tAllacation\t  Need    \tAvailable\n");
    printf("\tA   B   C\tA   B   C\tA   B   C\t A   B   C\n");
    for(i = 0; i < N; i++) {
        printf("%c\t",name[i]);
        for(j = 0; j < M; j++) printf("%d  ",max[i][j]);
        printf("\t");
        for(j = 0; j < M; j++) printf("%d  ",allication[i][j]);
        printf("\t");
        for(j = 0; j < M; j++) printf("%d  ",need[i][j]);
        printf("\t");
        if(i == 0) {
            for(j = 0; j < M; j++) printf("%d  ",available[j]);
        }
        printf("\n");
    }
}

int safety(int allication[N][M],int need[N][M],int available[M],char name[N]) {
   int i,j,flag,x = 0; 
    char num[5];
    int work[M];
    int finish[N] = {0};
    for(i = 0; i < M; i++) {
        work[i] = available[i];
    }
    while(1) {
        flag = 0;
        for(i = 0; i < N; i++) {
            if(finish[i] == 0 && work[0] >= need[i][0] && work[1] >= need[i][1] && work[2] >= need[i][2]) {
                for(j = 0; j < M; j++) work[j] += allication[i][j];
                finish[i] = 1;
                flag++;
                num[x++] = name[i];
                //printf("%c   ",name[i]);
            }
        }
        if(flag == 0) {
            printf("无安全序列");
            return -1;
        }
        if(finish[0] == 1 && finish[1] == 1 && finish[2] == 1 && finish[3] == 1 && finish[4] == 1) {
            printf("\n安全序列为：");
            for(x = 0; x < 5; x++) printf("%c  ",num[x]);  
            printf("\n");
            return 1;
        }
    }
    return 1;
}
int banker(int max[N][M],int allication[N][M],int need[N][M],int available[M],char name[N]){
    int i,j,request[M],check[M];
    char x;
    printf("请输入进程名：");
    getchar();
    scanf("%c",&x);
    switch(x) {
        case 'A':
            i = 0; break;
        case 'B':
            i = 1; break;
        case 'C':
            i = 2; break;
        case 'D':
            i = 3; break;
        case 'E':
            i = 4; break;
        default:
            printf("输入的进程不存在!\n");  
            return -1;
    }
    printf("请输入请求个资源的数量:");
    for(j = 0; j < M; j++) scanf("%d",&request[j]);
    getchar();
    for(j = 0; j< M; j++) {
        if(request[j] + allication[i][j] > max[i][j]) {
            printf("\n资源申请超过最大需求量！\n");
            return -1;
        }
        if(available[j] < request[j]) {
            printf("\n不能满足进程！\n");
            return -1;
        }
    }
    for(j = 0; j < M; j++) {
        available[j] -= request[j];
        allication[i][j] += request[j];
        need[i][j] -= request[j];
    }
    safety(allication,need,available,name);
    return 1;

}
