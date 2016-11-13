#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;


int main() {
    freopen("ctiming.in", "r", stdin);
    freopen("ctiming.out", "w", stdout);
    int a, b, c;
    cin >> a >> b >> c;
    if (a < 11 || (a == 11 && b < 11) || (a == 11 && b == 11 && c < 11)) {
        cout << -1 << endl;
        return 0;
    }
    
    int ans = 0;
    if (a == 11) {
        if (b == 11) 
            cout << c - 11 << endl;
        else
            cout << (b - 11) * 60 + c << endl;
    } else {
        cout << 49 + 12 * 60 + (a - 12) * 24 * 60 + b * 60 + c << endl;
    }
    
    return 0;    
}
