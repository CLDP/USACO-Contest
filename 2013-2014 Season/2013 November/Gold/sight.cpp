#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double PI = 3.14159265358979323846;


struct node {
    double x, y;
    double deg, base;
};

bool compare(const node &a, const node &b) {
    return (b.base - b.deg) - (a.base - a.deg) > 1e-10;
}


int main() {
    freopen("sight.in", "r", stdin);
    freopen("sight.out", "w", stdout);
    int n;
    double r;
    cin >> n >> r;
    vector<node> vex;
    for (int i = 0; i < n; ++i) {
        node p;
        cin >> p.x >> p.y;
        p.deg = acos(r / sqrt(p.x * p.x + p.y * p.y));
        p.base = atan2(p.y, p.x);
        if (p.base - p.deg < 0) p.base += 2 * PI;
        vex.push_back(p);
    }
    sort(vex.begin(), vex.end(), compare);
    
    for (int i = 0; i < n; ++i) {
        vex.push_back(vex[i]);
        vex[n+i].base += 2 * PI;
    }
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        node T;
        T.deg = 0;
        T.base = vex[i].base + vex[i].deg;
        int temp = upper_bound(vex.begin(), vex.end(), T, compare) - vex.begin() - i - 1;
        ans += temp;
    }
    
    cout << ans << endl;
    
    return 0;
}
