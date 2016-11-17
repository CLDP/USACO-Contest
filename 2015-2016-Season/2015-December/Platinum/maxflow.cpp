#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 50010;

vector<int> X[MAXN];
int f[MAXN][20], d[MAXN][20], g[MAXN];

void dfs(int a, int fa, int d) {
    f[a][0] = fa;
    for (int j = 1; j < 20; ++j) f[a][j] = f[f[a][j - 1]][j - 1];
    g[a] = d;
    for (int i = 0; i < X[a].size(); ++i) {
        if (X[a][i] == fa) continue;
        dfs(X[a][i], a, d + 1);
    }
}

int LCA(int a, int b) {
    if (g[a] < g[b]) return LCA(b, a);
    int da = g[a], db = g[b];
    for (int i = 19; i >= 0; --i) {
        if (da - (1 << i) >= db) {
            da -= (1 << i);
            a = f[a][i];
        }
    }
    if (a == b) return a;

    for (int i = 19; i >= 0; --i) {
        if (f[a][i] == f[b][i]) continue;
        a = f[a][i];
        b = f[b][i];
    }
    return f[a][0];
}

void update(int a, int b) {
    int c = LCA(a, b);
    int D = g[a] - g[c];
    for (int i = 19; i >= 0; --i) {
        if (D - (1 << i) >= 0) {
            ++d[a][i];
            a = f[a][i];
            D -= (1 << i);
        }
    }

    D = g[b] - g[c];
    for (int i = 19; i >= 0; --i) {
        if (D - (1 << i) >= 0) {
            ++d[b][i];
            b = f[b][i];
            D -= (1 << i);
        }
    }
    ++d[c][0];
}

void check(int a, int &ans) {
    for (int i = 0; i < X[a].size(); ++i) {
        if (X[a][i] == f[a][0]) continue;
        check(X[a][i], ans);
    }
    int temp = 0;
    for (int i = 0; i < 20; ++i) temp += d[a][i];
    ans = max(ans, temp);
    for (int i = 1; i < 20; ++i) {
        if (d[a][i] == 0) continue;
        int c = f[a][0];
        for (int j = i - 1; j >= 0; --j) {
            d[c][j] += d[a][i];
            c = f[c][j];
        }
    }
}

int main() {
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    for (int i = 1; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        X[a].push_back(b);
        X[b].push_back(a);
    }
    dfs(1, 1, 0);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        update(a, b);
    }

    int ans = 0;
    check(1, ans);
    cout << ans << endl;
    return 0;
}
