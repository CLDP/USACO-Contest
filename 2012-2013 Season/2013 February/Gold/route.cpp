#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    freopen("route.in", "r", stdin);
    freopen("route.out", "w", stdout);
    int N, M, R;
    cin >> N >> M >> R;
    vector<int> x(N, 0), y(M, 0);
    for (int i = 0; i < N; ++i) cin >> x[i];
    for (int i = 0; i < M; ++i) cin >> y[i];
    
    vector<pair<int, int> > z(R);
    for (int i = 0; i < R; ++i) cin >> z[i].first >> z[i].second;
    sort(z.begin(), z.end());
    
    vector<long long> ans1(N, 0), ans2(M, 0);
    long long ansT = 0;
    for (int i = 0; i < N; ++i) ansT = max(ansT, ans1[i] = x[i]);
    for (int i = 0; i < M; ++i) ansT = max(ansT, ans2[i] = y[i]);
    for (int i = R - 1; i >= 0; --i) {
        int u = z[i].first - 1, v = z[i].second - 1;
        long long temp1 = x[u] + ans2[v], temp2 = y[v] + ans1[u];
        ans1[u] = max(ans1[u], temp1);
        ans2[v] = max(ans2[v], temp2);
        ansT = max(ansT, max(temp1, temp2));
    }
    
    cout << ansT << endl;
    return 0;
}

