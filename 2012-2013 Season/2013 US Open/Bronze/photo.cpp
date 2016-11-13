#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int x[1010], y[1010];
map<int, int> p;
vector<int> pairs[2010];

int main() {
    freopen("photo.in", "r", stdin);
    freopen("photo.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<int> lsh;
    for (int i = 0; i < k; ++i) {
        cin >> x[i] >> y[i];
        lsh.push_back(x[i]);
        lsh.push_back(y[i]);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(distance(lsh.begin(), unique(lsh.begin(), lsh.end())));
    for (int i = 0; i < lsh.size(); ++i) p[lsh[i]] = i;
     
    for (int i = 0; i < k; ++i) {
        if (p[x[i]] > p[y[i]])
            pairs[p[y[i]]].push_back(p[x[i]]);
        else
            pairs[p[x[i]]].push_back(p[y[i]]);
    }
    
    int ans = 0, upbound;
    n = lsh.size();
    for (int i = 0; i < n; ) {
        ++ans;
        upbound = n;
        while (i < upbound) {
            while (pairs[i].empty() && i < upbound) ++i;
            if (i == upbound) break;
            for (int j = 0; j < pairs[i].size(); ++j) 
             if (pairs[i][j] < upbound) upbound = pairs[i][j];
            ++i;
        }
    }
    
    cout << ans << endl;
    
    return 0;    
}

