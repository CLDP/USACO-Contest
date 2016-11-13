#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
    long long p, s;
};

bool compare(const node &a, const node &b) {
    return a.p + a.s < b.p + b.s;
}

int main() {
    freopen("gifts.in", "r", stdin);
    freopen("gifts.out", "w", stdout);
    int n;
    long long k;
    cin >> n >> k;
    vector<node> x;
    for (int i = 0; i < n; ++i) {
        node p;
        cin >> p.p >> p.s;
        x.push_back(p);
    }
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        vector<node> xx = x;
        xx[i].p /= 2;
        sort(xx.begin(), xx.end(), compare);
        int j = 0;
        long long kk = k;
        while (kk >= xx[j].p + xx[j].s) {
            kk -= xx[j].p + xx[j].s;
            ++j;
        }
        ans = max(j, ans);
    }
    
    cout << ans << endl;
    
    return 0;
}
