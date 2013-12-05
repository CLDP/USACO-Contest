#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

struct node {
    long long a, b, c, d;
};

int n;
set<long long> x;
vector<node> y;

long long getL(long long p) {
    vector<pair<long long, long long> > z;
    for (int i = 0; i < n; ++i) {
        if (y[i].a <= p && p < y[i].c) z.push_back(make_pair(y[i].b, y[i].d));
    }
    if (z.empty()) return 0;
    
    sort(z.begin(), z.end());
    long long l = z[0].first, r = z[0].second, ans = 0;
    for (int i = 1; i < z.size(); ++i) {
        if (z[i].first <= r) {
            r = max(r, z[i].second);
        } else {
            ans += r - l;
            l = z[i].first;
            r = z[i].second;
        }
    }
    ans += r - l;
    
    return ans;
}

int main() {
    freopen("planting.in", "r", stdin);
    freopen("planting.out", "w", stdout);
    
    cin >> n;
    for (int i = 0; i < n; ++i) {
        node p;
        cin >> p.a >> p.b >> p.c >> p.d;
        if (p.a > p.c) swap(p.a, p.c);
        if (p.b > p.d) swap(p.b, p.d);
        x.insert(p.a);
        x.insert(p.c);
        y.push_back(p);
    }
    
    set<long long>::iterator iter = x.begin();
    long long prev = *iter, len = getL(*iter), ans = 0;
    ++iter;
    while (iter != x.end()) {
        ans += (*iter - prev) * len;
        prev = *iter;
        len = getL(*iter);
        ++iter;
    }
    
    cout << ans << endl;
    
    return 0;
}
