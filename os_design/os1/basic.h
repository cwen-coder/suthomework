#ifndef basic_h
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define basic_h
char *errormsg[256];
struct pcb {
	int pid;
	int ppid;
	int prio;
	int status;
	int lasttime;
	int tottime;
};
struct pnode {
	pcb *node;
	pnode *sub;
	pnode *brother;
	pnode *next;
}; 
struct semphore {
	char name[5];
	int count;
	int curpid;
	pnode *wlist;
};
#define geterror(eno) printf("%s\n",errormsg[eno])

void initerror() {
	errormsg[0] = (char *)malloc(20);
	errormsg[0] = "error command!";
	errormsg[1] = (char *)malloc(20);
	errormsg[1] = "error parameter!";
}

char *substr(char *s,int start,int end) {
	char *s1;
	int len = strlen(s);
	if(start < 0 || end >= len || start > end)
		return NULL;
	s1 = (char*)malloc(end-start+2);
	int i;
	for(i = 0; i <= end-start; i++)
		s1[i] = s[i+start];
	s1[i+1] = '\0';
	return s1; 
}

 int instr(char *s,char c) {
 	int i;
 	for(i = 0; i < strlen(s);i++)
 		if(s[i] == c) return i;
	return -1;
 }
 
 int *strtoarray(char *s) {
 	int *a,count,x1;
 	int i;
 	char c,*s1,*s2;
 	if(!s) {
	 	printf("string can't be null!\n"); 
	 	return NULL;
	 }
	 count = 0;
	 s1 = s;
	 for(i = 0; i < strlen(s1); i++) 
	 	if(s1[i] == ',')count++;
 	count++;
 	a = (int *)malloc(count);
 	c = ',';
 	for(i = 0; i < count; i++) {
	 	x1 = instr(s1,c);
	 	if(x1 > 0) s2 = substr(s1,0,x1-1);
	 	else s2 = s1;
	 	a[i] = atoi(s2);
	 	if(c == ',')
	 		s1 = substr(s1,x1+1,strlen(s1)-1);
	 }
	 return a; 
 }
 #endif
 
