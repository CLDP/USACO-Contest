#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 21;
const int INF = 1000000000;

int n, ans;
int x[MAXN];

int dfs(int t, int a, int b, int c) {
    if (t == n) {
        ans = min(ans, c);
        return 0;
    }
    if (c >= ans) return 0;
    
    if (a + x[t] > c) {
        dfs(t + 1, b, c, a + x[t]);
    } else 
    if (a + x[t] > b) {
        dfs(t + 1, b, a + x[t], c);
    } else {
        dfs(t + 1, a + x[t], b, c);
    }
    
    if (b + x[t] > c) {
        dfs(t + 1, a, c, b + x[t]);
    } else {
        dfs(t + 1, a, b + x[t], c);
    }
    
    dfs(t + 1, a, b, c + x[t]);
    return 0;
}

int main() {
    freopen("baleshare.in", "r", stdin);
    freopen("baleshare.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> x[i];
    sort(x, x+n);
    int total = 0;
    for (int i = 0; i < n; ++i) total += x[i];
    int t1 = 0, t2 = 0, t3 = 0;
    for (int i = 0; i < n; ++i) {
        if (t1 < total / 3) {
            t1 += x[i];
        } else
        if (t2 < total / 3) {
            t2 += x[i];
        } else {
            t3 += x[i];
        }
    }
    ans = max(t1, max(t2, t3));
    
    for (int i = 0; i < n / 2; ++i) swap(x[i], x[n-1-i]);
    
    dfs(0, 0, 0, 0);
    
    cout << ans << endl;
    
    return 0;
}
