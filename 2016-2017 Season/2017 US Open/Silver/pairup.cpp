#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int N;
pair<long long, int> X[MAXN];

int main() {
    freopen("pairup.in", "r", stdin);
    freopen("pairup.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> X[i].second >> X[i].first;
    sort(X, X + N);
    long long ans = 0;
    int L = 0, R = N - 1;
    while (L <= R) {
        ans = max(ans, X[L].first + X[R].first);
        if (X[L].second == X[R].second) {
            ++L;
            --R;
            continue;
        }
        if (X[L].second > X[R].second) {
            X[L].second -= X[R].second;
            --R;
        } else {
            X[R].second -= X[L].second;
            ++L;
        }
    }
    cout << ans << endl;

    return 0;
}
