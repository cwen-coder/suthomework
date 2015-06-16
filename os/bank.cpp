#include<iostream>
#include<cstring>
#include<cstdio>
#define False 0
#define True 1
using namespace std;
int Max[100][100]={0};              //各进程所需各类资源的最大需求
int Avaliable[100]={0};             //系统可用资源
char name[100]={0};                 //资源的名称
int Allocation[100][100]={0};       //系统已分配资源
int Need[100][100]={0};             //还需要资源
int Request[100]={0};               //请求资源向量
int temp[100]={0};                  //存放安全序列
int Work[100]={0};                  //存放系统可提供资源
int M=100;                          //作业的最大数为100
int N=100;                          //资源的最大数为100
void showdata()                //显示资源矩阵
{
	int i,j;
	cout<<"系统目前可用的资源[Avaliable]:"<<endl;
	for(i=0;i<N;i++)
		cout<<name[i]<<" ";
	cout<<endl;
	for (j=0;j<N;j++)
		cout<<Avaliable[j]<<" ";     //输出分配资源
	cout<<endl;
	cout<<"            Max         Allocation        Need"<<endl;
	cout<<"进程名:\t    ";
	for(j=0;j<3;j++){
		for(i=0;i<N;i++)
			cout<<name[i]<<" ";
		cout<<"        ";
	}
	cout<<endl;
	for(i=0;i<M;i++){
		cout<<" "<<i<<"          ";
		for(j=0;j<N;j++)
			cout<<Max[i][j]<<" ";
		cout<<"        ";
		for(j=0;j<N;j++)
			cout<<Allocation[i][j]<<" ";
		cout<<"        ";
		for(j=0;j<N;j++)
			cout<<Need[i][j]<<" ";
		cout<<endl;
	}
}

