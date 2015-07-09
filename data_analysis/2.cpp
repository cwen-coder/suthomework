/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月09日 星期四 08时46分02秒
 ************************************************************************/

#include <iostream>
#include <math.h>
using namespace std;
class SCYT{
public:
	SCYT()
	{
		h=new double[10];
		x=new double[10];
		y=new double[10];
		m=new double[10];//M
		d=new double[10];
		u=new double[10];//μ
		r=new double[10];
		w=new double[10];//追赶法中的u
		z=new double[10];//追赶法中的y
		l=new double[10];//追赶法中的l
		p1=0;p2=0;p3=0;p4=0;
		n=0;
	}
	void Create()
	{
		int i=0;
		cout<<"请输入x的个数：";
		cin>>n;
		cout<<"请输入x的值：";
		for(i=0;i<n;i++)
			cin>>x[i];
		cout<<"请输入y的值：";
		for(i=0;i<n;i++)
			cin>>y[i];
	}
	void Calculate1(double s0,double sn)
	{
		int i;
		for(i=0;i<n-1;i++)//求h
			h[i]=x[i+1]-x[i];
		for(i=1;i<n-1;i++)//求μ
			u[i]=h[i-1]/(h[i-1]+h[i]);
		u[n-1]=1;
		for(i=1;i<n-1;i++)//求
			r[i]=h[i]/(h[i-1]+h[i]);
		r[0]=1;
		d[0]=(6*((y[0]-y[1])/(x[0]-x[1])-s0))/h[0];
		d[n-1]=(6*(sn-(y[n-2]-y[n-1])/(x[n-2]-x[n-1])))/h[n-2];
		for(i=1;i<n-1;i++)//求d
		{
			d[i]=(6*((y[i]-y[i+1])/(x[i]-x[i+1])-(y[i-1]-y[i])/(x[i-1]-x[i])))/(h[i-1]+h[i]);
		}
	
		w[0]=2;z[0]=d[0];
		for(i=1;i<n;i++)//追赶法
		{
			l[i]=u[i]/w[i-1];
			w[i]=2-l[i]*r[i-1];
			z[i]=d[i]-l[i]*z[i-1];
		}
		m[n-1]=z[n-1]/w[n-1];
		for(i=n-2;i>=0;i--)
		{
			m[i]=(z[i]-r[i]*m[i+1])/w[i];
		}
		for(i=0;i<n-1;i++)
		{
			p1=m[i+1]/(6*h[i])-m[i]/(6*h[i]);//x^3的系数
			p2=m[i]*x[i+1]*3/(6*h[i])-m[i+1]*3*x[i]/(6*h[i]);//x^2的系数
			p3=m[i+1]*3*x[i]*x[i]/(6*h[i])-m[i]*(3*x[i+1]*x[i+1])/(6*h[i])-(y[i]-m[i]*h[i]*h[i]/6)/h[i]+(y[i+1]-m[i+1]*h[i]*h[i]/6)/h[i];//x的系数
			p4=m[i]*x[i+1]*x[i+1]*x[i+1]/(6*h[i])-m[i+1]*x[i]*x[i]*x[i]/(6*h[i])+(y[i]-m[i]*h[i]*h[i]/6)*x[i+1]/h[i]-(y[i+1]-m[i+1]*h[i]*h[i]/6)*x[i]/h[i];//常数
			cout<<"s"<<i+1<<"="<<p1<<"*x^3+"<<p2<<"*x^2+"<<p3<<"*x+"<<p4;
			cout<<"   x∈["<<x[i]<<","<<x[i+1]<<"]"<<endl;
		}
	}
	void Calculate2()
	{
		int i;
		for(i=0;i<n-1;i++)//求h
			h[i]=x[i+1]-x[i];
		for(i=1;i<n-1;i++)//求μ
			u[i]=h[i-1]/(h[i-1]+h[i]);
		u[n-1]=0;
		for(i=1;i<n-1;i++)//求
			r[i]=h[i]/(h[i-1]+h[i]);
		r[0]=0;
		d[0]=0;
		d[n-1]=0;
		for(i=1;i<n-1;i++)//求d
		{
			d[i]=(6*((y[i]-y[i+1])/(x[i]-x[i+1])-(y[i-1]-y[i])/(x[i-1]-x[i])))/(h[i-1]+h[i]);
		}
	
		w[0]=2;z[0]=d[0];
		for(i=1;i<n;i++)//追赶法
		{
			l[i]=u[i]/w[i-1];
			w[i]=2-l[i]*r[i-1];
			z[i]=d[i]-l[i]*z[i-1];
		}
		m[n-1]=0;
		m[0]=0;
		for(i=n-2;i>0;i--)
		{
			m[i]=(z[i]-r[i]*m[i+1])/w[i];
		}
		for(i=0;i<n-1;i++)
		{
			p1=m[i+1]/(6*h[i])-m[i]/(6*h[i]);//x^3的系数
			p2=m[i]*x[i+1]*3/(6*h[i])-m[i+1]*3*x[i]/(6*h[i]);//x^2的系数
			p3=m[i+1]*3*x[i]*x[i]/(6*h[i])-m[i]*(3*x[i+1]*x[i+1])/(6*h[i])-(y[i]-m[i]*h[i]*h[i]/6)/h[i]+(y[i+1]-m[i+1]*h[i]*h[i]/6)/h[i];//x的系数
			p4=m[i]*x[i+1]*x[i+1]*x[i+1]/(6*h[i])-m[i+1]*x[i]*x[i]*x[i]/(6*h[i])+(y[i]-m[i]*h[i]*h[i]/6)*x[i+1]/h[i]-(y[i+1]-m[i+1]*h[i]*h[i]/6)*x[i]/h[i];//常数
			cout<<"s"<<i+1<<"="<<p1<<"*x^3+"<<p2<<"*x^2+"<<p3<<"*x+"<<p4;
			cout<<"   x∈["<<x[i]<<","<<x[i+1]<<"]"<<endl;
		}
	}
private:
	double *h;
    double *x;
    double *y;
    double *m;
    double *d;
    double *u;
	double *w;
	double *l;
	double *z;
	double *r;
	double p1,p2,p3,p4;
	int n;
};
int main()
{
	int i;
	char c='y';
	double s0,sn;
	SCYT s;
	s.Create();
	while(c=='y')
	{
	cout<<"请选择条件："<<endl;
	cout<<"1、已知s'0和s'n。"<<endl;
	cout<<"2、已知s”0=s”n=0。"<<endl;
	cin>>i;
	switch(i)
	{
	case 1:
		{
			cout<<"请输入s'0和s'n的值：";
			cin>>s0>>sn;
			s.Calculate1(s0,sn);
		}break;
	case 2:
		{
			s.Calculate2();
		}break;
	}
	cout<<"是否继续？是按y，否则按任意键结束。";
	cin>>c;
	}
	return 0;
}
/*

x	 0.25	0.30	0.39	0.45	0.53
f(x) 0.5000 0.5477  0.6245	0.6708	0.7280
(1).S`(0.25) = 1.0000	 S`(0.53) = 0.6868
(2).S``(0.25) = S``(0.53) = 0

5
0.25	0.30	0.39	0.45	0.53
0.5000 0.5477  0.6245	0.6708	0.7280
1
1.0000 0.6868
y
2


*/

