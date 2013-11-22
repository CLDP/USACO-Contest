#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;


int n, k;
int f[(1 << 17) - 1];
bool z[(1 << 17) - 1];
vector<int> x, y;

int dp(int a) {
    if (z[a]) return f[a];
    z[a] = true;
    for (int i = 0; i < k; ++i) 
     if (a & (1 << i)) {
         int temp = dp(a ^ (1 << i));
         f[a] = max(f[a], (int)(upper_bound(y.begin(), y.end(), y[temp] + x[i]) - y.begin() - 1));
     }
     
    return f[a];
}


int main() {
    freopen("nochange.in", "r", stdin);
    freopen("nochange.out", "w", stdout);
    cin >> k >> n;
    
    x = vector<int>(k, 0);
    y = vector<int>(n+1, 0);
    
    for (int i = 0; i < k; ++i) cin >> x[i];
    for (int j = 1; j <= n; ++j) {
        cin >> y[j];
        y[j] += y[j-1];
    }
    
    int ans = -1;
    for (int i = 0; i < (1 << k); ++i) {
        if (!z[i]) dp(i);
        if (f[i] == n) {
            int temp = 0;
            for (int j = 0; j < k; ++j)
             if (!(i & (1 << j))) temp += x[j];
            if (temp > ans) ans = temp;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
