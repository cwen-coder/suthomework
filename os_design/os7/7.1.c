/*************************************************************************
	> File Name: 7.1.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月05日 星期日 13时11分30秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#define QUOTO 20
#define BLOCK 3
int quo[QUOTO] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
int blo[BLOCK];
void Optimal(int quo[],int blo[]);
void FIFO(int quo[],int blo[]);
void LRU(int quo[],int blo[]);
int main() {
    int  ch;
    printf("******************页面置换算法********************\n");
    printf("                  Optimal置换算法：1\n");
    printf("                  FIFO置换算法：   2\n");
    printf("                  LRU置换算法：    3\n");
    printf("                  退出：           4\n");
    while(1) {
        printf("输入你的命令：");
        scanf("%d",&ch);
        memset(blo,-1,sizeof(blo));
        switch(ch) {
            case 1:
                Optimal(quo,blo);
                break;
            case 2:
                FIFO(quo,blo);
                break;
            case 3:
                LRU(quo,blo);
                break;
            case 4:
                return 0;
                break;
            default:
                printf("输入不正确！\n");
        }
    }
    return 0;
}

void Optimal(int quo[],int blo[]) {
    int count = 0;
    int i,j,k;
     int tmp[BLOCK];
    for(i = 0; i < QUOTO; i++) {
        for(j = 0; j < BLOCK;j++)tmp[j] = 100;
        if(count < BLOCK) {
            blo[count++] = quo[i];
            for(j = 0; j < count; j++) printf("%d  ",blo[j]);
            printf("\n");
        }else {
            int a = 0;
            for(j = 0; j < BLOCK; j++) {
                if(quo[i] == blo[j]) {
                    a = 1;
                    break;
                }
            }
            if(a == 1) printf("不缺页\n");
            else {
                for(j = 0; j < BLOCK; j++) {
                    for(k = i+1; k < QUOTO; k++) 
                    if(blo[j] == quo[k]) {
                        tmp[j] = k;
                        break;
                    }
                }
                int max = tmp[0];
                int t = 0;
                for(j = 1; j < BLOCK; j++) {
                    if(tmp[j] > max) {
                        max = tmp[j];
                        t = j;
                    }
                    //printf("%d\n",max);
                }
                blo[t] = quo[i];
                for(j = 0; j < BLOCK; j++) printf("%d  ",blo[j]);
                printf("\n");
            }
        }
    }
}

void FIFO(int quo[],int blo[]) {
    int count = 0;
    int old[BLOCK];
    int i,j;
    for(i = 0; i < BLOCK; i++) old[i] = 0;
    for(i = 0; i < QUOTO; i++) {
        if(count < BLOCK) {
            blo[count++] = quo[i];
            for(j = 0; j < count; j++) printf("%d  ",blo[j]);
            printf("\n");
            for(j = 0; j < count; j++) old[j]++;
        }else {  
            int a = 0;
            for(j = 0; j < BLOCK; j++) {
                if(quo[i] == blo[j]) {
                    a = 1;
                    break;
                }
            }
            if(a == 1) {
                printf("不缺页\n");
                for(j = 0; j < BLOCK; j++) old[j]++;
            } else {
                int max = old[0]; 
                int maxj = 0;
                for(j = 1; j < BLOCK; j++) {
                    if(old[j] > max){
                        max = old[j];
                        maxj = j;
                    }
                }
                blo[maxj] = quo[i];
                old[maxj] = 0;
                for(j = 0; j < BLOCK; j++){
                    if(j != maxj) old[j]++;
                } 
                for(j = 0; j < BLOCK; j++) printf("%d  ",blo[j]);
                printf("\n");
            }
        }
    }

}

void LRU(int quo[],int blo[]) {
    int count = 0;
    int old[BLOCK];
    int i,j;
    for(i = 0; i < BLOCK; i++) old[i] = 0;
    for(i = 0; i < QUOTO; i++) {
        if(count < BLOCK) {
            blo[count++] = quo[i];
            for(j = 0; j < count; j++) printf("%d  ",blo[j]);
            printf("\n");
            for(j = 0; j < count; j++) old[j]++;
        }else {  
            int a = 0;
            int te = 0;
            for(j = 0; j < BLOCK; j++) {
                if(quo[i] == blo[j]) {
                    a = 1;
                    old[j] = 0;
                    te = j;
                    break;
                }
            }
            if(a == 1) {
                printf("不缺页\n");
                for(j = 0; j < BLOCK; j++){
                    if(j != te) old[j]++;
                } 
            } else {
                int max = old[0]; 
                int maxj = 0;
                for(j = 1; j < BLOCK; j++) {
                    if(old[j] > max){
                        max = old[j];
                        maxj = j;
                    }
                }
                blo[maxj] = quo[i];
                old[maxj] = 0;
                for(j = 0; j < BLOCK; j++){
                    if(j != maxj) old[j]++;
                } 
                for(j = 0; j < BLOCK; j++) printf("%d  ",blo[j]);
                printf("\n");
            }
        }
    }
}
