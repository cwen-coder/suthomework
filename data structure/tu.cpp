/*************************************************************************
	> File Name: tu.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年06月12日 星期五 13时42分20秒
 ************************************************************************/

#include<iostream>
#include<cstdlib>
#define MaxSize 20
using namespace std;
typedef struct ArcNode {
    int adjvex;
    ArcNode *next;
}ArcNode;

struct VertexNode {
    int vertex;
    ArcNode *firstedge;
};
class ALGraph {
    public:
        ALGraph(int a[],int n,int e) ;
        void DFSTraverse(int v);
        void BFSTraverse(int v);
    private:
        VertexNode adjlist[MaxSize];
        int visited[MaxSize];
        int pwrite[MaxSize];
        int vertexNum,arcNum;
};
ALGraph::ALGraph(int a[],int n,int e) {
    ArcNode *s;
    vertexNum = n;
    arcNum = e;
    for(int i =0; i < vertexNum; i++ ) {
        adjlist[i].vertex = a[i];
        adjlist[i].firstedge = NULL;
        visited[i] = 0;
        pwrite[i] = 0;
    }
    for(int k = 0; k < arcNum; k++ ) {
        int i,j;
        cin >> i >> j;
        s = new ArcNode;
        s->adjvex = j;
        s->next = adjlist[i].firstedge; 
        adjlist[i].firstedge = s;
    }
}
void ALGraph::DFSTraverse(int v) {
    ArcNode *stack[arcNum+1];
    int num = 0;
    cout << adjlist[v].vertex;
    visited[v] = 1;
    pwrite[v] = 1;
    ArcNode *p;
    p = adjlist[v].firstedge;
    while(p != NULL || num > 0) {
        while(p != NULL) {
            if(pwrite[p->adjvex] == 0){
                cout << p->adjvex;
                pwrite[p->adjvex] = 1;
                stack[num++] = p; 
                p = p->next;
            }else p = p->next;
        }
        if(num <= 0)break;
        num--;
        p = stack[num];
        int jj = stack[num]->adjvex;
        if(visited[jj] == 0){
            p = adjlist[jj].firstedge;
            visited[jj] = 1;
        }
    }
    cout << endl;
}
void ALGraph::BFSTraverse(int v) {
    int front = -1;
    int rear = -1;
    int Queue[MaxSize];
    cout << adjlist[v].vertex;
    visited[v] = 1;
    pwrite[v] = 1;
    Queue[++rear] = v;
    ArcNode *p;
    while(front != rear){
        v = Queue[++front];
        p = adjlist[v].firstedge; 
        while(p != NULL) {
            int j = p->adjvex;
            if(pwrite[j] == 0) {
                cout << p->adjvex;
                pwrite[j] = 1;
            }
            if(visited[j] == 0){
                Queue[++rear] = j;
                visited[j] = 1;
            }
            p = p->next;
        }
    }
    cout << endl;
}
int main() {
    int n,e;
    int a[MaxSize];
    int b[MaxSize];
    cout << "请输入节点数,边数：";
    cin >> n >> e;
    for(int i = 0; i < n; i++) {
        a[i] = i;
    }
    ALGraph tu(a,n,e);
    int temp;
    cout << "深度优先搜索输入0，广度优先搜索输入1：";
    cin >> temp;
    if(temp == 0) {
        cout << "深度优先非递归遍历：";
        tu.DFSTraverse(0);
    }else if(temp == 1) {
        cout << "广度优先搜索：";
        tu.BFSTraverse(0);
    }else cout << "输入有误" << endl;
    return 0;
}
