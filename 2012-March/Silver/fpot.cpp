#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int INF = 1000000000;

int main() {
    freopen("fpot.in", "r", stdin);
    freopen("fpot.out", "w", stdout);
    int n, d;
    cin >> n >> d;
    vector<pair<int, int> > x;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        x.push_back(make_pair(a, b));
    }
    sort(x.begin(), x.end());
    
    int ans = INF;
    vector<pair<int, int> >::iterator l = x.begin(), r = x.begin();
    multiset<int> z;
    z.insert(r->second);
    while (true) {
        bool flag = true;
        while (z.empty() || *(z.rbegin()) - *(z.begin()) < d) {
            ++r;
            if (r == x.end()) {
                flag = false;
                break;
            }
            z.insert(r->second);
        }
        if (!flag) break;
        if (r->first - l->first < ans) ans = r->first - l->first;
        int t = l->first;
        while (l->first == t) {
            // multiset has two erases. This one erases one element, the other erases all. 
            z.erase(z.find(l->second));
            ++l;
        }
    }
    
    if (ans == INF)
        cout << -1 << endl;
    else
        cout << ans << endl;
    
    return 0;
}
