#include<stdio.h>
#include<string.h>
#include<ctype.h>
char *strupr(char *str) 
{ 
    char *ptr = str; 

    while (*ptr != '\0') { 
        if (islower(*ptr)) 
            *ptr = toupper(*ptr); 
        ptr++; 
    } 

    return str; 
}
char *strlwr(char *str) {
    char *ptr = str;
    while (*ptr != '\0'){
        if(isupper(*ptr))
            *ptr = tolower(*ptr);
        ptr++;
    }
    return str;
}
void main()
{
	int  full=0;                       //用于判断缓冲池是否为满
	int  emputy=15;                    //用于判断缓冲池时候为空
	char buffer[15][10];               //用于存放产品
	char ch[10];                       //用于接收生产的产品和消费的产品  
	int  i=0,j=0;
	int  num;
	int  number;
	int  numb;
	printf("----------------------------------产品使用说明-------------------------------\n");
	printf("1生产者生产产品\n");
	printf("2消费者消费产品\n");
	printf("3生产字母产品\n");
	printf("4生产数字产品\n");
	printf("5生产符号产品\n");
	printf("6消费方式(显示)\n");
	printf("7消费方式(打印)\n");
	printf("8消费方式(全部变成小写)\n");
	printf("9消费方式(全部变成大写)\n");
	printf("-----------------------------------------------------------------------------\n");
	while(1)
	{
		printf("请输入1或者2进行生产或消费:");
		scanf("%d",&num);
	if(num==1)                                                       //当num为1的时候，生产者生产产品
	{
		printf("请输入3或者4或者5生产不同的产品:");                  //当number为3时生产字符，为4时生产数字，为5时生产字符
		scanf("%d",&number);
		//以下生产字符
		if(number==3)
		{
			if(full==15)
			{
				printf("产品已满!\n");
			}
			if(full<15)
			{
				printf("请输入生产的产品:");
				scanf(" %s",ch);
				for(j=0;j<sizeof(ch);j++)
				{
					buffer[i][j]=ch[j];
				}
				j++;
				buffer[i][j]='\0';
				i++;
				full++;
				emputy--;
				printf("产品生产成功!产品为:%s\n",buffer[i-1]);
			}
		}//if(number==3)结束
		//以下生产数字
		if(number==4)
		{
			if(full==15)
			{
				printf("产品已满!\n");
			}
			if(full<15)
			{
				printf("请输入生产的产品:");
				scanf(" %s",ch);
				for(j=0;j<sizeof(ch);j++)
				{
					buffer[i][j]=ch[j];
				}
				j++;
				buffer[i][j]='\0';
				i++;
				full++;
				emputy--;
				printf("产品生产成功!产品为:%s\n",buffer[i-1]);
			}
		}//if(number==4)结束
		//以下生产字符
		if(number==5)
		{
			if(full==15)
			{
				printf("产品已满!\n");
			}
			if(full<15)
			{
				printf("请输入生产的产品:");
				scanf(" %s",ch);
			for(j=0;j<sizeof(ch);j++)
			{
				buffer[i][j]=ch[j];
			}
				j++;
				buffer[i][j]='\0';
				i++;
				full++;
				emputy--;
				printf("产品生产成功!产品为:%s\n",buffer[i-1]);
			}
		}//if(number==5)结束
	}//if(num==1)结束
	if(num==2)                                                           //当num为2时，消费者消费产品
	{
		printf("请输入6或者7或者8或者9选择不同消费方式:");               //当numb为6时显示，为7时打印，为8时转换成小写，为9时转换成大写
		scanf("%d",&numb);
		//以下为显示消费模式
		if(numb==6)
		{
			if(emputy<15)
			{
				i--;
				emputy++;
				full--;
				printf("消费成功!显示:%s\n",buffer[i]);
			}
			else
			{
				printf("产品为空!\n");
			}
		}//if(numb==6)结束
		//以下为打印消费模式
		if(numb==7)
		{
			if(emputy<15)
			{
				i--;
				emputy++;
				full--;
				printf("消费成功!打印:%s\n",buffer[i]);
			}
			else
			{
				printf("产品为空!\n");
			}
		}//if(numb==7)结束
		//以下为转换成小写消费模式
		if(numb==8)
		{
			if(emputy<15)
			{
				i--;
				emputy++;
				full--;
				printf("消费成功!转换成小写:%s\n",strlwr(buffer[i]));
			}
			else
			{
				printf("产品为空!\n");
			}
		}//if(numb==8)结束
		//以下为转换成大写消费模式
		if(numb==9)
		{
			if(emputy<15)
			{
				i--;
				emputy++;
				full--;
				printf("消费成功!转换成大写:%s\n",strupr(buffer[i]));
			}
			else
			{
				printf("产品为空!\n");
			}
		}
	}
	}
}
