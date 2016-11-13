#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

int ans = 0;
string p[31];
vector<pair<int, int> > x[901];

int SPFA(int s, int n) {
    vector<bool> z(n + 1, false);
    vector<int> d(n + 1, INF);
    z[s] = true;
    d[s] = 0;
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
        int t = que.front();
        que.pop();
        for (int i = 0; i < x[t].size(); ++i) {
            if (d[x[t][i].first] > d[t] + x[t][i].second) {
                d[x[t][i].first] = d[t] + x[t][i].second;
                if (!z[x[t][i].first]) {
                    z[x[t][i].first] = true;
                    que.push(x[t][i].first);
                }
            }
        }
        z[t] = false;
    }
    for (int i = 1; i <= n; ++i) ans = max(ans, d[i]);
    
    return 0;
}


int main() {
    freopen("distant.in", "r", stdin);
    freopen("distant.out", "w", stdout);
    int N, A, B;
    cin >> N >> A >> B;
    for (int i = 0; i < N; ++i) cin >> p[i];
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < N; ++j) {
         if (i > 0) {
             x[i * N + j + 1].push_back(make_pair((i - 1) * N + j + 1, p[i][j] == p[i-1][j] ? A : B));
         }
         if (i < N - 1) {
             x[i * N + j + 1].push_back(make_pair((i + 1) * N + j + 1, p[i][j] == p[i+1][j] ? A : B));
         }
         if (j > 0) {
             x[i * N + j + 1].push_back(make_pair(i * N + j, p[i][j] == p[i][j-1] ? A : B));
         }
         if (j < N - 1) {
             x[i * N + j + 1].push_back(make_pair(i * N + j + 2, p[i][j] == p[i][j+1] ? A : B));
         }
     }
     
    for (int i = 1; i <= N * N; ++i) SPFA(i, N * N);
    cout << ans << endl;
    
    return 0;
}
