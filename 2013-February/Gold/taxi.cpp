#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int N, M;
int x[MAXN], y[MAXN];


int main() {
    freopen("taxi.in", "r", stdin);
    freopen("taxi.out", "w", stdout);
    
    long long ans = 0;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        cin >> x[i] >> y[i];
        ans += abs(x[i] - y[i]);
    }
    x[N] = M;
    y[N] = 0;
    sort(x, x + N + 1);
    sort(y, y + N + 1);
    for (int i = 0; i <= N; ++i) ans += abs(x[i] - y[i]);
    
    cout << ans << endl;
    return 0;
}

