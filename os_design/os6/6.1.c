/*************************************************************************
	> File Name: 6.1.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月04日 星期六 21时52分44秒
 ************************************************************************/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 10
void Output(int track[],int num);
void FCFS(int track[],int num);
void SSTF(int track[],int num);
void SCAN(int track[],int num);
void CSCAN(int track[],int num);
int compInc(const void *a,const void *b) {
    return *(int *)a - *(int *)b;
}
int main() {
    int input,num;
    int track[N];
    srand((int)time(0)); 
    int i;
    for(i=0;i<N;i++) { 
        track[i]=1+(int)(200.0*rand()/(RAND_MAX+1.0));      
        }
            printf("\n");
        num=1+(int)(200.0*rand()/(RAND_MAX+1.0));
    while(1) {
            printf("printf*************                磁盘调度算法               ***********\n");
            printf("printf*******************************************************************\n");
            printf("printf*************             请选择要使用的算法            ***********\n");
            printf("printf**********                                                 ********\n");
            printf("printf*****                  1、先来先服务调度算法(FCFS)            *****\n");
            printf("printf*****                  2、最短寻道时间优先调度算法(SSTF)      *****\n");
            printf("printf*****                  3、扫描调度算法(SCAN)                  *****\n");
            printf("printf*****                  4、循环扫描调度算法(CSCAN)             *****\n");
            printf("printf*****                  5、调用五种算法，进行比较              *****\n");
            printf("printf*****                  6、退出                                *****\n");
            printf("printf**********                                                 ********\n");
            printf("printf*************                                           ***********\n");
            printf("printf*******************************************************************\n\n");
            printf("请选择算法：");
            scanf("%d",&input);
            printf("\n");
            switch(input) {
                case 1:    
                    FCFS(track,num);
                    break;
                case 2:    
                    SSTF(track,num);  
                    break;
                case 3:    
                    SCAN(track,num);
                    break;
                case 4:    
                    CSCAN(track,num);
                    break;
                case 5:
                    FCFS(track,num);
                    SSTF(track,num);
                    SCAN(track,num);
                    CSCAN(track,num);
                    break;
                case 6:
                    exit(0);
                    break;
        }
    }
return 0;
}

void Output(int track[],int num) {
    printf("请求磁道的序列为：") ;
    int i;
    for(i = 0; i < N; i++) {
        printf(" %d ",track[i]);
    } 
    printf("\n");
    printf("当前所在磁道号为： %d\n",num);
}

