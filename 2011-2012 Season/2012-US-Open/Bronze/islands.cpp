#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    freopen("islands.in", "r", stdin);
    freopen("islands.out", "w", stdout);
    int n;
    cin >> n;
    vector<pair<int, int> > x;
    vector<bool> z(n, true);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        x.push_back(make_pair(a, i));
    }
    sort(x.begin(), x.end());
    
    int ans = 1, temp = 1;
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && x[j].first == x[i].first) {
            int t = x[j].second;
            z[t] = false;
            if (t > 0 && t < n - 1) {
                if (z[t - 1] && z[t + 1]) ++temp;
                if (!z[t - 1] && !z[t + 1]) --temp;
            } else {
                if (t == 0 && !z[t + 1]) --temp;
                if (t == n - 1 && !z[t - 1]) -- temp;
            }
            ++j;
        }
        ans = max(ans, temp);
        i = j;
    }
    
    cout << ans << endl;
    
    return 0;
}
