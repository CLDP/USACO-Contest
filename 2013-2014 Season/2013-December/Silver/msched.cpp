#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10010;

struct node {
    int g, d;
};


vector<node> x;

bool compare(const node &a, const node &b) {
    if (a.d != b.d) return a.d < b.d;
    return a.g > b.g;
}


int main() {
    freopen("msched.in", "r", stdin);
    freopen("msched.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        node p;
        cin >> p.g >> p.d;
        x.push_back(p);
    }
    sort(x.begin(), x.end(), compare);
    
    multiset<int> z;
    
    int prev = 0, i = 0, timeleft = 0;
    while (i < n) {
        int j = i;
        while (j < n && x[j].d == x[i].d) ++j;
        int time = x[i].d - prev + timeleft;
        prev = x[i].d;
        while (i < j) {
            if (time > 0) {
                --time;
                z.insert(x[i].g);
            } else {
                if (*z.begin() < x[i].g) {
                    z.erase(z.begin());
                    z.insert(x[i].g);
                }
            }
            ++i;
        }
        timeleft = time;
    }
    
    multiset<int>::iterator iter = z.begin();
    int ans = 0;
    while (iter != z.end()) {
        ans += *iter;
        ++iter;
    }
    
    cout << ans << endl;
    
    return 0;
}
