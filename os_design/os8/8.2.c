#include<stdio.h> 
#define size 10
int empty,full,in,out,a[size]={0},i,m=1;
void produce()
{
	int j;
	if(empty>0) 
	{
		empty--; 
		a[in]=1;
		printf("生产了一件产品。\n");
		full++;
		printf("现在缓冲池里的产品数为：%d\n",full);
		printf("请输入接下来的操作，1为继续生产，2为消费：");
		in=(in+1)%size; 
		scanf("%d",&j);
		if(i==1 || i==2)
			i=j;
	}
	else 
	{
		printf("缓存池已满无法执行生产操作，如果你要继续操作，请输入2进行消费，否则输入其他任意键结束：");
		scanf("%d",&j);
		if(j==2)
			i=j; 
		else
			i=3;
	}
}
void consume()
{
	int j;
	if(full>0)
	{
		full--;
		a[out]=0;
		printf("消费了一件产品。\n");
		printf("现在缓冲池里的产品数为：%d\n",full);
		printf("请输入接下来的操作，1为生产，2为继续消费：");
		out=(out+1)%size;
		scanf("%d",&j);
		if(i==1||i==2)
			i=j;
		empty++;
	}
	else 
	{
		printf("缓存池已空无法执行消费操作，如果你要继续操作，请输入1进行生产，否则输入其他任意键结束：");
		scanf("%d",&j);
		if(j==1) 
			i=j; 
		else
			i=3;
	}
}
int main()
{ 
	empty=size;
	full=0;
	in=out=0;
	printf("请输入你想要执行的操作，1为生产，2为消费：");
	scanf("%d",&i);
	while(m)
	{
		switch(i)
		{
			case 1:
				produce();
				break;
			case 2:
				consume();
				break;
			default:
				printf("结束操作!\n");m=0;
		}
	}
return 0;
}
