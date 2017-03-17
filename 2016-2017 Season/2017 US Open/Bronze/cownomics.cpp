#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

string X[110], Y[110];
bool Z[200];


int main() {
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> X[i];
    for (int i = 0; i < N; ++i) cin >> Y[i];

    int ans = 0;
    for (int i = 0; i < M; ++i) {
        memset(Z, 0, sizeof(Z));
        bool flag = true;
        for (int j = 0; j < N; ++j) Z[X[j][i]] = true;
        for (int j = 0; j < N; ++j) {
            if (Z[Y[j][i]]) flag = false;
        }
        ans += flag;
    }
    cout << ans << endl;

    return 0;
}
