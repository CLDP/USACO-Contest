#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

struct coupons {
    long long p, c;
};

bool compare(const coupons &a, const coupons &b) {
    if (a.c != b.c) return a.c < b.c;
    return a.p < b.p;
}

int main() {
    freopen("coupons.in", "r", stdin);
    freopen("coupons.out", "w", stdout);
    
    int n, k;
    long long m;
    cin >> n >> k >> m;
    vector<coupons> x;
    for (int i = 0; i < n; ++i) {
        coupons p;
        cin >> p.p >> p.c;
        x.push_back(p);
    }
    sort(x.begin(), x.end(), compare);
    priority_queue<long long> reuse;
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (k > 0) {
            if (m < x[i].c) break;
            m -= x[i].c;
            --k;
            reuse.push(x[i].p - x[i].c);
        } else {
            long long t1 = reuse.top() + x[i].c, t2 = x[i].p;
            if (t1 < t2) {
                if (m < t1) break;
                reuse.pop();
                reuse.push(x[i].p - x[i].c);
                m -= t1;
            } else {
                if (m < t2) break;
                m -= t2;
            }
        }
        ans = i + 1;
    }
    
    cout << ans << endl;
    
    return 0;
}
