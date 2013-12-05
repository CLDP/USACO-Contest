#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100010;
const int MAXK = 21;

int fa[MAXN], f[MAXN][MAXK];
vector<pair<int, bool> > x[MAXN];
bool z[MAXN];

int make_tree() {
    queue<int> que;
    que.push(1);
    z[1] = true;
    while (!que.empty()) {
        int a = que.front();
        que.pop();
        for (int i = 0; i < x[a].size(); ++i)
         if (!z[x[a][i].first]) {
             x[a][i].second = true;
             que.push(x[a][i].first);
             z[x[a][i].first] = true;
             fa[x[a][i].first] = a;
         }
    }
    return 0;
}

int dp(int a, int b) {
    int ans = f[a][0];
    for (int i = 0; i < x[a].size(); ++i) {
        if (!x[a][i].second) continue;
        ans += f[x[a][i].first][b-1];
    }
    
    return ans;
}

int cal(int a, int b) {
    int ans = f[a][b], c = a;
    while (a != 1 && b > 0) {
        c = a;
        a = fa[a];
        --b;
        ans += f[a][b];
        if (b > 0) ans -= f[c][b - 1];
    }
    return ans;
}


int main() {
    freopen("nearcows.in", "r", stdin);
    freopen("nearcows.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        x[a].push_back(make_pair(b, false));
        x[b].push_back(make_pair(a, false));
    }
    
    make_tree();
    
    for (int i = 1; i <= n; ++i) cin >> f[i][0];
    
    for (int i = 1; i <= k; ++i) 
     for (int j = 1; j <= n; ++j) f[j][i] = dp(j, i);
    
    for (int i = 1; i <= n; ++i) cout << cal(i, k) << endl;
    
    return 0;
}
