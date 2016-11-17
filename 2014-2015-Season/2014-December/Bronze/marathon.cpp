#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int N;
long long X[MAXN], Y[MAXN];

int main() {
    freopen("marathon.in", "r", stdin);
    freopen("marathon.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin >> N;
    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
        if (i > 0) ans += abs(X[i] - X[i - 1]) + abs(Y[i] - Y[i - 1]);
    }
    long long temp = ans;
    for (int i = 1; i < N - 1; ++i) {
        ans = min(ans, temp + abs(X[i + 1] - X[i - 1]) + abs(Y[i + 1] - Y[i - 1])
                            - abs(X[i] - X[i - 1]) - abs(X[i + 1] - X[i]) 
                            - abs(Y[i] - Y[i - 1]) - abs(Y[i + 1] - Y[i]));
    }
    cout << ans << endl;
    return 0;
}
