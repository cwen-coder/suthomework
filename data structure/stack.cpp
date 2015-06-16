#include<stdlib.h>
#include<iostream>
using namespace std;
template<class ElemType>class StackSq {
public:
	void AllotStack();
	bool EmptyStack();
	ElemType Peek( );
	ElemType Pop( );
	void Push(ElemType item);
	StackSq(int ms);
	virtual ~StackSq();
private:
	int MaxSize;
	int top;
	ElemType* stack;
};

template<class ElemType>StackSq<ElemType>::StackSq(int ms)
{    if(ms<=0) { cout<<"ms值非法！"<<endl; exit(1); }
     MaxSize=ms;   stack=new ElemType[ms];
   if(!stack)
   { cerr<<"Memory allocation failure!"<<endl;   exit(1);   }
   top=-1;
}
template<class ElemType>StackSq<ElemType>::~StackSq(){
   delete []stack;    stack=0;   top=-1;   MaxSize=0;
}
template<class ElemType>void StackSq<ElemType>::Push(ElemType item){
   if(top==MaxSize-1)  AllotStack(); 
   top++;    stack[top]=item;
}
template<class ElemType>ElemType StackSq<ElemType>::Pop(){
   if(top==-1) { cerr<<"Stack is empty!"<<endl;  exit(1);   }
   top--;   return stack[top+1];
}
template<class ElemType>
ElemType StackSq<ElemType>::Peek(){
   if(top==-1) {cerr<<"Stack is empty!"<<endl;   exit(1); }
   return stack[top];
}
template<class ElemType>bool StackSq<ElemType>::EmptyStack()
{     return top==-1;   }
template<class ElemType>void StackSq<ElemType>::AllotStack(){
    ElemType *p=new ElemType[2*MaxSize];
	MaxSize*=2;
	for(int i=0;i<=top;i++)
		p[i]=stack[i];
	delete []stack;  stack=p;
}
double Compute(char *str){
	StackSq<double> S(5);
	double x,y;  	int i=0;
	while(str[i]){
		if(str[i]==' ')
		{ i++; continue; }
		switch(str[i])
		{
	    	case '+':  x=S.Pop()+S.Pop();  i++;  break;
			case '-': x=S.Pop();  x=S.Pop()-x; 	i++; 	break;
			case '*':	x=S.Pop()*S.Pop(); i++; break;
			case '/': x=S.Pop(); if(x!=0.0)  x=S.Pop()/x; else	{
					cerr<<"Divide by 0!"<<endl;
					exit(1);  	}  	i++;	break;
			default: x=0;  while(str[i]>=48 && str[i]<=57){
					       x=x*10+str[i]-48;  i++;}
				   if(str[i]=='.'){ 
 i++; 	y=0;  double j=10.0;
					while(str[i]>=48 && str[i]<=57)
					{y=y+(str[i]-48)/j;	i++;  j*=10; }
					  x+=y;	}  //if
		}
		S.Push(x);
	}
	if(S.EmptyStack())
	{	cerr<<"Stack is empty!"<<endl;  	exit(1);	}
	x=S.Pop();
	if(S.EmptyStack())  return x;
	else	{cerr<<"expression error!"<<endl; 	exit(1);	}
}
int Precedence(char op);
void Change(char *s1,char *s2){
	StackSq<char> R(5);
	R.Push('@');  int i=0,j=0;  	char ch=s1[i];
	while(ch!='\0')
	{	if(ch==' ') ch=s1[++i];
		else if(ch=='(')
		{  R.Push(ch); ch=s1[++i];  }
		else if(ch==')')	{
			while(R.Peek()!='(')  s2[j++]=R.Pop();
			R.Pop();  ch=s1[++i];
		}
		else if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
		{	char w=R.Peek();
			while(Precedence(w)>=Precedence(ch))
			{
				s2[j++]=w; R.Pop();  w=R.Peek();
			}
			R.Push(ch); ch=s1[++i];
		}
		else
		{ if((ch<'0'||ch>'9') && ch!='.'){
				cout<<"中缀表达式表示错误！"<<endl;
				exit(1);
			}
			while((ch>='0' && ch<='9')||ch=='.'){
				s2[j++]=ch;
				ch=s1[++i];
			}
			s2[j++]=' ';
		}
	}
	ch=R.Pop();
	while(ch!='@'){
		if(ch=='('){
			cerr<<"expression error!"<<endl;
			exit(1);
		}
		else	{
			s2[j++]=ch;
			ch=R.Pop();
		}
	}
	s2[j++]='\0';
}
int Precedence(char op){
	switch(op)
	{
		case '+': case '-':  return 1;
	   case '*': case '/':  return 2;
	   case '(': case '@':
	   default:
		   return 0;
	}
}
double Compute(char *str);
void Change(char *s1,char *s2);
//类的使用
int main()
{
	char a[50],b[50];
	cout<<"输入一个中缀算术表达式：";
	cin.getline(a,50);
	Change(a,b);
	cout<<"中缀:"<<a<<endl;
	cout<<"后缀:"<<b<<endl;
	cout<<"求值:"<<Compute(b)<<endl;
return 0;
}

