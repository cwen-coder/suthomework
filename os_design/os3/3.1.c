#include<stdio.h>
#include<stdlib.h>
#define getpch(type) (type*)malloc(sizeof(type)) 
struct LNode { 
	int size;
	int start;
	int end;
	struct LNode *next;
	struct LNode *front;
}*L; 
typedef struct LNode LN;
LN *find;
int n;
void InsertList(int size,int start) {	
	LN *p,*s,*t;
	p=L;
	t=p->next;	                                  
	s=getpch(LN);  
	s->size=size;
	s->start=start;
	s->end=start + size ;	
	s->next=t;      
	p->next=s;
	if(t)   t->front=s;
	s->front=p;
}
void PrintList() {
	LN *p; int i;
	p=L->next;
	printf("\n空闲区号  长度  起始位置  终止位置\n");
	for(i=1;i<=n;i++) {
		printf(" %3d\t  %3d\t%3d\t  %4d\n",i,p->size, p->start,p->end);
		p=p->next;
	}
}
void BFSortList() {
	LN *p,*s,*t;
	int min_size,i;
	int size,start,end;		
	t=L->next;
	p=L->next;
	for(i=0;i<n;i++) {
		s=p->next;
		min_size = p->size;
		while(s){
			if(min_size>s->size) {
				min_size=s->size;
				t=s;
			}
			s=s->next;
		}
		size=t->size;
		start=t->start;
		end=t->end;
		
		t->size=p->size;
		t->start=p->start;
		t->end=p->end;
		
		p->size=size;
		p->start=start;
		p->end=end;
		
		t=p->next;
		p=p->next;
	}
}

void SortList() {
	LN *p,*s,*t;
	int min_start,i;
	int size,start,end;		
	t=L->next;
	p=L->next;
	for(i=0;i<n;i++) {
		s=p->next;
		min_start=p->start;
		while(s){
			if(min_start>s->start){
				min_start=s->start;
				t=s;
			}
			s=s->next;
		}
		size=t->size;
		start=t->start;
		end=t->end;
		
		t->size=p->size;
		t->start=p->start;
		t->end=p->end;
		
		p->size=size;
		p->start=start;
		p->end=end;
		
		t=p->next;
		p=p->next;
	}
}
void GetFree()  {
	int size,start,i;
	L=getpch(LN);  
	L->next=NULL;
	L->front=NULL;
	printf("请输入空闲区数:");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{	
		printf("请输入第%2d空闲区的大小和始址:\n",i);
		scanf("%d %d",&size,&start);
		InsertList(size,start);
	}
	printf("分配完毕!\n");
	//printf("\n空闲链表情况:\n");
	//PrintList();
}
void Assign(int size) 
{
	LN *p,*t;
	p=L->next;
	t=L;
	while(p){
		if(size > p->size){
			p=p->next;
			t=t->next;
			if(!p){				
				printf("没有足够大的空闲区分配！分配不成功");			   
			}
		}
		else{
			p->size = p->size - size;
			p->start= p->start + size ;
			if(p->size==0){
				t->next = p->next ;
				p->next->front=t;
				n--;
				free(p);
			}			
			printf("分配成功！\n");
			printf("分配后的空闲链表情况如下:\n");
			PrintList();
			break;			
		}
	}
}
int flag=-1;
void NF_Assign(int size) {
	LN *p,*t;
	int i=n;
	p=find->next;
	t=find;
	while(p) {
		if(size > p->size){
			p=p->next;
			t=t->next;
			if(!p){				
				printf("没有足够大的空闲区分配！分配不成功");			   
			}
		}
		else{
			p->size = p->size - size;
			p->start= p->start + size ;
			find=p;
			if(p->size==0){
				t->next = p->next;
				p->next->front=t;
				n--;
				free(p);
			}
			printf("分配成功！\n");
			flag=1;
			printf("分配后的空闲链表情况如下：\n");
			PrintList();
			break;	
		}
	}
	if(flag==-1){	
		p=L->next;
		t=L;	
	while(p!=find){
		if(size > p->size){
			p=p->next;
			t=t->next;
			if(!p){				
				printf("没有足够大的空闲区分配！分配不成功");			   
			}
		}
		else{
			p->size = p->size - size;
			p->start= p->start + size ;
			find=t;
			if(p->size==0){
				t->next = p->next ;
				p->next->front=t;
				n--;
				free(p);
			}
			printf("分配成功！\n");
			printf("分配后的空闲链表情况如下：");
			PrintList();	
			break;
		}
		
	}
	
	}
}
void  Recover(int start, int end)  {
	LN *p,*t;
	int size,flag=0;
	size=end-start;	
	p=L->next;
	t=p->next;
	while(p){
		if(t && p->end==start && t->start==end){
			p->size = p->size + size + t->size;
			p->end = t->end;
			p->next=t->next;
            t->next->front=p;
			free(t);
			n--;
			SortList();			
			
			flag=1;
            break;			
		}
		else if(p->end == start){    
			flag=1;
			p->size = p->size + size;
			p->end = p->end + size ;
			SortList();			
			
			break;
		}
		else if( p->start == end){
			p->size= p->size +size;
			p->start=start;
			SortList();
			flag=1;
			
			break;
		}
		p=p->next;     
		if(p)
			t=p->next;               
	}

	if(flag==0){ 
		InsertList(size,start); 
		n++;
	}
	printf("回收后的空闲链表情况如下:");
	PrintList();  
	printf("按任意键继续\n");  
}
int window()
{
	int m;
//	system("cls");
	printf("++++++++++动态内存分配算法演示程序++++++++++\n");
	printf("+          按对应数字选择对应算法          +\n");
	printf("+   1.首次适应算法      2.循环首次适应算法 +\n");
	printf("+   3.最佳适应算法      4.回收内存         +\n");
	printf("+               按0退出!                   +\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++\n");
	scanf("%d",&m);
	return m;
}
int main(){
	int start,end,size;
	int m;
	GetFree();
	getchar();
    m=window();
	if(m==2) find=L;
	while(m){
		switch(m){
		case 1:	    
			SortList();  
			printf("\n空闲链表情况:\n");
			PrintList();
			printf("请输入进程需要的空闲区大小:");
			scanf("%d",&size);
			Assign(size); printf("\n按任意键继续");
			break;
		case 2:	   
			SortList();  
			printf("\n空闲链表情况:\n");
			PrintList();
			printf("请输入进程需要的空闲区大小:");
			scanf("%d",&size);
			NF_Assign(size);printf("\n按任意键继续");
			break;
		case 3:	    
			BFSortList();  
			printf("\n空闲链表情况:\n");
			PrintList();
			printf("请输入进程需要的空闲区大小:");
			scanf("%d",&size);
			Assign(size);printf("\n按任意键继续");
			break;
		case 4:	    
			printf("请输入回收区的首地址和中止地址:");
			scanf("%d %d",&start,&end);								
			Recover(start,end);
			break;	
		case 0:	    
			exit(0);
		default : 
			printf("\n\t\t输入错误,请重新输入"); getchar(); 
		}
		getchar();
		m=window();
	}
return 0;
}
