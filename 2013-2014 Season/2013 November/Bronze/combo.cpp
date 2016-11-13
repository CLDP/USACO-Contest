#include <iostream>
#include <cstdio>
using namespace std;

int n;

bool check(int a, int b) {
    if (b >= a && b - a <= 2) return true;
    if (a >= b && a - b <= 2) return true;
    if (a < b && a + n - b <= 2) return true;
    if (b < a && b + n - a <= 2) return true;
    return false;
}


int main() {
    freopen("combo.in", "r", stdin);
    freopen("combo.out", "w", stdout);
    int x[3], y[3];
    int ans = 0;
    cin >> n >> x[0] >> x[1] >> x[2] >> y[0] >> y[1] >> y[2];
    for (int i = 1; i <= n; ++i)
     for (int j = 1; j <= n; ++j)
      for (int k = 1; k <= n; ++k)
       if ((check(x[0], i) && check(x[1], j) && check(x[2], k)) ||
           (check(y[0], i) && check(y[1], j) && check(y[2], k))) ++ans;
    
    cout << ans << endl;
    
    return 0;
}
