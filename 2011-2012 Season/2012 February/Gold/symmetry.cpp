#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

long long getMLine(long long &a, long long &b, long long &c, long long x1, long long y1, long long x2, long long y2) {
    a = 2 * (x1 - x2);
    b = 2 * (y1 - y2);
    c = (y1 + y2) * (y2 - y1) + (x2 - x1) * (x1 + x2);
    return 0;
}

long long getLine(long long &a, long long &b, long long &c, long long x1, long long y1, long long x2, long long y2) {
    a = y2 - y1;
    b = x1 - x2;
    c = y2 * (x2 - x1) - x2 * (y2 - y1);
    return 0;
}

bool check(long long a, long long b, long long c, set<pair<long long, long long> > &x) {
    set<pair<long long, long long> >::iterator iter = x.begin();
    while (iter != x.end()) {
        pair<long long, long long> t;
        long long x1 = iter->first, y1 = iter->second;
        if (((-2 * c - a * x1 - b * y1) * b - (b * x1 - a * y1) * a) % (a * a + b * b) != 0) return false;
        t.second = ((-2 * c - a * x1 - b * y1) * b - (b * x1 - a * y1) * a) / (a * a + b * b);
        if (((-2 * c - a * x1 - b * y1) * a + (b * x1 - a * y1) * b) % (a * a + b * b) != 0) return false;
        t.first = ((-2 * c - a * x1 - b * y1) * a + (b * x1 - a * y1) * b) / (a * a + b * b);
        if (x.find(t) == x.end()) return false;
        ++iter;
    }
    
    return true;
}

int main() {
    freopen("symmetry.in", "r", stdin);
    freopen("symmetry.out", "w", stdout);
    int n;
    cin >> n;
    set<pair<long long, long long> > x;
    vector<pair<long long, long long> > y;
    for (int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        x.insert(make_pair(a, b));
        y.push_back(make_pair(a, b));
    }
    
    vector<bool> z(n, false);
    z[0] = true;
    int ans = 0;
    
    for (int i = 1; i < n; ++i) {
        long long r = y[i].first, s = y[i].second;
        long long a, b, c;
        getMLine(a, b, c, y[0].first, y[0].second, r, s);
        if (check(a, b, c, x)) ++ans;
        
        if (z[i]) continue;
        z[i] = true;
        
        getLine(a, b, c, y[0].first, y[0].second, r, s);
        if (check(a, b, c, x)) ++ans;
        for (int j = 1; j < n; ++j)
         if (a * y[j].first + b * y[j].second + c == 0) z[j] = true;
    }
    
    cout << ans << endl;
    
    return 0;
}
