#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <stack>
#include <time.h>
#include <numeric>

using namespace std;

using PII = pair<int, int>;

const int N = 1e2 + 10;

int n;
int a[N];

// 线性查找
int liner_search(int x){ 
    // 查找成功返回对应索引，失败返回0
    for (int i = 1; i <= n; i++){
        if(a[i] == x)
            return i;
    }
    return 0;
}

int binary_search(int x){ // 要保证有序
    sort(a + 1, a + 1 + n);
    int l = 1, r = n;
    while(l <= r){
        int mid = l + r >> 1;
        if(x < a[mid])
            r = mid - 1;
        else if(x > a[mid])
            l = mid + 1;
        else
            return mid;
    }
    return 0;
}

int main(){
    srand(int(time(0))); // 设置随机数种子
    cout << "请输入随机数个数:";
    // cin >> n;
    n = 10;
    for (int i = 1; i <= n; i++){
        a[i] = rand() % n + 1; // 生成1~n之间的随机数
        cout << a[i] << ' ';
    }
    cout << endl;
    cout << binary_search(a[3]);
}