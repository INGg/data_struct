#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <numeric>
#include <sstream>
#include <unordered_map>
#define ll long long
#define ull unsigned long long
#define re return
#define pb push_back
#define Endl "\n"
#define endl "\n"
#define x first
#define y second
#define all(x) (x).begin(),(x).end()

using namespace std;

using PII = pair<int, int>;

const int N = 1e5 + 10;
const int M = 1e5 + 10;
const int mod = 1000000007;
const int INF = 0x3f3f3f3f;

int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

int T;

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
        while(j > 1 && a[j - 1] > a[0]){
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
        while (l < r){ // 找位置
            int mid = l + r >> 1;
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
            if(a[j] < a[j - 1]){
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
        for (int j = i + 1; j <= n; j++){
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
    for (int d = n / 2; d; d /= 2){
        for (int start = 1; start <= d; start ++){
            for (int i = start + d; i <= n; i += d){
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
    int x = a[(l + r) / 2];
    while (i < j){
        do i ++ ; while (a[i] < x);
        do j -- ; while (a[j] > x);
        if (i < j) swap(a[i], a[j]);
    }
    quick_sort(l, j);
    quick_sort(j + 1, r);
}

// 归并排序
int tmp[N];
// void merge_sort(int l, int r){
//     if(l >= r)
//         return;
//     int mid = l + r >> 1;
//     merge_sort(l, mid), merge_sort(mid + 1, r);
//     int i = l, j = mid + 1, k = 0;
//     while(i <= mid && j <= r){
//         if(a[i] <= a[j]) // 等于放在这里保证稳定性
//             tmp[k++] = a[i++];
//         else{
//             tmp[k++] = a[j++];
//         }
//     }
//     while(i <= mid)
//         tmp[k++] = a[i++];
//     while(j <= r)
//         tmp[k++] = a[j++];
//     for (int i = l, j = 0; j < k; i++, j++)
//         a[i] = tmp[j];
// }

void merge_sort(){
    for (int k = 0; 1 << k < n; k++){
        for (int l = 1; l + (1 << k) <= n; l += (1 << k | 1)) {
            int r = min(l + (1 << k | 1), n);
            int mid = l + r >> 1;
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
            
        }
        for (int i = 1; i <= n; i++){
            cout << a[i] << ' ';
        }
    }
}

// 堆排序
struct heap{
    int sz; // 堆的大小
    int tr[N];

    int top(){
        return tr[1];
    }

    void down(int u){ // 堆的下放操作
        int t = u; // 当前节点
        if(u << 1 <= sz && a[u << 1] > a[t]) // 看看左儿子是不是比当前节点大
            t = u << 1;
        if(u << 1 | 1 <= sz && a[u << 1 | 1] > a[t]) // 看看右儿子是不是比当前节点大
            t = u << 1 | 1;
        if(u != t){ // 交换节点并递归更新整个子树
            swap(a[u], a[t]);
            down(t);
        }
    }

    void up(int u){
        while(u / 2 && a[u / 2] > a[u]){
            swap(a[u / 2], a[u]);
            u /= 2;
        }
    }

    void push(int x){
        a[++sz] = x;
        up(sz);
    }

    void heap_sort(){ 
        sz = n; // 确定一开始树的大小
        for (int i = n / 2; i; i--)
            down(i);
        for (int i = 1; i <= n; i++){ // 输出并删除元素
            swap(a[1], a[sz]);
            sz--;
            down(1);
        }
    }
};

// 基数排序
int s[N];
int w[N];
void radix_sort(int d, int r){ // 关键字（在r进制下要排序的数化成r进制最多有多少位）的个数，r进制
    int radix = 1;
    for (int i = 1; i <= d; i ++){
        for (int j = 0; j < r; j++)
            s[j] = 0;
        for (int j = 1; j <= n; j++)
            s[a[j] / radix % r]++;
        for (int j = 1; j < r; j++)
            s[j] += s[j - 1];
        for (int j = n; j >= 1; j--)
            w[s[a[j] / radix % r]--] = a[j];
        for (int j = 1; j <= n; j++)
            a[j] = w[j];
        radix *= r;
    }
    /*
    s[i]是小于i的数的个数

    从推导过程中看，a[i]应该放在s[a[i]]-1的位置上，
    但是如果说要放到1~n的下标上是会出错的，因为进制是有0出现的，会放到错误的位置上去

    所以结果应为(--s[a[j] / radix % r]) + 1，即s[a[j] / radix % r]--

    如果想降序排序，那么根据s的定义对s求后缀和，然后再从后往前确认位置即可
    */
}

// 支持链式存储
void solve(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    // insert_sort(a); // 插入排序
    // binary_search_insert_sort(a); // 折半插入排序
    // bubble_sort(a); // 冒泡排序
    // select_sort(a); // 选择排序
    // shell_sort(a); // 希尔排序
    // radix_sort(10, 10); // 基数排序
    merge_sort();
    for (int i = 1; i <= n; i++){
        cout << a[i] << ' ';
    }
}

int main(){
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    T = 1;
    // cin >> T;
    while(T--){
        solve();
    } 
}