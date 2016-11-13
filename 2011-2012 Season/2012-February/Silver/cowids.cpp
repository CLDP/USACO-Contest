#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

long long C(long long n, long long k) {
    long long ans = 1;
    for (int i = n; i > n - k; --i) ans *= i;
    for (int i = 2; i <= k; ++i) ans /= i;
    return ans;
}


int main() {
    freopen("cowids.in", "r", stdin);
    freopen("cowids.out", "w", stdout);
    long long n, k;
    cin >> n >> k;
    
    long long p = 0, temp = 0;
    while ((temp = C(k+p-1, k-1)) < n) {
        n -= temp;
        ++p;
    }
    cout << 1;
    int times = 0;
    while (p > 0 || k > 1) {
        if ((temp = C(k+p-2, k-1)) >= n) {
            cout << 0;
            --p;
        } else {
            cout << 1;
            n -= temp;
            --k;
        }
    }
    
    cout << endl;
    
    return 0;
}