int changdata(int i)                             //进行资源分配
{ 
	int j;
	for (j=0;j<M;j++) {
		Avaliable[j]=Avaliable[j]-Request[j];
		Allocation[i][j]=Allocation[i][j]+Request[j];
		Need[i][j]=Need[i][j]-Request[j];
	}
	return 1;
}
int safe()                                        //安全性算法
{
	int i,k=0,m,apply,Finish[100]={0};
	int j;
	int flag=0;
	Work[0]=Avaliable[0];
	Work[1]=Avaliable[1];
	Work[2]=Avaliable[2];
	for(i=0;i<M;i++){ 
		apply=0;
		for(j=0;j<N;j++){
			if (Finish[i]==False&&Need[i][j]<=Work[j])
			{   
				apply++;
				if(apply==N){
					for(m=0;m<N;m++)
						Work[m]=Work[m]+Allocation[i][m];    //变分配数
					Finish[i]=True;
					temp[k]=i;
					i=-1; 
					k++;
					flag++;
				}
			}
		}
	}
	for(i=0;i<M;i++){
		if(Finish[i]==False){
			cout<<"系统不安全"<<endl;         //不成功系统不安全
			return -1;
		}
	}
    cout<<"系统是安全的!"<<endl;             //如果安全，输出成功提示
    cout<<"分配的序列:";
	for(i=0;i<M;i++)
	{                                        //输出运行进程数组
		cout<<temp[i];
		if(i<M-1) cout<<"->";
	}
	cout<<endl;
	return 0;
}
void share()                                //利用银行家算法对申请资源对进行判定
{
	char ch;
	int i=0,j=0;
	ch='y';
	cout<<"请输入要求分配的资源进程号(0-"<<M-1<<"):"; 
    cin>>i;                                //输入须申请的资源号
	cout<<"请输入进程 "<<i<<" 申请的资源:"<<endl;
	for(j=0;j<N;j++)
	{
		cout<<name[j]<<":";
		cin>>Request[j];                    //输入需要申请的资源
	}
	for (j=0;j<N;j++){
		if(Request[j]>Need[i][j])           //判断申请是否大于需求，若大于则出错
		{ 
			cout<<"进程 "<<i<<"申请的资源大于它需要的资源";
			cout<<" 分配不合理，不予以分配！"<<endl;
			ch='n';
			break;
		}
		else {
			if(Request[j]>Avaliable[j])       //判断申请是否大于当前资源，若大于则出错
			{                         
				cout<<"进程"<<i<<"申请的资源大于系统现在可利用的资源";
				cout<<" 分配出错，不予分配!"<<endl;
				ch='n';
				break;
			}
		}
    }
    if(ch=='y') {
		changdata(i);                     //根据进程需求量变换资源
		showdata();                       //根据进程需求量显示变换后的资源
		safe();                           //根据进程需求量进行银行家算法判断
    }
}
void addresources()                       //添加资源
{                                     
    int n,flag;
	cout<<"请输入需要添加资源种类的数量:";
	cin>>n;
	flag=N;
	N=N+n;
	for(int i=0;i<n;i++){
		cout<<"名称:";
		cin>>name[flag];
		cout<<"数量:";
		cin>>Avaliable[flag++];
	}
	showdata();
	safe();
}
void delresources()                   //释放资源
{                               
	char ming;
	int i,flag=1;
	cout<<"请输入需要释放的资源名称：";
	do{
		cin>>ming;
		for(i=0;i<N;i++)
			if(ming==name[i]){
				flag=0;
				break;
			}
			if(i==N)
				cout<<"该资源名称不存在，请重新输入：";
	}
	while(flag);
	for(int j=i;j<N-1;j++)
	{
		name[j]=name[j+1];
		Avaliable[j]=Avaliable[j+1];
		
    }
	N=N-1;
	showdata();
	safe();
}
void changeresources()          //修改资源函数
{                              
	cout<<"系统目前可用的资源[Avaliable]:"<<endl;
    for(int i=0;i<N;i++)
		cout<<name[i]<<":"<<Avaliable[i]<<endl;
	cout<<"输入系统可用资源[Avaliable]:"<<endl;
	cin>>Avaliable[0]>>Avaliable[1]>>Avaliable[2];
	cout<<"经修改后的系统可用资源为"<<endl;
	for (int k=0;k<N;k++)
		cout<<name[k]<<":"<<Avaliable[k]<<endl;
	showdata();
	safe();
}
void addprocess()                     //添加作业
{                         
    int flag=M;
	M=M+1;
	cout<<"请输入该作业的最大需求量[Max]"<<endl;
	for(int i=0;i<N;i++){
		cout<<name[i]<<":";
		cin>>Max[flag][i];
		Need[flag][i]=Max[flag][i]-Allocation[flag][i];
	}
	showdata();
	safe();
}
int main()                     //主函数
{
	
    int i,j,number,choice,m,n,flag;
	char ming;
	cout<<"\t **************资源管理系统的设计与实现*************"<<endl;
	cout<<"\t ********************银行家算法设计*****************"<<endl;
	cout<<"\t\t  请输入系统可供资源种类的数量:";
	cin>>n;
	N=n;
	for(i=0;i<n;i++)
	{
		cout<<"资源"<<i+1<<"的名称:";
		cin>>ming;
		name[i]=ming;
		cout<<"资源"<<i+1<<"的数量:";
		cin>>number;
		Avaliable[i]=number;
	}
	cout<<endl;
	cout<<"请输入作业的数量:";
	cin>>m;
	M=m;
	cout<<"\t\t请输入各进程的最大需求量("<<m<<"*"<<n<<"矩阵)[Max]:"<<endl;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			cin>>Max[i][j];
		do{
			flag=0;
			cout<<"\t\t请输入各进程已申请的资源量("<<m<<"*"<<n<<"矩阵)[Allocation]:"<<endl;
			for(i=0;i<m;i++)
				for(j=0;j<n;j++){
					cin>>Allocation[i][j];
					if(Allocation[i][j]>Max[i][j])
						flag=1;
					Need[i][j]=Max[i][j]-Allocation[i][j];
				}
				if(flag)
					cout<<"申请的资源大于最大需求量，请重新输入!\n";
		}
		while(flag);
		
		showdata();              //显示各种资源
		safe();                  //用银行家算法判定系统是否安全
		while(choice)
		{
			cout<<"**************银行家算法演示***************"<<endl;
			cout<<"               1:增加资源    "<<endl;
			cout<<"               2:释放资源    "<<endl;
			cout<<"               3:修改资源    "<<endl;
			cout<<"               4:分配资源    "<<endl;
			cout<<"               5:增加作业    "<<endl;
			cout<<"               0:退出系统    "<<endl;
			cout<<"*******************************************"<<endl;
			cout<<"请选择你的操作:";
			cin>>choice;
			switch(choice)
			{
			case 1: addresources();break;
			case 2: delresources();break;
			case 3: changeresources();break;
			case 4: share();break;
			case 5: addprocess();break;
			case 0: choice=0;break;
			default: cout<<"请正确选择操作(0-5)!"<<endl;break;
			}
		}
		return 1;
}
