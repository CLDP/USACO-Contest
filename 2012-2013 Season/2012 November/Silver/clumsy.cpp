#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;


int main() {
    freopen("clumsy.in", "r", stdin);
    freopen("clumsy.out", "w", stdout);
    string p;
    cin >> p;
    int ans = 0, L = 0;
    for (int i = 0; i < p.size(); ++i) {
        L += (p[i] == '(' ? 1 : -1);
        if (L < 0) {
            ++ans;
            L += 2;
        }
    }
    ans += L / 2;
    cout << ans << endl;
    
    return 0;
}
