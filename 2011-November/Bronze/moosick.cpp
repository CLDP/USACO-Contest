#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 20010;

int n, m;
int x[MAXN], y[11], z[11];
vector<int> ans;


int main() {
    freopen("moosick.in", "r", stdin);
    freopen("moosick.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> x[i];
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> z[i];
    sort(z, z + m);
    
    for (int i = 0; i < n - m + 1; ++i) {
        for (int j = 0; j < m; ++j) y[j] = x[i+j];
        sort(y, y + m);
        int tmp = y[0] - z[0];
        bool flag = true;
        for (int j = 1; j < m; ++j) flag &= (tmp == y[j] - z[j]);
        if (flag) ans.push_back(i + 1);
    }
    
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) cout << ans[i] << endl;
    
    return 0;    
}
