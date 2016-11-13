#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

bool check(int a, int b) {
    while (a > 0 && b > 0) {
        if (a % 10 + b % 10 > 9) return false;
        a /= 10;
        b /= 10;
    }
    return true;
}


int main() {
    freopen("escape.in", "r", stdin);
    freopen("escape.out", "w", stdout);
    int n, x[21];
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> x[i];
    
    int ans = 0;
    for (int i = 1; i < (1 << n); ++i) {
        int tmp = i, j = 0, now = 0, sum = 0;
        bool flag = true;
        while (tmp > 0) {
            if (tmp & 1) {
                if (!check(sum, x[j])) {
                    flag = false;
                    break;
                }
                sum += x[j];
                ++now;
            }
            ++j;
            tmp /= 2;
        }
        
        if (flag && now > ans) ans = now;
    }
    
    cout << ans << endl;
    
    return 0;
}
