/*************************************************************************
	> File Name: tujuzhen.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年06月16日 星期二 22时11分42秒
 ************************************************************************/

#include<iostream>
#include<cstdio>
#define MAXV  100
#define INF 32767   
using namespace std;
const int MaxSize=10;
class MGraph {
    public:
        MGraph(int a[],int n, int e);
    public:
        int vertex[MaxSize];
        int arc[MaxSize][MaxSize];
        int vertexNum, arcNum;
};
MGraph::MGraph(int a[],int n,int e) {
    vertexNum = n;
    arcNum = e;
    for(int i = 0; i < vertexNum; i++) {
        vertex[i] = a[i];
    }
    for(int i =0; i < vertexNum; i++) {
        for(int j = 0; j < vertexNum; j++) {
            arc[i][j] = 0;
        }
    }
    for(int k = 0;k <arcNum; k++) {
        int i,j;
        cin >> i >> j;
        arc[i][j] = 1;
        arc[j][i] = 1;
    }
}

void prim(MGraph g,int v)  
{
      int Vlength[MAXV];
      int i, j, k;
      int cloest[MAXV];
      int min;
      for(i=0;i<g.vertexNum;i++)
      {
           Vlength[i]=g.arc[v][i];
           cloest[i]=v;
      }
      for(i=1;i<g.vertexNum;i++)
      {
           min=INF;   
           for(j=0;j<g.vertexNum;j++) 
           {
               if(Vlength[j]!=0&&Vlength[j]<min)
               {
                   min=Vlength[j];
                   k=j;
               }
           }
           printf("结点<%d~~~~~~~%d)    边的权值为:   %d\n",cloest[k],k,min);
           Vlength[k]=0;
           Vlength[cloest[k]]=0;
    for(j=0;j<g.vertexNum;j++)  
           {
               if(g.arc[k][j]!=0 && g.arc[k][j]<Vlength[j])
               {
                   Vlength[j]=g.arc[k][j];
                   cloest[j]=k;
               }
           }
      }
    cout << endl;
}
int main() {
    int n,e;
    cout << "输入顶点数和弧数：";
    cin >> n >> e;
    int a[MAXV];
    for(int i = 0; i < n; i++) {
        a[i] = i;
    }
    MGraph g(a,n,e);
    prim(g,0);
    return 0;
}
