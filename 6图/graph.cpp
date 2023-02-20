#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <time.h>
#include <numeric>

using namespace std;

using PII = pair<int, int>;

const int N = 1e2 + 10;
const int M = 1e2 + 10;

int n;
int a[N];

template<class T>
class MGraph
{
public:
    MGraph(T a[], int n, int e){
        v_num = n, e_num = e;
        for (int i = 0; i < n; i++){
            v[i] = a[i];
        }
        memset(g, 0, sizeof(n * n));
        for (int i = 1; i <= n; i++){
            int x, y;
            // int z; // 权值
            cin >> x >> y;
            g[x][y] = g[y][x] = 1;
        }
    }
    void DFS(){
        memset(vis, 0, sizeof(bool) * n);
        for (int i = 0; i < v_num; i++){
            if(!vis[i])
                dfs(i);
        }
    }
    void BFS(){
        memset(vis, 0, sizeof(bool) * n);
        for (int i = 0; i < v_num; i++){
            if(!vis[i])
                bfs(i);
        }
    }
private:
    T v[N];
    int g[N][N];
    int v_num, e_num;
    bool vis[N];
    void dfs(int v){
        // work(v) // 在这个节点需要的工作
        vis[v] = 1;
        for (int i = 0; i < v_num; i++){
            if(g[v][i] && !vis[i]){
                dfs(i);
            }
        }
    }

    void bfs(int v){
        queue<int> q;
        q.push(v);
        while(q.size()){
            auto t = q.top();
            q.pop();
            
            for (int i = 0; i < n; i++){
                if(g[t][i] && !vis[i]){
                    // work(i) // BFS中要做的事情

                    vis[t] = 1;
                    q.push(i);
                }
            }
        }
    }
};

