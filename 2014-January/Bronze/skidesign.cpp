#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1001;

int x[MAXN];


int main() {
    freopen("skidesign.in", "r", stdin);
    freopen("skidesign.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> x[i];
    
    long long ans = 1000000000;
    for (int i = 0; i <= 83; ++i) {
        long long temp = 0;
        for (int j = 0; j < n; ++j) {
            if (x[j] < i) temp += (x[j] - i) * (x[j] - i);
            if (x[j] > i + 17) temp += (i + 17 - x[j]) * (i + 17 - x[j]);
        }
        if (temp < ans) ans = temp;
    }
    
    cout << ans << endl;
    
    return 0;
}
