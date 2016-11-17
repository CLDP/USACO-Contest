#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int N, A, B;

int main() {
    freopen("cowroute.in", "r", stdin);
    freopen("cowroute.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin >> A >> B >> N;
    int ans = 10000;
    for (int i = 0; i < N; ++i) {
        int C, M, D;
        cin >> C >> M;
        bool L = false, R = false;
        for (int j = 0; j < M; ++j) {
            cin >> D;
            if (D == A) L = true;
            if (D == B && L) R = true;
        }
        if (R) ans = min(ans, C);
    }
    if (ans == 10000) ans = -1;
    cout << ans << endl;
    return 0;
}
