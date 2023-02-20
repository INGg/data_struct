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

// 插入排序
// 描述：从前往后循环插入比当前元素在他前面的那些元素他应该在的位置上
// 特点：前一部分是有序的，但不一定是最终的顺序
// 时间复杂度：最好O(n)，平均O(n^2)，最坏O(n^2)
// 空间复杂度：O(1)
// 稳定
void insert_sort(int a[]){
    for (int i = 2; i <= n; i++){
        a[0] = a[i]; // 哨兵
        int j = i;
        while(j > 1 && a[j - 1] > a[0]){ // 移动元素
            a[j] = a[j - 1];
            j--;
        }
        a[j] = a[0];
    }
}

// 折半插入排序
// 描述：在插入排序的基础上，找元素在的位置上使用二分查找来确定，但是移动的个数是不变的
// 二分找第一个比当前元素大的元素
// 稳定
void binary_search_insert_sort(int a[]){
    for (int i = 2; i <= n; i++){
        if(a[i - 1] <= a[i]) // 可能前面找不到
            continue;
        a[0] = a[i]; // 哨兵
        int l = 1, r = i - 1;
        while (l < r){ // 二分找位置
            int mid = (l + r) >> 1;
            if(a[mid] > a[0])
                r = mid;
            else
                l = mid + 1;
        }
        // 移动元素
        for (int j = i - 1; j >= r; j--){
            a[j + 1] = a[j];
        }
        a[l] = a[0];
    }
}

// 冒泡排序
// 描述：基于交换的排序，每次循环都会从最后开始（也不一定是最后）把这个序列中前几小的元素冒到前面，他的前面是有序的
// 特点：若其中一次没有发生交换那就说明已经是有序的了；每一轮都会按照次序确定一个元素的最终位置
// 时间复杂度：最好O(n)，平均O(n^2)，最坏O(n^2)
// 空间复杂度：O(1)
// 最坏比较次数：n(n-1)/2 交换次数：3n(n-1)/2
// 稳定
void bubble_sort(int a[]){
    for (int i = 1; i <= n; i++){
        int flag = 0;
        for (int j = n; j > i; j--){
            if(a[j] < a[j - 1]){ // 逆序就交换
                flag = 1;
                swap(a[j], a[j - 1]);
            }
        }
        if(!flag) // 已经有序了
            break;
    }
}

// 简单选择排序
// 描述：每一次找到没在位置上的最小的元素，第n次迭代把第i小的元素放在i位置上
// 时间复杂度：最好O(n^2)，平均O(n^2)，最坏O(n^2)
// 空间复杂度：O(1)
// 不稳定
// 支持链式存储
void select_sort(int a[]){
    for (int i = 1; i < n; i++){
        int k = i;
        for (int j = i + 1; j <= n; j++){ // 从未排序的中找出最小的
            if(a[j] < a[k]){ // 找最小的元素
                k = j;
            }
        }
        swap(a[i], a[k]); // 放到他应该在的位置上
    }
}

// 希尔排序
// 描述：选取增量d，来划分组，组内用插入排序，每一轮增量减一（可以定义定义一个任意的递减序列，
// 最后一个一定是1）
// 特点：对于部分有序（基本有序）的序列，使用插入排序效果很好；在每次排序完成后，组内是有序的
// 时间复杂度：O(n^2) O(n sqrt(n))
// 空间复杂度：O(1)
// 不支持链式结构
void shell_sort(int a[]){
    for (int d = n / 2; d; d /= 2){ // 选取增量
        for (int start = 1; start <= d; start ++){ // 每个组起点
            for (int i = start + d; i <= n; i += d){ // 对每个组进行插入排序
                a[0] = a[i]; // 哨兵
                int j = i;
                while(j > start && a[j - d] > a[0]){
                    a[j] = a[j - d];
                    j -= d;
                }
                a[j] = a[0];
            }
        }
    }
}

