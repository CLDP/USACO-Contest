#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int x[11], y[11];

int getD(int a, int b) {
    if (x[a] == x[b]) {
        return y[b] > y[a] ? 0 : 2;
    } else 
    if (y[a] == y[b]) {
        return x[b] > x[a] ? 1 : 3;
    } else {
        return 4;
    }
}


int main() {
    freopen("connect.in", "r", stdin);
    freopen("connect.out", "w", stdout);
    
    int n, times = 1;
    cin >> n;
    vector<int> z;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        z.push_back(i);
        times *= (i + 1);
    }
    
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    
    int ans = 0;
    while (times--) {
        int dir = getD(n, z[0]);
        bool flag = (dir < 4);
        for (int i = 1; i < n; ++i) {
            int tempD = getD(z[i-1], z[i]);
            flag &= (tempD < 4);
            flag &= (tempD != dir);
            if (!flag) break;
            dir = tempD;
        }
        
        if (flag) {
            int tempD = getD(z[n-1], n);
            if (tempD < 4 && tempD != dir) ++ans;
        }
        
        next_permutation(z.begin(), z.end());
    }
    
    cout << ans << endl;
    
    return 0;
}
