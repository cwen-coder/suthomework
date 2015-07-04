/*************************************************************************
	> File Name: 4.2.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月04日 星期六 15时16分19秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
    char name[20];
    int prio;
    int round;
    int cputime;
    int needtime;
    char state;
    int count;
    struct node *next;
}PCB;
typedef struct Queue {
    PCB *LinkPCB;
    int prio;
    int round;
    struct Queue *next;
}ReadyQueue;
PCB *run = NULL;
PCB *finish = NULL;
ReadyQueue *Head = NULL;
int num;
int ReadyNum;
void Output();
void InsertFinish(PCB *in);
void InsertPrio(ReadyQueue *in);
void PrioCreate();
void GetFirst(ReadyQueue *queue);
void InsertLast(PCB *in,ReadyQueue *queue);
void ProcessCreate();
void RoundRun(ReadyQueue *timechip);
void MultiDispatch();
int main() {
    PrioCreate();
    ProcessCreate();
    MultiDispatch();
    Output();
    return 0;
}
void Output() {
    ReadyQueue *print = Head;
    PCB *p;
    printf("进程名\t优先级\t轮数\tCPU时间\t需要时间\t进程状态\t计数器\n");
    while(print) {
        if(print -> LinkPCB != NULL) {
            p = print -> LinkPCB;
            while(p) {
                printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);
                p = p->next;
            }
        }
        print = print -> next;
    } 
    p = finish;
    while(p!=NULL) {
            printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);
            p = p->next;
    }
    p = run;
    while(p!=NULL) {
            printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);
            p = p-> next;  
    }
}
void InsertFinish(PCB *in) {
    PCB *fst;
    fst = finish;
    if(finish == NULL) {
        in -> next = finish;
        finish = in;
    }else {
        while(fst->next != NULL) {
            fst = fst->next;
        }
        in->next = fst -> next;
        fst->next = in;
    }
}
void InsertPrio(ReadyQueue *in) {
   ReadyQueue *fst,*nxt; 
    fst = nxt = Head;
    if(Head == NULL){
        in->next = Head;
        Head = in;
    } else {
        if(in -> prio >= fst -> prio) {
            in->next = Head;
            Head = in;
        } else {
            while(fst -> next != NULL) {
                nxt = fst;
                fst = fst->next;
                if(in -> prio >= fst -> prio) break;
            }
            if(fst -> next == NULL) {
                in -> next = fst->next;
                fst->next = in;
            }else {
                in -> next = fst;
                nxt -> next = in;
            }
        }
    }
}
void PrioCreate() {
    ReadyQueue *tmp;
    int i;
    printf("输入就绪队列的个数：");
    scanf("%d",&ReadyNum);
    printf("输入每个就绪队列的CPU时间片：");
    for(i = 0; i < ReadyNum; i++){
        if((tmp = (ReadyQueue *)malloc(sizeof(ReadyQueue))) == NULL) {
            perror("119行处申请内存出错\n");
            exit(1);
        }
        scanf("%d",&(tmp->round));
        tmp -> prio = 50 - tmp -> round;
        tmp -> LinkPCB = NULL;
        tmp -> next = NULL;
        InsertPrio(tmp);
    }
}
void GetFirst(ReadyQueue  *queue) {
    run = queue -> LinkPCB;
    if(queue->LinkPCB != NULL){
        run -> state = 'R';
        queue -> LinkPCB = queue -> LinkPCB -> next;
        run ->next = NULL;
    }
}
void InsertLast(PCB *in,ReadyQueue *queue) {
   PCB *fst;
    fst = queue -> LinkPCB;
    if(queue -> LinkPCB == NULL) {
        in -> next = queue->LinkPCB;
        queue -> LinkPCB = in;
    } else {
        while(fst -> next != NULL) fst = fst->next;
        in -> next = fst-> next;
        fst-> next = in;
    }
}
void ProcessCreate() {
    PCB *tmp;
    int i;
    printf("输入进程的个数：");
    scanf("%d",&num);
    printf("输入进程的名字和进程所需要的时间：\n");
    for(i = 0; i < num; i++) {
        if((tmp = (PCB *)malloc(sizeof(PCB))) == NULL) {
            perror("第157行处申请内存出错\n");
            exit(1);
        }
        scanf("%s",tmp->name);
        getchar();
        scanf("%d",&(tmp->needtime));
        tmp -> cputime = 0;
        tmp -> state = 'W';
        tmp -> prio = 50 - tmp->needtime;
        tmp -> round = Head -> round;
        tmp -> count = 0;
        InsertLast(tmp,Head);
    }
}
void RoundRun(ReadyQueue *timechip) {
    int flag = 1;
    GetFirst(timechip) ;
    while(run != NULL) {
        while(flag) {
            run -> count++;
            run -> cputime++;
            run -> needtime--;
            if(run -> needtime == 0) {
                run -> state = 'F';
                InsertFinish(run);
                flag = 0;
            } else if(run -> count == timechip -> round) {
                run ->  state = 'W';
                run -> count = 0;
                InsertLast(run,timechip);
                flag = 0;
            }
        }
        flag = 1;
        GetFirst(timechip);
    }
}
void MultiDispatch() {
    int flag = 1;
    int k = 0;
    ReadyQueue *point;
    point = Head;
    GetFirst(point);
    while(run != NULL) {
        Output();
        if(Head ->LinkPCB != NULL) point = Head;
        while(flag) {
            run -> count++;
            run -> cputime++;
            run -> needtime--;
            if(run -> needtime == 0) {
                run -> state = 'F';
                InsertFinish(run);
                flag = 0;
            }else if(run -> count == run -> round) {
                run -> state = 'W';
                run -> count = 0;
                if(point -> next != NULL) {
                    run -> round = point -> next -> round;
                    InsertLast(run, point -> next) ;
                    flag = 0;
                } else {
                    RoundRun(point);
                    break;
                }
            }
            ++k;
            if (k == 3) ProcessCreate();
        }
        flag = 1;
        if(point -> LinkPCB == NULL) point = point ->next;
        if(point -> next == NULL) {
            RoundRun(point);
            break;
        }
        GetFirst(point);
    }
}
