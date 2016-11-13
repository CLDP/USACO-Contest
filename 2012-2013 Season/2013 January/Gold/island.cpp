#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 52;
const int INF = 1000000000;

struct node {
    int a, b, d;
};


int N, M, nn;
string p[MAXN];
int x[MAXN][MAXN], y[MAXN][MAXN];
int f[16][16];
int d[1 << 15][15];


int dfs(int a, int b, int K) {
    x[a][b] = K;
    if (a > 0 && p[a-1][b] == 'X' && x[a-1][b] == 0) dfs(a-1, b, K);
    if (a < N-1 && p[a+1][b] == 'X' && x[a+1][b] == 0) dfs(a+1, b, K);
    if (b > 0 && p[a][b-1] == 'X' && x[a][b-1] == 0) dfs(a, b-1, K);
    if (b < M-1 && p[a][b+1] == 'X' && x[a][b+1] == 0) dfs(a, b+1, K);
    return 0;
}


int find(int k) {
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) y[i][j] = 0;
    
    queue<node> que;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) {
         if (p[i][j] != 'S') continue;
         if ((i > 0 && x[i-1][j] == k) || (i < N-1 && x[i+1][j] == k) ||
             (j > 0 && x[i][j-1] == k) || (j < M-1 && x[i][j+1] == k)) {
             node q;
             q.a = i; q.b = j; q.d = 1;
             y[i][j] = 1;
             que.push(q);
         }
     }
     
    while (!que.empty()) {
        node q = que.front();
        que.pop();
        int a = q.a, b = q.b, d = q.d;
        if (p[a][b] == 'X' && x[a][b] != k) {
            f[k][x[a][b]] = min(d-1, f[k][x[a][b]]);
            continue;
        }
        ++q.d;
        if (a > 0 && p[a-1][b] != '.' && x[a-1][b] != k && y[a-1][b] == 0) {
            --q.a;
            y[a-1][b] = q.d;
            que.push(q);
            ++q.a;
        }
        if (a < N-1 && p[a+1][b] != '.' && x[a+1][b] != k && y[a+1][b] == 0) {
            ++q.a;
            y[a+1][b] = q.d;
            que.push(q);
            --q.a;
        }
        if (b > 0 && p[a][b-1] != '.' && x[a][b-1] != k && y[a][b-1] == 0) {
            --q.b;
            y[a][b-1] = q.d;
            que.push(q);
            ++q.b;
        } 
        if (b < M-1 && p[a][b+1] != '.' && x[a][b+1] != k && y[a][b+1] == 0) {
            ++q.b;
            y[a][b+1] = q.d;
            que.push(q);
            --q.b;
        } 
    }
    
    return 0;
}


int main() {
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> p[i];
    
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) {
         if (p[i][j] == 'X' && x[i][j] == 0) dfs(i, j, ++nn);
     }
     
    for (int i = 1; i <= nn; ++i)
     for (int j = 1; j <= nn; ++j) f[i][j] = INF;
     
    for (int k = 1; k <= nn; ++k) find(k);
    
    N = nn;
    for (int i = 1; i <= N; ++i) f[i][i] = 0;
    
    for (int k = 1; k <= N; ++k)
     for (int i = 1; i <= N; ++i)
      for (int j = 1; j <= N; ++j)
       if (f[i][k] + f[k][j] < f[i][j]) f[i][j] = f[i][k] + f[k][j];
    
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < N; ++j) f[i][j] = f[i+1][j+1]; 
    
    for (int i = 0; i < (1 << N); ++i)
     for (int j = 0; j < N; ++j) d[i][j] = INF;
     
    for (int k = 0; k < N; ++k) d[1 << k][k] = 0;
    
    for (int j = 1; j < N; ++j) {
        vector<int> state(N - j, 0);
        for (int i = 0; i < j; ++i) state.push_back(1);
        while (state[0] == 0) {
            int ss = 0;
            for (int i = 0; i < N; ++i) ss += state[i] * (1 << i);
            for (int i = 0; i < N; ++i) {
                if (state[i] == 0) continue;
                if (d[ss][i] == INF) continue;
                for (int l = 0; l < N; ++l) {
                    if (ss & (1 << l)) continue;
                    d[ss + (1 << l)][l] = min(d[ss + (1 << l)][l], d[ss][i] + f[i][l]);
                }
            }
            next_permutation(state.begin(), state.end());
        }
        while (state[0] != 0) {
            int ss = 0;
            for (int i = 0; i < N; ++i) ss += state[i] * (1 << i);
            for (int i = 0; i < N; ++i) {
                if (state[i] == 0) continue;
                if (d[ss][i] == INF) continue;
                for (int l = 0; l < N; ++l) {
                    if (ss & (1 << l)) continue;
                    d[ss + (1 << l)][l] = min(d[ss + (1 << l)][l], d[ss][i] + f[i][l]);
                }
            }
            next_permutation(state.begin(), state.end());
        }
    }
   
    int ansT = INF;
    for (int i = 0; i < N; ++i) ansT = min(ansT, d[(1 << N) - 1][i]);
    cout << ansT << endl;
    
    return 0;
}
