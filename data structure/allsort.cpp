/*************************************************************************
    > File Name: allsort.cpp
    > Author: 
    > Mail: 
    > Created Time: 2015年06月17日 星期三 09时06分49秒
 ************************************************************************/

#include<iostream>
#include<cstdio>
using namespace std;
#define MAX 100
void SelectSort(int a[],int n) {
    for(int i = 0; i < n; i++) {
        int index = i;
        for(int j = i+1; j < n; j++ ) {
            if(a[j] < a[index]) index = j;
        }
        if(index != i) {
            a[i] = a[i] ^ a[index];
            a[index] = a[i] ^ a[index];
            a[i] = a[i] ^ a[index];
        }
    }
}
void InsertSort(int a[],int n) {
    for(int i = 1; i < n; i++) {
        int j;
        int temp = a[i];
        for( j = i - 1; a[j] > temp;j--) {
            a[j+1] = a[j];
            if(j == 0) {
                j--;
                break;
            }
        }
        a[j+1] = temp;
    }
}
void BubbleSort(int a[],int n){
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(a[j] > a[j+1]) {
                a[j] = a[j] ^ a[j+1];
                a[j+1] = a[j] ^ a[j+1];
                a[j] = a[j] ^ a[j+1];
            }
        }
    }
}
void ShellSort(int a[],int n) {
    for(int d = n / 2; d >= 1; d = d / 2) {
        for(int i = d; i < n; i++) {
            int temp = a[i];
            int j;
            for(j = i - d; j >= 0 && temp < a[j]; j = j -d) 
                a[j+d] = a[j];
            a[j+d] = temp;
        }
    }
}
int Partition(int r[],int first,int end){
    int i = first;
    int j = end;
    while(i < j) {
        while(i < j && r[i] <= r[j])j--;
        if(i < j) {
            r[i] = r[i] ^ r[j];
            r[j] = r[i] ^ r[j];
            r[i] = r[i] ^ r[j];
            i++;
        }
        while(i < j && r[i] <= r[j]) i++;
        if(i < j) {
            r[i] = r[i] ^ r[j];
            r[j] = r[i] ^ r[j];
            r[i] = r[i] ^ r[j];
            j--;
        }
    }
    return i;
}
void QuickSort(int a[],int first,int end){
    if(first < end) {
        int pivot = Partition(a,first,end);
        QuickSort(a,first,pivot - 1);
        QuickSort(a,pivot + 1,end);
    }
}
void Sift(int r[],int k,int n) {
    int i = k;
    int j = 2 * i;
    while(j <= n) {
        if(j < n && r[j] < r[j+1]) j++;
        if(r[i] > r[j]) break;
        else {
            r[i] = r[i] ^ r[j];
            r[j] = r[i] ^ r[j];
            r[i] = r[i] ^ r[j];
            i = j;
            j = 2 * i;
        }
    }
}
void HeapSort(int a[],int n) {
    for(int i = n / 2; i >= 1;i--) {
        Sift(a,i,n);
    }
    for(int i = 1; i < n; i++) {
        a[1] = a[1] ^ a[n-i+1];
        a[n-i+1] = a[1] ^ a[n-i+1];
        a[1] = a[1] ^ a[n-i+1];
        Sift(a,1,n-i);
    }
}

void QuickSortND(int a[],int low,int high)  
{  
    if(high-low<1) return;  
    int* stk=new int[high-low+1];  
    int p=0;  
    int l,h,m;  
    stk[p++]=low;  
    stk[p++]=high;  
    while(p!=0)  
    {  
        h=stk[--p];  
        l=stk[--p];  
        if (l<h)  
        {  
            m=Partition(a,l,h);  
            if (m-1>l)  
            {  
                stk[p++]=l;  
                stk[p++]=m-1;  
            }  
            if (m+1<h)  
            {  
                stk[p++]=m+1;  
                stk[p++]=h;  
            }  
        }  
    }  
    delete[] stk;  
}  

int main() {
    int n;
    cout << "数组的长度:";
    int  a[MAX],b[MAX],c[MAX],d[MAX],e[MAX],f[MAX],g[MAX];
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];  
        b[i] = a[i];
        c[i] = a[i];
        d[i] = a[i];
        e[i] = a[i];
        f[i+1] = a[i];
        g[i] = a[i];
    }
    cout << "未排序的数组：";
    for(int i = 0; i < n; i++) printf("%3d",a[i]);
    cout << endl;
    cout << "选择排序后：";
    SelectSort(a,n);
    for(int i = 0; i < n; i++) printf("%3d",a[i]);
    cout << endl;
    cout << "直接插入排序后：";
    InsertSort(b,n);
    for(int i = 0; i < n; i++) printf("%3d",b[i]);
    cout << endl;
    cout << "冒泡排序后：";
    BubbleSort(c,n);
    for(int i = 0; i < n; i++) printf("%3d",c[i]);
    cout << endl;
    cout << "希尔排序后：";
    ShellSort(d,n);
    for(int i = 0; i < n; i++) printf("%3d",d[i]);
    cout << endl;
    cout << "快速排序后：";
    QuickSort(e,0,n-1);
    for(int i = 0; i < n; i++) printf("%3d",e[i]);
    cout << endl;
    cout << "堆排序后：";
    HeapSort(f,n);
    for(int i = 1; i <= n; i++) printf("%3d",f[i]);
    cout << endl;
    cout << "非递归快速排序后：";
    QuickSortND(g,0,n-1);
    for(int i = 0; i < n; i++) printf("%3d",g[i]);
    cout << endl;

    return 0;
}
