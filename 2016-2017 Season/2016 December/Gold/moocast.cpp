#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

int N;
long long X[MAXN], Y[MAXN];
long long dist[MAXN][MAXN];
bool Z[MAXN];

long long ddist(int a, int b) {
    return (X[a] - X[b]) * (X[a] - X[b]) + (Y[a] - Y[b]) * (Y[a] - Y[b]);
}

int dfs(int a, long long D) {
    Z[a] = true;
    for (int i = 0; i < N; ++i) {
        if (!Z[i] && dist[a][i] <= D) dfs(i, D);
    }
    return 0;
}

bool check(long long D) {
    memset(Z, 0, sizeof(Z));
    dfs(0, D);
    for (int i = 0; i < N; ++i) {
        if (!Z[i]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];
    if (N == 1) {
        cout << 0 << endl;
        return 0;
    }
    long long L = 0, R = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            dist[i][j] = dist[j][i] = ddist(i, j);
            R = max(R, dist[i][j]);
        }
    }
    while (L + 1 < R) {
        long long mid = (L + R) >> 1;
        if (check(mid)) R = mid; else L = mid;
    }
    cout << R << endl;
    return 0;
}
