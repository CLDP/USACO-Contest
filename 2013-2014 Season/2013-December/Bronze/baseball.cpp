#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;



int main() {
    freopen("baseball.in", "r", stdin);
    freopen("baseball.out", "w", stdout);
    int n, ans = 0;
    cin >> n;
    vector<int> x(n, 0);
    for (int i = 0; i < n; ++i) cin >> x[i];
    sort(x.begin(), x.end());
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            int left = x[j] + (x[j] - x[i]);
            int right = x[j] + (x[j] - x[i]) * 2;
            int l = lower_bound(x.begin(), x.end(), left) - x.begin();
            int r = upper_bound(x.begin(), x.end(), right) - x.begin();
            ans += r - l;
        }
    }
    cout << ans << endl;
    
    return 0;
}
