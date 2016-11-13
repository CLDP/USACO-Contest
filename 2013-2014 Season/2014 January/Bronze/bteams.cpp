#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;



int main() {
    freopen("bteams.in", "r", stdin);
    freopen("bteams.out", "w", stdout);
    vector<int> x(12, 0), y(12, 0);
    for (int i = 0; i < 12; ++i) {
        cin >> x[i];
        y[i] = i / 3;
    }
    
    int ans = 1000000000;
    while (y[0] == 0) {
        vector<int> z(4, 0);
        for (int i = 0; i < 12; ++i) z[y[i]] += x[i];
        sort(z.begin(), z.end());
        if (z[3] - z[0] < ans) ans = z[3] - z[0];
        next_permutation(y.begin(), y.end());
    }
    while (y[0] != 0) {
        vector<int> z(4, 0);
        for (int i = 0; i < 12; ++i) z[y[i]] += x[i];
        sort(z.begin(), z.end());
        if (z[3] - z[0] < ans) ans = z[3] - z[0];
        next_permutation(y.begin(), y.end());
    }
    
    cout << ans << endl;
    
    return 0;
}
