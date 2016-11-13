#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;


int main() {
    freopen("folding.in", "r", stdin);
    freopen("folding.out", "w", stdout);
    int n, l;
    cin >> n >> l;
    l *= 2;
    set<int> x;
    vector<int> y;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        x.insert(a * 2);
        y.push_back(a * 2);
    }
    
    int ans = 0;
    for (int i = 1; i < l; ++i) {
        bool flag = true;
        for (int j = 0; j < n; ++j) {
            flag &= (2 * i - y[j] < 0 || 2 * i - y[j] > l || x.find(2 * i - y[j]) != x.end());
            if (!flag) break;
        }
        
        if (flag) ++ans;
    }
    
    cout << ans << endl;
    
    return 0;
}
