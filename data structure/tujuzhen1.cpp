#include <stdio.h>
#define MAXV  100
#define INF 32767       /*INF表示∞*/
typedef int InfoType;
typedef struct
{   int no;                     
    InfoType info;              
} VertexType;                   
typedef struct                 
{   int edges[MAXV][MAXV];     
    int vexnum,arcnum;         
    VertexType vexs[MAXV];      
} MGraph;                       
 
void DispMat(MGraph g)

{
    int i,j;
    for (i=0;i<g.vexnum;i++)
    {
        for (j=0;j<g.vexnum;j++)
            if (g.edges[i][j]==INF)
                printf("  ∞");
            else
                printf("%3d",g.edges[i][j]);
        printf("\n");
    }
}
 
void prim(MGraph g,int v)  
{
      
      int Vlength[MAXV];
      int i, j, k;
      int cloest[MAXV];
      int min;
      for(i=0;i<g.vexnum;i++)
      {
           Vlength[i]=g.edges[v][i];
           cloest[i]=v;
      }
      for(i=1;i<g.vexnum;i++)
      {
           min=INF;   
           for(j=0;j<g.vexnum;j++) 
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
    for(j=0;j<g.vexnum;j++)  
           {
               if(g.edges[k][j]!=0&&g.edges[k][j]<Vlength[j])
               {
                   Vlength[j]=g.edges[k][j];
                   cloest[j]=k;
               }
           }
      }
}
int main()
{
    int i,j,u=3;
    MGraph g;
    int A[MAXV][11];
    g.vexnum=6;g.arcnum=10;
    for (i=0;i<g.vexnum;i++)
        for (j=0;j<g.vexnum;j++)
            A[i][j]=INF;
    A[0][1]=5;A[0][2]=8;A[0][3]=7;A[0][5]=3;
    A[1][2]=4;
    A[2][3]=5;A[2][5]=9;
    A[3][4]=5;
    A[4][5]=1;
    for (i=0;i<g.vexnum;i++)
        for (j=0;j<g.vexnum;j++)
            A[j][i]=A[i][j];
    for (i=0;i<g.vexnum;i++)     
        for (j=0;j<g.vexnum;j++)
            g.edges[i][j]=A[i][j];
    printf("\n");
    printf("图G的邻接矩阵表示出来:\n");
    DispMat(g);
    printf("\n");
    printf("普里姆算法求解结果:\n");
    prim(g,0);
    printf("\n");
return 0;
}
