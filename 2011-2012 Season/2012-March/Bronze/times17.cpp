#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int f[1010];


int main() {
    freopen("times17.in", "r", stdin);
    freopen("times17.out", "w", stdout);
    
    string p;
    cin >> p;
    
    int L = p.size();
    for (int i = 0; i < L; ++i) {
        f[i] += (p[L - 1 - i] - '0') * 17;
        f[i + 1] += f[i] / 2;
        f[i] = f[i] % 2;
    }
    
    while (f[L] > 1) {
        f[L + 1] = f[L] / 2;
        f[L] = f[L] % 2;
         ++L;
    }
    
    for (int i = L; i >= 0; --i) cout << f[i];
    cout << endl;
    
    return 0;
}
