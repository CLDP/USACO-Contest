#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 501;

int N, M, T;
int x[MAXN][MAXN], y[MAXN][MAXN];
int d[MAXN * MAXN], f[MAXN * MAXN];

int find(int a) {
    if (a != f[a]) f[a] = find(f[a]);
    return f[a];
}

int Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;
    if (d[a] > d[b]) f[b] = f[a]; else f[a] = f[b];
    d[a] += d[b];
    d[b] = d[a];
    return 0;
}


int bfs(int a, int b, int fa, int s) {
    queue<pair<int, int> > que;
    que.push(make_pair(a, b));
    while (!que.empty()) {
        a = que.front().first;
        b = que.front().second;
        que.pop();
        if (y[a][b] != -1) continue;
        if (find(a * M + b + 1) != fa) continue;
        y[a][b] = s;
        if (a > 0) que.push(make_pair(a - 1, b));
        if (a < N - 1) que.push(make_pair(a + 1, b));
        if (b > 0) que.push(make_pair(a, b - 1));
        if (b < M - 1) que.push(make_pair(a, b + 1));
    }
    return 0;
}


int main() {
    freopen("skilevel.in", "r", stdin);
    freopen("skilevel.out", "w", stdout);
    cin >> N >> M >> T;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) cin >> x[i][j];
    
    set<pair<int, int> > diff;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) {
         if (i < N - 1) diff.insert(make_pair(abs(x[i][j] - x[i+1][j]), (i * M + j) * 2));
         if (j < M - 1) diff.insert(make_pair(abs(x[i][j] - x[i][j+1]), (i * M + j) * 2 + 1));
         y[i][j] = -1;
     }
    
    for (int i = 1; i <= N * M; ++i) {
        d[i] = 1;
        f[i] = i;
    }
    
    for (set<pair<int, int> >::iterator iter = diff.begin(); iter != diff.end(); ++iter) {
        int a, b, c;
        c = iter->second % 2;
        a = iter->second / 2 / M;
        b = iter->second / 2 % M;
        if (c == 0) {
            Union(a * M + b + 1, (a + 1) * M + b + 1);
            if (y[a+1][b] == -1 && d[find((a + 1) * M + b + 1)] >= T) {
                bfs(a + 1, b, find((a + 1) * M + b + 1), iter->first);
            }
        } else {
            Union(a * M + b + 1, a * M + b + 2);
            if (y[a][b+1] == -1 && d[find(a * M + b + 2)] >= T) {
                bfs(a, b + 1, find(a * M + b + 2), iter->first);
            }
        }
        if (y[a][b] == -1 && d[find(a * M + b + 1)] >= T) {
            bfs(a, b, find(a * M + b + 1), iter->first);
        }
    }
    
    long long ans = 0;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) {
         int a;
         cin >> a;
         if (a == 1) ans += y[i][j];
     }
    
    cout << ans << endl;
    
    return 0;
}
