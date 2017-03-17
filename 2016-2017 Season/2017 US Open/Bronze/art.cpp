#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    freopen("lostcow.in", "r", stdin);
    freopen("lostcow.out", "w", stdout);
    int a, b;
    cin >> a >> b;
    if (a == 0) {
        cout << 0 << endl;
        return 0;
    }

    int ans = 0;
    for (int i = 0; i < 14; i += 2) {
        if (b > a) {
            if (a + (1 << i) >= b) {
                cout << ans + b - a << endl;
                break;
            }
            ans += (1 << i) * 2 + (1 << (i + 1)) * 2;
        } else {
            ans += (1 << i) * 2;
            if (a - (1 << (i + 1)) <= b) {
                cout << ans + a - b << endl;
                break;
            }
            ans += (1 << (i + 1)) * 2;
        }
    }
    return 0;
}
