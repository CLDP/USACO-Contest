#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 1010;
const int INF = 1000000009;

int N, M, K;
int X[MAXN], Y[MAXN];
int f[MAXN][MAXN][11];

int main() {
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    cin >> N >> M >> K;
    for (int i = 1; i <= N; ++i) cin >> X[i];
    for (int j = 1; j <= M; ++j) cin >> Y[j];

    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= M; ++j) f[i][j][0] = 1;
    }

    for (int k = 1; k <= K; ++k) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                if (X[i] <= Y[j]) continue;
                f[i][j][k] = f[i - 1][j - 1][k - 1];
            }
        }
        for (int i = 1; i <= N; ++i) {
            int row = 0;
            for (int j = 1; j <= M; ++j) {
                row = (row + f[i][j][k]) % INF;
                f[i][j][k] = (row + f[i - 1][j][k]) % INF;
            }
        }
    }

    cout << f[N][M][K] << endl;
    return 0;
}
