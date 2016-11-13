#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct node {
    int a, b;     
};

bool comparex(const node &a, const node &b) {
    return a.a < b.a;     
}
bool comparey(const node &a, const node &b) {
    return a.b < b.b;     
}


vector<node> x, y;


int main() {
    freopen("crossings.in", "r", stdin);
    freopen("crossings.out", "w", stdout);
    int n;
    cin >> n;
    map<int, int> change;
    for (int i = 0; i < n; ++i) {
        node p;
        cin >> p.a >> p.b;
        x.push_back(p);
        y.push_back(p);
    }
    sort(x.begin(), x.end(), comparex);
    sort(y.begin(), y.end(), comparey);
    for (int i = 0; i < n; ++i) change[y[i].b] = i;
    
    int ans = 0, a = 0, maxT = -1;
    for (int i = 0; i < n; ++i) {
        if (y[i].b == x[i].b && maxT < i) ++ans;
        maxT = max(maxT, change[x[i].b]);
    }
    cout << ans << endl;
    
    return 0;   
}

