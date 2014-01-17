#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 501;
const int INF = 1000000000;

struct node {
    int t;
    long long L, C;
};

int N, M, T;
int d[MAXN];
bool z[MAXN];
vector<node> x[MAXN];


int SPFA(int C) {
    for (int i = 1; i <= N; ++i) {
        d[i] = INF;
        z[i] = false;
    }
    d[0] = 0;
    z[0] = true;
    queue<int> que;
    que.push(0);
    
    while (!que.empty()) {
        int t = que.front();
        que.pop();
        for (int i = 0; i < x[t].size(); ++i) {
            if (x[t][i].C < C) continue;
            if (x[t][i].L + d[t] < d[x[t][i].t]) {
                d[x[t][i].t] = x[t][i].L + d[t];
                if (!z[x[t][i].t]) {
                    z[x[t][i].t] = true;
                    que.push(x[t][i].t);
                }
            }
        }
        z[t] = false;
    }
    
    return 0;
}


int main() {
    freopen("mroute.in", "r", stdin);
    freopen("mroute.out", "w", stdout);
    cin >> N >> M >> T;
    
    vector<long long> D;
    for (int i = 0; i < M; ++i) {
        int a, b;
        node p;
        cin >> a >> b >> p.L >> p.C;
        D.push_back(p.C);
        --a; --b;
        p.t = b;
        x[a].push_back(p);
        p.t = a;
        x[b].push_back(p);
    }
    
    sort(D.begin(), D.end());
    D.resize(unique(D.begin(), D.end()) - D.begin());
    
    double ans = 1e20;
    for (int i = 0; i < D.size(); ++i) {
        SPFA(D[i]);
        if (d[N-1] + 1.0 * T / D[i] < ans) ans = d[N-1] + 1.0 * T / D[i];
       // cerr << D[i] << " " << d[N-1]  << endl;
    }
    cout << (int)ans << endl;
    
    return 0;
}