// 快速排序
// 描述：随机找一个分界点，将整个数组划分成两端，使得左边一段小于x，右边一段大于等于x
//       递归处理左右两边
void quick_sort(int l, int r)  // 快速排序
{
    if (l >= r) return;
    int i = l - 1, j = r + 1;
    int x = a[(l + r) >> 1];
    while (i < j){
        do i++; while (a[i] < x); // 寻找左边的比x小的位置
        do j--; while (a[j] > x); // 寻找右边的比x大的位置
        if (i < j) swap(a[i], a[j]); // 交换使得满足快速排序的定义
    }
    // 递归处理没有排好序的部分
    quick_sort(l, j);
    quick_sort(j + 1, r);
}

// 归并排序
int tmp[N]; // 归并排序辅助数组
void merge_sort(int a[]){
    // 归并排序的归并操作
    auto merge = [&](int l, int r){
        int mid = (l + r) >> 1;
        int i = l, j = mid + 1;
        int o = 0;
        while (i <= mid && j <= r){
            if (a[i] <= a[j]) 
                tmp[o++] = a[i++];
            else 
                tmp[o++] = a[j++];
        }

        while (i <= mid) 
            tmp[o++] = a[i++];
        while (j <= r)
            tmp[o++] = a[j++];

        for (int i = l, j = 0; j < o; j++, i++)
            a[i] = tmp[j];
    };

    // 建立两个栈，使每个区间按照递归顺序入栈出栈
    stack<pair<int, int>> st1; // 待处理区间的栈
    stack<pair<int, int>> st2; // 最终递归顺序的栈
    st1.push({1, n}); // 把要处理的最长的区间长度放入栈中
    while(st1.size()){
        auto t = st1.top();
        st1.pop();

        st2.push(t); // 按照递归顺序放到st2中
        if(t.first == t.second) // 长度为1的就不用放了
            continue;
        int mid = (t.first + t.second) >> 1; // 左右两边放到待处理的栈中
        st1.push({t.first, mid}), st1.push({mid + 1, t.second});
    }

    while(st2.size()){
        // cout << st2.top().x << ' ' << st2.top().second << endl;
        auto t = st2.top();
        st2.pop();
        merge(t.first, t.second);
    }
}

// 堆排序
struct heap{
    int sz; // 堆的大小
    int h[N]; // 堆数组

    int top(){
        return h[1];
    }

    int size(){
        return sz;
    }

    void down(int u){ // 堆的下放操作
        int t = u; // 当前节点
        if(u << 1 <= sz && h[u << 1] < h[t]) // 看看左儿子是不是比当前节点大
            t = u << 1;
        if((u << 1 | 1) <= sz && h[u << 1 | 1] < h[t]) // 看看右儿子是不是比当前节点大
            t = (u << 1 | 1);
        if(u != t){ // 交换节点并递归更新整个子树
            swap(h[u], h[t]);
            down(t);
        }
    }

    void up(int u){
        while(u / 2 && h[u / 2] > h[u]){
            swap(h[u / 2], h[u]);
            u /= 2;
        }
    }

    void push(int x){
        h[++sz] = x;
        up(sz);
    }

    void pop(){
        if(sz){
			h[1] = h[sz];
			sz--;
			down(1);
		}
    }

    heap(int _h[]){
        for (int i = 1; i <= n; i++)
            h[i] = _h[i];
        sz = n; // 确定一开始树的大小
        for (int i = n / 2; i; i--)
            down(i);
    }
};


int main(){
    srand(int(time(0))); // 设置随机数种子
    cout << "请输入随机数个数:";
    cin >> n;
    for (int i = 1; i <= n; i++){
        a[i] = rand() % n + 1; // 生成1~n之间的随机数
    }
    // insert_sort(a); // 插入排序
    // binary_search_insert_sort(a); // 折半插入排序
    // bubble_sort(a); // 冒泡排序
    // select_sort(a); // 选择排序
    // shell_sort(a); // 希尔排序
    // radix_sort(10, 10); // 基数排序
    // merge_sort(a); // 归并排序
    // auto h = heap(a);  // 堆排序
    // while(h.size()){
    //     cout << h.top() << ' ';
    //     h.pop();
    // }
    

    for (int i = 1; i <= n; i++){
        cout << a[i] << ' ';
    }
}