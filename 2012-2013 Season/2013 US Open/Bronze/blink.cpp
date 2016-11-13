#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
using namespace std;

map<int, long long> ans;
bool x[20], y[20];

int main() {
    freopen("blink.in", "r", stdin);
    freopen("blink.out", "w", stdout);
    int n;
    long long m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> x[i];
    while (m > 0) {
        --m;
        for (int i = 0; i < n; ++i) y[i] = x[i];
        for (int i = 0; i < n; ++i) {
            if (x[i] && i != n-1) y[i+1] = !y[i+1];
            if (x[i] && i == n-1) y[0] = !y[0];
        }
        int a = 0;
        for (int i = 0; i < n; ++i) {
            x[i] = y[i];
            a = a * 2 + x[i];
        }
        if (ans.find(a) == ans.end()) {
            ans[a] = m;
        } else {
            m = m % (ans[a] - m);
        }
    }
    for (int i = 0; i < n; ++i) 
     if (x[i]) 
         cout << 1 << endl;
     else
         cout << 0 << endl;
    
    return 0;    
}
