#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 310;

long long X[MAXN], Y[MAXN];
long long D[MAXN][MAXN][2][12];
int ans[MAXN];

int getd(int a, int b, int c) {
    long long A = Y[a] - Y[b];
    long long B = X[b] - X[a];
    long long C = X[a] * Y[b] - X[b] * Y[a];
    if (A * X[c] + B * Y[c] + C > 0) return 1;
    return 0;
}

int main() {
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            string P(N, '.');
            for (int k = 0; k < N; ++k) {
                if (k == i || k == j) continue;
                long long A = Y[i] - Y[j];
                long long B = X[j] - X[i];
                long long C = X[i] * Y[j] - X[j] * Y[i];
                if (A * X[k] + B * Y[k] + C > 0) P[k] = '1'; else P[k] = '0';
            }
            long long t1 = 0, t2 = 0;
            int l = 0;
            for (int k = 0; k < N; ++k) {
                t1 <<= 1;
                t2 <<= 1;
                if (k != 0 && k % 30 == 0) {
                    D[i][j][0][l] = t1;
                    D[i][j][1][l] = t2;
                    t1 = t2 = 0;
                    ++l;
                }
                if (P[k] == '0') t1 += 1;
                if (P[k] == '1') t2 += 1;
            }
            D[i][j][0][l] = t1;
            D[i][j][1][l] = t2;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            for (int k = j + 1; k < N; ++k) {
                int ij = getd(i, j, k);
                int ik = getd(i, k, j);
                int jk = getd(j, k, i);
                int cnt = 0;
                long long temp = 0;
                for (int l = 0; l < (N + 29) / 30; ++l) {
                    temp = D[i][j][ij][l] & D[i][k][ik][l] & D[j][k][jk][l];
                    cnt += __builtin_popcount(temp);
                }
                ++ans[cnt];
            }
        }
    }
    for (int i = 0; i <= N - 3; ++i) cout << ans[i] << endl;
    return 0;
}
