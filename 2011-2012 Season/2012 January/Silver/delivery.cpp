#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;

const int MAXN = 311;
const int INF = 1000000000;

int n;
int mx = 0, my = 0;
int x[MAXN], y[MAXN], dx[MAXN], dy[MAXN];
int f[MAXN][MAXN];


int bfs(int a, int b) {
    memset(f, 0, sizeof(f));
    for (int i = 0; i < n; ++i) 
     if (i != a && i != b) f[x[i]][y[i]] = 1;
     
    queue<pair<int, int> > que;
    que.push(make_pair(x[a], y[a]));
    while (!que.empty()) {
        int c = que.front().first;
        int d = que.front().second;
        que.pop();
        if (c > 0 && f[c-1][d] == 0) {
            f[c-1][d] = f[c][d] + dx[c-1];
            que.push(make_pair(c-1, d));
        }
        if (c < mx && f[c+1][d] == 0) {
            f[c+1][d] = f[c][d] + dx[c];
            que.push(make_pair(c+1, d));
        }
        if (d > 0 && f[c][d-1] == 0) {
            f[c][d-1] = f[c][d] + dy[d-1];
            que.push(make_pair(c, d-1));
        }
        if (d < my && f[c][d+1] == 0) {
            f[c][d+1] = f[c][d] + dy[d];
            que.push(make_pair(c, d+1));
        }
    }
    
    if (f[x[b]][y[b]] == 0) 
        return INF;
    else
        return f[x[b]][y[b]];
}


int main() {
    freopen("delivery.in", "r", stdin);
    freopen("delivery.out", "w", stdout);
    cin >> n;
    set<int> xx, yy;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        xx.insert(x[i]);
        xx.insert(x[i] - 1);
        xx.insert(x[i] + 1);
        yy.insert(y[i]);
        yy.insert(y[i] - 1);
        yy.insert(y[i] + 1);
    }
    
    set<int>::iterator iter = xx.begin();
    int prev = *iter;
    ++iter;
    while (iter != xx.end()) {
        dx[mx] = *iter - prev;
        ++mx;
        prev = *iter;
        ++iter;
    }
    
    iter = yy.begin();
    prev = *iter;
    ++iter;
    while (iter != yy.end()) {
        dy[my] = *iter - prev;
        ++my;
        prev = *iter;
        ++iter;
    }
    
    iter = xx.begin();
    for (int i = 0; i < mx; ++i) {
        for (int j = 0; j < n; ++j)
         if (x[j] == *iter) x[j] = i;
        ++iter;
    }
    
    iter = yy.begin();
    for (int i = 0; i < my; ++i) {
        for (int j = 0; j < n; ++j)
         if (y[j] == *iter) y[j] = i;
        ++iter;
    }
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += bfs(i, (i + 1) % n);
        if (ans >= INF) break;
    }
    
    if (ans > INF) 
        cout << -1 << endl;
    else 
        cout << ans << endl;
    
    return 0;
}
