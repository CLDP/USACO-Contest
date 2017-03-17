#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

string X[510], Y[510];
bool Z[64];

int getI(char C) {
    if (C == 'A') return 0;
    if (C == 'C') return 1;
    if (C == 'G') return 2;
    return 3;
}

int main() {
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> X[i];
    for (int i = 0; i < N; ++i) cin >> Y[i];

    int ans = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = i + 1; j < M; ++j) {
            for (int k = j + 1; k < M; ++k) {
                memset(Z, 0, sizeof(Z));
                for (int l = 0; l < N; ++l) {
                    Z[getI(X[l][i]) * 16 + getI(X[l][j]) * 4 + getI(X[l][k])] = true;
                }
                bool flag = true;
                for (int l = 0; l < N; ++l) {
                    if (Z[getI(Y[l][i]) * 16 + getI(Y[l][j]) * 4 + getI(Y[l][k])]) {
                        flag = false;
                        break;
                    }
                }
                ans += flag;
            }
        }
    }
    cout << ans << endl;

    return 0;
}
