#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;


int main() {
    freopen("crowded.in", "r", stdin);
    freopen("crowded.out", "w", stdout);
    int n, d;
    cin >> n >> d;
    vector<pair<int, int> > cow;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        cow.push_back(make_pair(a, b));
    }
    sort(cow.begin(), cow.end());
    
    deque<pair<int, int> > pre;
    vector<int> z(n, 0);
    for (int i = 0; i < n; ++i) {
        if (pre.size() == 0) {
            pre.push_back(cow[i]);
        } else {
            while (!pre.empty() && pre.front().first <  cow[i].first - d) pre.pop_front();
            if (pre.front().second >= 2 * cow[i].second) ++z[i];
            while (!pre.empty() && pre.back().second < cow[i].second) pre.pop_back();
            pre.push_back(cow[i]);
        }
    }
    pre.clear();
    for (int i = n-1; i >= 0; --i) {
        if (pre.size() == 0) {
            pre.push_back(cow[i]);
        } else {
            while (!pre.empty() && pre.front().first >  cow[i].first + d) pre.pop_front();
            if (pre.front().second >= 2 * cow[i].second) ++z[i];
            while (!pre.empty() && pre.back().second < cow[i].second) pre.pop_back();
            pre.push_back(cow[i]);
        }
    }
    
    int ans = 0;
    for (int i = 0; i < n; ++i) ans += (z[i] == 2);
    
    cout << ans << endl;
    
    return 0;
}
