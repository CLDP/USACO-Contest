#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;
const int MAXM = 25001;

int x[MAXN], y[MAXN];
int f[MAXM];

int main() {
    freopen("stacking.in", "r", stdin);
    freopen("stacking.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        ++x[a];
        ++y[b + 1];
    }
    
    int h = 0;
    for (int i = 1; i <= n; ++i) {
        h += x[i];
        h -= y[i];
        ++f[h];
    }
    
    h = 0;
    int i = 0;
    while (h <= n / 2) {
        h += f[i];
        ++i;
    }
    
    cout << i - 1 << endl;
    
    return 0;
}
