#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 1001;

int x[MAXN];

int main() {
    freopen("cowrow.in", "r", stdin);
    freopen("cowrow.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> x[i];
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int prev = -1, num = 0;
        for (int j = 0; j < n; ++j) {
            if (x[j] == x[i]) continue;
            if (x[j] != prev) {
                prev = x[j];
                num = 1;
                ans = max(ans, num);
            } else {
                ++num;
                ans = max(ans, num);
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
