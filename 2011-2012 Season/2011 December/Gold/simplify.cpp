#include <cstdio>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 40010;
const int INF = 1000000007;

int f[MAXN], d[MAXN];
vector<pair<int, pair<int, int> > > x;


int find(int a) {
    if (a != f[a]) f[a] = find(f[a]);
    return f[a];
}

bool Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (d[a] < d[b]) {
        f[a] = f[b];
    } else {
        f[b] = f[a];
    }
    d[a] += d[b];
    d[b] = d[a];
    return true;
}


int main() {
    freopen("simplify.in", "r", stdin);
    freopen("simplify.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        x.push_back(make_pair(c, make_pair(a, b)));
    }
    
    sort(x.begin(), x.end());
    
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        d[i] = 1;
    }
    
    int tree = 0;
    long long num = 1;
    for (int i = 0; i < m; ) {
        int j = i, diff = 0, a, b;
        set<pair<int, int> > hash;
        while (x[j].first == x[i].first) {
            a = x[j].second.first;
            b = x[j].second.second;
            a = find(a);
            b = find(b);
            if (a != b) {
                ++diff;
                if (a < b) swap(a, b);
                hash.insert(make_pair(a, b));
            }
            ++j;
        }
        
        int join = 0;
        while (i < j) {
            join += Union(x[i].second.first, x[i].second.second);
            ++i;
        }
        tree += join * x[i-1].first;
        if (diff == 3) {
            if (join == 1 || (join == 2 && hash.size() == 3)) num = (num * 3) % INF;
            if (join == 2 && hash.size() == 2) num = (num * 2) % INF;
        } else 
        if (diff == 2) {
            if (join == 1) num = (num * 2) % INF;
        }
    }
    
    cout << tree << " " << num << endl;
    
    return 0;
}
