#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if (b <= c || d <= a) {
        cout << b - a + d - c << endl;
    } else {
        cout << max(b, d) - min(a, c) << endl;
    }
    return 0;
}
