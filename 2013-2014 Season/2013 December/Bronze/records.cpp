#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


map<string, map<string, map<string, int> > > x;

int main() {
    freopen("records.in", "r", stdin);
    freopen("records.out", "w", stdout);
    int n, ans = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string p, q, r;
        cin >> p >> q >> r;
        if (q > r) swap(q, r);
        if (p > q) swap(p, q);
        if (q > r) swap(q, r);
        ++x[p][q][r];
        if (x[p][q][r] > ans) ans = x[p][q][r];
    }
    cout << ans << endl;
    
    return 0;
}
