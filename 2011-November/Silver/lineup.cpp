#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 2100000000;

int n;
vector<pair<int, int> > x;
map<int, int> hash;


int main() {
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);
    int a, b;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        x.push_back(make_pair(a, b));
        ++hash[b];
    }
    sort(x.begin(), x.end());
    
    int l = 0, r = 0, m = hash.size(), ans = INF;
    hash.clear();
    
    while (r < n) {
        while (hash.size() < m) {
            ++hash[x[r++].second];
            if (r == n) break;
        }
        while (hash.size() == m) {
            if (ans > x[r-1].first - x[l].first) ans = x[r-1].first - x[l].first;
            --hash[x[l].second];
            if (hash[x[l].second] == 0) hash.erase(x[l].second);
            ++l;
        }
    }
    
    cout << ans << endl;
    return 0;
}
