#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int A[MAXN], B[MAXN], f[MAXN];

int main() {
    freopen("restack.in", "r", stdin);
    freopen("restack.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> A[i] >> B[i];
    
    f[0] = A[0] - B[0];
    for (int i = 1; i < n; ++i) f[i] = A[i] + f[i-1] - B[i];
    nth_element(f, f + n / 2, f + n);
    int m = f[n / 2];
    long long ans = 0;
    for (int i = 0; i < n; ++i) ans += abs(f[i] - m);
    
    cout << ans << endl;
    
    return 0;
}
