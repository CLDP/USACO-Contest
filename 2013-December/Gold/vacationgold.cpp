#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXK = 201;
const int MAXN = 20001;
const int INF = 1000000000;


int N, M, K, Q;
vector<pair<int, int> > x[MAXN], y[MAXN];
int d[MAXK][MAXN], D[MAXK][MAXN];


int SPFA_out(int I, int s) {
    vector<bool> z(N + 1, false);
    for (int i = 1; i <= N; ++i) d[I][i] = INF;
    
    z[s] = true;
    d[I][s] = 0;
    queue<int> que;
    que.push(s);
    
    while (!que.empty()) {
        int a = que.front();
        que.pop();
        for (int i = 0; i < x[a].size(); ++i) {
            if (d[I][x[a][i].first] > d[I][a] + x[a][i].second) {
                d[I][x[a][i].first] = d[I][a] + x[a][i].second;
                if (!z[x[a][i].first]) {
                    z[x[a][i].first] = true;
                    que.push(x[a][i].first);
                }
            }
        }
        z[a] = false;
    }
    
    return 0;
}


int SPFA_in(int I, int s) {
    vector<bool> z(N + 1, false);
    for (int i = 1; i <= N; ++i) D[I][i] = INF;
    
    z[s] = true;
    D[I][s] = 0;
    queue<int> que;
    que.push(s);
    
    while (!que.empty()) {
        int a = que.front();
        que.pop();
        for (int i = 0; i < y[a].size(); ++i) {
            if (D[I][y[a][i].first] > D[I][a] + y[a][i].second) {
                D[I][y[a][i].first] = D[I][a] + y[a][i].second;
                if (!z[y[a][i].first]) {
                    z[y[a][i].first] = true;
                    que.push(y[a][i].first);
                }
            }
        }
        z[a] = false;
    }
    
    return 0;
}

int main() {
    freopen("vacationgold.in", "r", stdin);
    freopen("vacationgold.out", "w", stdout);
    cin >> N >> M >> K >> Q;
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        x[a].push_back(make_pair(b, c));
        y[b].push_back(make_pair(a, c));
    }
    vector<int> H(K, 0);
    vector<int> FH(N + 1, -1);
    for (int i = 0; i < K; ++i) {
        cin >> H[i];
        FH[H[i]] = i;
    }
    
    for (int i = 0; i < K; ++i) {
        SPFA_out(i, H[i]);
        SPFA_in(i, H[i]);
    }
    
    int num = 0, cost = 0;
    for (int i = 0; i < Q; ++i) {
        int a, b;
        cin >> a >> b;
        if (FH[b] != -1) {
            if (D[FH[b]][a] != INF) {
                ++num;
                cost += D[FH[b]][a];
            }
        } else
        if (FH[a] != -1) { 
            if (d[FH[a]][b] != INF) {
                ++num;
                cost += d[FH[a]][b];
            }
        } else
        if (FH[a] == -1) {
            int temp = INF;
            for (int k = 0; k < K; ++k) {
                if (D[k][a] + d[k][b] < temp) temp = D[k][a] + d[k][b];
            }
            if (temp < INF) {
                ++num;
                cost += temp;
            }
        }
    }
    
    cout << num << endl;
    cout << cost << endl;
    
    return 0;
}
