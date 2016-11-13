#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
using namespace std;

const int MAXN = 10010;
const int MAXK = 5;
const int INF = 1000000000;

int n, m, k;
vector<pair<int, int> > x[MAXN];
int d[MAXK][MAXN];

int SPFA(int T, int s) {
    vector<bool> z(n, false);
    for (int i = 1; i <= n; ++i) d[T][i] = INF;
    
    queue<int> que;
    que.push(s);
    d[T][s] = 0;
    z[s] = true;
    while (!que.empty()) {
        int a = que.front();
        que.pop();
        for (int i = 0; i < x[a].size(); ++i) {
            if (d[T][x[a][i].first] > d[T][a] + x[a][i].second) {
                d[T][x[a][i].first] = d[T][a] + x[a][i].second;
                if (!z[x[a][i].first]) {
                    z[x[a][i].first] = true;
                    que.push(x[a][i].first);
                }
            }
        }
        z[a] = false;
    }
    
    return 0;
}


int main() {
    freopen("relocate.in", "r", stdin);
    freopen("relocate.out", "w", stdout);
    cin >> n >> m >> k;
    vector<int> z(k, 0);
    set<int> zz;
    for (int i = 0; i < k; ++i) {
        cin >> z[i];
        zz.insert(z[i]);
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        x[a].push_back(make_pair(b, c));
        x[b].push_back(make_pair(a, c));
    }
    
    vector<int> y;
    for (int i = 0; i < k; ++i) {
        SPFA(i, z[i]);
        y.push_back(i);
    }
    
    int times = 1;
    for (int i = 1; i <= k; ++i) times *= i;
    
    int ans = INF;
    for (int i = 0; i < times; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (zz.find(j) != zz.end()) continue;
            int temp = 0;
            temp += d[y[0]][j] + d[y[k-1]][j];
            for (int t = 0; t < k - 1; ++t) temp += d[y[t]][z[y[t+1]]];
            if (temp < ans) ans = temp;
        }
        
        next_permutation(y.begin(), y.end());
    }
    
    cout << ans << endl;
    
    return 0;
}
