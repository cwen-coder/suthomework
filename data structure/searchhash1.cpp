/*************************************************************************
	> File Name: searchhash1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年06月17日 星期三 00时48分27秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#define MAX 100
using namespace std;
bool hash(int HashTable[],int k,int n) {
    for(int i = 0; i < n; i++) {
        if(HashTable[(k + i) % n] == 0){
            HashTable[(k +i) % n] = k;
            return true;
        }
    }
    return false;
}
void createHash(int HashTable[],int n){
    int k;
    cin >> k;
    while(k) {
        if(!hash(HashTable,k,n)) {
            cout << "操作失败！";   
        }
        cin >> k;
    }
}
int searchHash(int HashTable[],int k,int n) {
    int j = k % n;
    for(int i = 0; i < n; i++) {
        if(HashTable[j+i] == k) return j+i;
    } 
   
        if(!hash(HashTable,k,n)){
            cout << "插入失败！" << endl;
            return -2;
        }
        return -1; 
    
        
}
int main() {
    
    int HashTable[MAX];
    memset(HashTable,0,sizeof(HashTable));
    int n;
    cout << " 输入表长：";
    cin >> n;
    createHash(HashTable,n);
    for(int i = 0; i < n; i++) {
        cout << HashTable[i] << "  ";
    }
    cout << endl;
    int temp ;
    cout << "输入你要查找的的值,输入０退出：";
    while(cin >> temp && temp) {
        int result = searchHash(HashTable,temp,n);
        if(result >= 0) {
            cout << "查找成功！散列地址为： " << result << endl;
        }else if(result == -2){
           cout << "表可能已满！"<< endl; 
        }else 
            cout <<"查找失败！表中不存在！将其插入！"<< endl;
    cout << "输入你要查找的值，输入０退出：";
    }
    return 0;
}
