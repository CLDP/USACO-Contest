#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1000000000;
const int MAXN = 101;

int n, m;
int x[MAXN][MAXN];
int f[MAXN], d[MAXN];
bool z[MAXN];

int dijkstra(bool root) {
    for (int i = 1; i <= n; ++i) {
        d[i] = INF;
        z[i] = false;
    }
    
    d[1] = 0;
    
    while (true) {
        int a = -1, b = INF;
        for (int j = 1; j <= n; ++j)
         if (!z[j] && d[j] < b) {
             b = d[j];
             a = j;
         }
        if (a == -1) break;
        z[a] = true;
        
        for (int j = 1; j <= n; ++j) 
         if (d[a] + x[a][j] < d[j]) {
             d[j] = d[a] + x[a][j];
             if (root) f[j] = a;
         }
    }
    
    return d[n];
}



int main() {
    freopen("rblock.in", "r", stdin);
    freopen("rblock.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) 
     for (int j = 1; j <= n; ++j)
      if (i != j) x[i][j] = INF;
    
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        x[a][b] = x[b][a] = c;
    }
    
    int len = dijkstra(true);
    int ans = 0;
    int a = n, b = f[n];
    
    while (a != 1) {
        int c = x[a][b];
        x[a][b] = x[b][a] = c * 2;
        int tmp = dijkstra(false);
        if (tmp - len > ans) ans = tmp - len;
        x[a][b] = x[b][a] = c;
        a = b;
        b = f[a];
    }
    
    cout << ans << endl;
    
    return 0;
}
