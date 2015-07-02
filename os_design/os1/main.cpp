#include "basic.h"
pnode *proot;
pnode *plink;
int createpc(int *para) {
	pnode *p,*p1,*pp;
	int pflag;
	pflag = 0;
	for(p = plink; p; p = p->next) {
		if(p->node->pid == para[0]) {
			printf("pid%d is already exist\n",para[0]);
			return -1;
		}
		if(p->node->pid == para[1]) {
			pflag = 1;
			pp = p;
		} 
	}
	if(!pflag) {
		printf("parent id %d is not exit!\n",para[1]);
		return -2;
	}
	p1 = new pnode;
	p1->node = new pcb;
	p1->node->pid = para[0];
	p1->node->ppid = para[1];
	p1->node->prio = para[2];
	p1->sub = NULL;
	p1->next = NULL;
	p1->brother = NULL;
	if(!pp->sub) pp->sub = p1;
	else  {
		for(p = pp->sub;p->brother; p = p->brother);
		p->brother = p1;
	}
	
	for(p = plink; p->next; p = p->next);
	p->next = p1;
	return 0; 
}

void showdetail() {
	pnode *p,*p1;
	p = plink;
	for(;p;) {
		printf("%d(prio %d):",p->node->pid,p->node->prio);
		p1 = p->sub;
		for(;p1;) {
			printf("%d(prio %d)",p1->node->pid,p1->node->prio);
			p1 = p1->brother;
		}
		printf("\n");
		p = p->next;
	}
	printf("\n");
} 
int main() {
	initerror();
	short cflag,pflag;
	char cmdstr[32];
	proot = new pnode;
	proot->node = new pcb;
	proot->node->pid = 0;
	proot->node->ppid = 1;
	proot->node->prio = 0;
	proot->next = NULL;
	proot->sub = NULL;
	proot->brother = NULL;
	plink = proot;
	while(1) {
		cflag = 0;
		pflag = 0;
		printf("cmd:");
		scanf("%s",cmdstr);
		if(!strcmp(cmdstr,"exit")) break;
		if(!strcmp(cmdstr,"showdetail")){
			cflag = 1;
			pflag = 1;
			showdetail();
		} else {
			int *para;
			char *s,*s1;
			s = strstr(cmdstr,"createpc");
			if(s) {
				cflag = 1;
				para = (int *)malloc(3);
				s1 = substr(s,instr(s,'(')+1,strlen(s)-2);
				para = strtoarray(s1);
				createpc(para);
				pflag = 1;
			}
		}
		if(!cflag) {
			geterror(0);
		} else {
			if(!pflag)
				geterror(1);
		}
	}
	return 0;
}
