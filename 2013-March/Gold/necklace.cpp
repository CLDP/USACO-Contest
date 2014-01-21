#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    freopen("necklace.in", "r", stdin);
    freopen("necklace.out", "w", stdout);
    string p, q;
    cin >> p >> q;
    int N = p.size(), M = q.size();
    for (int i = 0; i < N; ++i) p[i] -= 'a';
    for (int j = 0; j < M; ++j) q[j] -= 'a';
    
    vector<vector<int> > next(M, vector<int>(26, 0));
    for (int i = 1; i < M; ++i) {
        int prev = next[i - 1][q[i - 1]];
        next[i - 1][q[i - 1]] = i;
        for (int j = 0; j < 26; ++j) next[i][j] = next[prev][j];
    }
    next[M - 1][q[M - 1]] = M;
    
    vector<int> f(M, - N - 1);
    f[0] = 0;
    for (int i = 0; i < N; ++i) {
        vector<int> g = f;
        for (int j = 0; j < M; ++j) {
            int cur = next[j][p[i]];
            if (cur < M) g[cur] = max(g[cur], f[j] + 1);
        }
        f = g;
    }
    
    int ans = 0;
    for (int i = 0; i < M; ++i) ans = max(ans, f[i]);
    cout << N - ans << endl;
    
    return 0;
}