void FCFS(int track[],int num) {
    int i;
    int sum = 0;
    double avg = 0.0;
    printf("*********************先来先服务调度算法**************************\n\n");
    Output(track,num);
    for(i = 0; i < N; i++) {
        if(num > track[i]) sum += num - track[i];
        else sum += track[i] - num;
        num = track[i];
    }
    avg = (double) sum / N;
    printf("磁道访问队列为：");
    for(i = 0; i < N; i++)printf(" %d ",track[i]);
    printf("\n平均寻道长度为： %.2lf\n\n",avg);
}
void SSTF(int track[],int num) {
    int status[N];
    int ctrack[N];
    int ttrack[N];
    int sum = 0;
    double avg = 0.0;
    memset(status,0,sizeof(status));
    memset(ctrack,-1,sizeof(ctrack));
    int i,j;
    int min = 201;
    int minj = 0;
    printf("**********************最短寻道时间优先调度算法********************\n\n");
    Output(track,num);
    for(i = 0; i < N; i++) {
        min = 201;
        minj = 0;
        for(j = 0; j < N; j++) {
            if(status[j] == 1) {
                ctrack[j] = 201;
            }else {
                if(num > track[j]) ctrack[j] = num - track[j]; 
                else ctrack[j] = track[j] - num;
            }
        }
        for(j = 0; j < N; j++) {
            if(ctrack[j] <= min) {
                min = ctrack[j];
                minj = j;
            }
        }
        sum += min;
        status[minj] = 1;
        num = track[minj];
        ttrack[i] = num;
        
    }
    avg = (double) sum / N;
    printf("磁道访问的序列为：");
    for(i=0;i<N;i++)
        printf(" %d ",ttrack[i]);
    printf("\n平均寻道长度为： %.2lf\n\n",avg);
}
void SCAN(int track[],int num) {
    int ctrack[N];
    int ttrack[N];
    int i ;
    int sum = 0;
    double avg = 0.0;
    for(i = 0; i < N; i++) {
        ctrack[i] = track[i];
    }
    printf("*****************************扫描调度算法*******************************\n\n");
    Output(track,num);
    qsort(ctrack,N,sizeof(ctrack[0]),compInc);
    if(num <= ctrack[0]) {
        for(i = 0; i < N; i++) {
            sum += ctrack[i] - num;
            num = ctrack[i];
            ttrack[i] = num;
        } 
    } else if(num >= ctrack[N-1]) {
        for(i = N-1; i >= 0; i--) {
            sum += num - ctrack[i];
            num = ctrack[i];
            ttrack[i] = num;
        }
    }else {
        int tmp1 = 0;
        int tmp2 = 0;
        for(i = 0; i < N; i++) {
            if(ctrack[i] <= num && ctrack[i+1] >= num) {
                tmp1 = i;
                tmp2 = i+1;
                break;
            }
        }
        if(num - ctrack[tmp1] > ctrack[tmp2] - num) {
            int j = 0;
            for(i = tmp2; i < N; i++) {
                sum += ctrack[i] - num;
                num = ctrack[i];
                ttrack[j++] = num;
            }
            for(i = tmp1;i >= 0; i--) {
                sum += num - ctrack[i] ;
                num = ctrack[i];
                ttrack[j++] = num;
            }
        }else {
            int j = 0;
            for(i = tmp1;i >= 0; i--) {
                sum += num - ctrack[i] ;
                num = ctrack[i];
                ttrack[j++] = num;
            }
            for(i = tmp2; i < N; i++) {
                sum += ctrack[i] - num;
                num = ctrack[i];
                ttrack[j++] = num;
            }
        }
    }
    avg = (double) sum / N;
    printf("磁道访问的序列为：");
    for(i=0;i<N;i++)
        printf(" %d ",ttrack[i]);
    printf("\n平均寻道长度为： %.2lf\n\n",avg);
}
void CSCAN(int track[],int num) {
    int ctrack[N];
    int ttrack[N];
    int i ;
    int sum = 0;
    double avg = 0.0;
    for(i = 0; i < N; i++) {
        ctrack[i] = track[i];
    }
    printf("*****************************循环扫描调度算法*******************************\n\n");
    Output(track,num);
    qsort(ctrack,N,sizeof(ctrack[0]),compInc);
    if(num <= ctrack[0]) {
        for(i = 0; i < N; i++) {
            sum += ctrack[i] - num;
            num = ctrack[i];
            ttrack[i] = num;
        } 
    } else if(num >= ctrack[N-1]) {
        for(i = N-1; i >= 0; i--) {
            sum += num - ctrack[i];
            num = ctrack[i];
            ttrack[i] = num;
        }
    }else {
        int tmp1 = 0;
        int tmp2 = 0;
        for(i = 0; i < N; i++) {
            if(ctrack[i] <= num && ctrack[i+1] >= num) {
                tmp1 = i;
                tmp2 = i+1;
                break;
            }
        }
        if(num - ctrack[tmp1] > ctrack[tmp2] - num) {
            int j = 0;
            for(i = tmp2; i < N; i++) {
                sum += ctrack[i] - num;
                num = ctrack[i];
                ttrack[j++] = num;
            }
            for(i = 0;i <= tmp1; i++) {
                sum += abs(num - ctrack[i]) ;
                num = ctrack[i];
                ttrack[j++] = num;
            }
        }else {
            int j = 0;
            for(i = tmp1;i >= 0; i--) {
                sum += num - ctrack[i] ;
                num = ctrack[i];
                ttrack[j++] = num;
            }
            for(i = N-1; i >= tmp2; i--) {
                sum += abs(ctrack[i] - num);
                num = ctrack[i];
                ttrack[j++] = num;
            }
        }
    }
    avg = (double) sum / N;
    printf("磁道访问的序列为：");
    for(i=0;i<N;i++)
        printf(" %d ",ttrack[i]);
    printf("\n平均寻道长度为： %.2lf\n\n",avg);
}

