#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 210;

string P[MAXN];
int U[MAXN][MAXN];

int main() {
    freopen("fortmoo.in", "r", stdin);
    freopen("fortmoo.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> P[i];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            U[i + 1][j + 1] = U[i][j + 1] + 1;
            if (P[i][j] == 'X') U[i + 1][j + 1] = 0; 
        }
    }
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            int L = -1;
            for (int k = 0; k < M; ++k) {
                if (P[i][k] == 'X' || P[j][k] == 'X') L = -1;
                if (U[j + 1][k + 1] >= j - i + 1) {
                    if (L == -1) L = k;
                    ans = max(ans, (j - i + 1) * (k - L + 1));
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
