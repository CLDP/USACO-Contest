#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const int MAXM = 2010;
const long long INF = 1LL * 100000000 * 100000000;

int N, M;
long long X[MAXM], Y[MAXM];
long long f[MAXN][MAXN][2];
long long D[MAXM][MAXM];

long long dist(int a, int b) {
    return (X[a] - X[b]) * (X[a] - X[b]) + (Y[a] - Y[b]) * (Y[a] - Y[b]);
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);
    cin >> N >> M;
    for (int i = 1; i <= N + M; ++i) cin >> X[i] >> Y[i];
    for (int i = 1; i <= N + M; ++i) {
        for (int j = i + 1; j <= N + M; ++j) {
            D[i][j] = D[j][i] = dist(i, j);
        }
    }
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= M; ++j) f[i][j][0] = f[i][j][1] = INF;
    }
    f[1][0][0] = 0;
    f[1][1][1] = D[1][N + 1];
    for (int j = 2; j <= M; ++j) f[1][j][1] = f[1][j - 1][1] + D[N + j - 1][N + j];

    for (int i = 2; i <= N; ++i) {
        f[i][0][0] = f[i - 1][0][0] + D[i - 1][i];
        for (int j = 1; j <= M; ++j) {
            f[i][j][0] = f[i][j][1] = INF;
            f[i][j][0] = min(f[i][j][0], f[i - 1][j][0] + D[i - 1][i]);
            f[i][j][0] = min(f[i][j][0], f[i - 1][j][1] + D[i][N + j]);
            f[i][j][1] = min(f[i][j][1], f[i][j - 1][0] + D[i][N + j]);
            if (j > 1) f[i][j][1] = min(f[i][j][1], f[i][j - 1][1] + D[N + j - 1][N + j]);
        }
    }
    cout << f[N][M][0] << endl;
    return 0;
}
