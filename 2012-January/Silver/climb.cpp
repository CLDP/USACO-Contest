#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


const int INF = 1000000000;

struct node {
    int u, d;
};

int n;
vector<node> x;

bool compare(const node &a, const node &b) {
    if (a.u < a.d && b.u < b.d) {
        return a.u < b.u;
    } else 
    if (a.u >= a.d && b.u < b.d) {
        return false;
    } else 
    if (a.u < a.d && b.u >= b.d) {
        return true;
    } else {
        return a.d > b.d;
    }
}


int main() {
    freopen("climb.in", "r", stdin);
    freopen("climb.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        node p;
        cin >> p.u >> p.d;
        x.push_back(p);
    }
    sort(x.begin(), x.end(), compare);
    
    int time1 = 0, time2 = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        time1 += x[i].u;
        time2 = max(time2, time1) + x[i].d;
        ans = max(ans, time2);
    }
    
    cout << ans << endl;
    
    return 0;
}
