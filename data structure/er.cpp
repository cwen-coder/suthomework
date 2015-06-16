/*************************************************************************
	> File Name: er.cpp
	> Author:CWen_Yin 
	> Mail: 
	> Created Time: 2015年06月11日 星期四 22时33分56秒
 ************************************************************************/

#include<iostream>
#include<cstdlib>
#define STACK_SIZE 100
using namespace std;
typedef struct BiNode {
    char data;
    struct BiNode *leChild;
    struct BiNode *riChild;
}BiNode,*BiRoot;
BiRoot biRoot;
char ch;
int num = 0;
int depth = 0;

void CreateTree(BiRoot &T) {
    cin >> ch;
    if(ch == '0') T = NULL;
    else {
        T = (BiRoot)malloc(sizeof(BiNode));
        T->data = ch;
        CreateTree(T->leChild);
        CreateTree(T->riChild);
    }
    return ;
}

void InOrder(BiRoot &T) {
    if(T == NULL) return;
    else {
        InOrder(T->leChild);
        cout << T->data;
        InOrder(T->riChild);
    }
}
void InOrderNoRec(BiRoot &T) {
    BiNode *p = T;
    int num = 0;
    BiNode *stack[30];
    while(p != NULL || num > 0)  {
        while(p != NULL ) {
            stack[num++] = p;
            p = p->leChild;
        }
        num--;
        p = stack[num];
        cout << p->data;
        p = p->riChild;
    }
    cout << endl;
}
void PreOrderNoRec(BiRoot &T) {
    BiNode *p = T;
    int num = 0;
    BiNode *stack[30];
    while(p != NULL || num > 0)  {
        while(p != NULL ) {
            cout << p->data;
            stack[num++] = p;
            p = p->leChild;
        }
        num--;
        p = stack[num];
        p = p->riChild;
    }
    cout << endl;
}

void PostOrderNoRec(BiRoot &T) {
    BiNode *p = T;
    BiNode *stack[30];
    int num = 0;
    BiNode *have_visited = NULL;
    while(p != NULL || num > 0) {
        while(p!= NULL) {
            stack[num++] = p;
            p = p->leChild;
        }
        p = stack[num -1];
        if(p->riChild == NULL || have_visited == p->riChild) {
            num--; 
            cout << p->data;
            have_visited = p;
            p = NULL;
        }else {
            
            p = p->riChild;
        }
    }
    cout << endl;
}
int countLeaves(BiRoot T) {
    if(T) {
        if(!T->leChild && !T->riChild)num++;
        countLeaves(T->leChild);
        countLeaves(T->riChild);
    }
    return num;
}
int countDepth(BiRoot T){
        if(T==NULL)return 0;
    else{
                int depth1 = countDepth(T->leChild);// 左子树的深度
                int depth2 = countDepth(T->riChild);// 右子树的深度
                if(depth1>depth2) depth = depth1+1; 
                else depth = depth2+1;
                return depth;
            
    }

}
int main() {
    cout << "建立二叉链表：" ;
    CreateTree(biRoot);
    cout << "中序递归遍历：";
    InOrder(biRoot);
    cout << endl;
    cout << "中序非递归遍历：";
    InOrderNoRec(biRoot);
    cout << "前序非递归遍历：";
    PreOrderNoRec(biRoot);
    cout << "后序非递归遍历："; 
    PostOrderNoRec(biRoot);
    cout << "二叉树的高度：" << countDepth(biRoot) << endl;
    cout << "二叉树的叶子个数：" << countLeaves(biRoot) << endl;
    return 0;
}

