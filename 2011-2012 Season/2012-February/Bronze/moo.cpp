#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;


int main() {
    freopen("moo.in", "r", stdin);
    freopen("moo.out", "w", stdout);
    
    int n;
    cin >> n;
    vector<int> f;
    f.push_back(3);
    int l = 0;
    while (f[l] < n) {
        f.push_back(f[l] * 2 + 4 + l);
        ++l;
    }

    while (n > 0) {
        while (f[l] > n) --l;
        if (n - f[l] <= 4 + l) {
            if (n - f[l] == 1) {
                cout << "m" << endl;
                break;
            } else {
                cout << "o" << endl;
                break;
            }
        } else {
            n -= f[l] + 4 + l;
        }
    }
    
    return 0;
}
