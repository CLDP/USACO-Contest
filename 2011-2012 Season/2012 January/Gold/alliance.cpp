#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;

const int MAXN = 100001;
const int INF = 1000000007;

int n, m;
int f[MAXN], d[MAXN], s[MAXN];
bool z[MAXN];
vector<int> x[MAXN];

int find(int a) {
    if (a != f[a]) f[a] = find(f[a]);
    return f[a];
}

int Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;
    if (d[a] < d[b]) {
        f[a] = f[b];
    } else {
        f[b] = f[a];
    }
    d[a] += d[b];
    d[b] = d[a];
    return 0;
}

int dfs(int a) {
    z[a] = true;
    vector<int>::iterator iter = x[a].begin();
    int ans = 0;
    while (iter != x[a].end()) {
        ++ans;
        if (!z[*iter]) ans += dfs(*iter);
        ++iter;
    }
    return ans;
}

long long deal(int a) {
    int ans = dfs(a) /  2;
    int size = d[find(a)];
    if (size == ans) {
        return 2;
    } else
    if (size == ans + 1) {
        return size;
    }
    return 0;
}


int main() {
    freopen("alliance.in", "r", stdin);
    freopen("alliance.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        d[i] = 1;
        f[i] = i;
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        ++s[a];
        ++s[b];
        x[a].push_back(b);
        x[b].push_back(a);
        Union(a, b);
    }
    
    long long ans = 1;
    for (int i = 1; i <= n; ++i) {
        if (z[find(i)]) continue;
        ans *= deal(i);
        ans %= INF;
    }
    
    cout << ans << endl;
    
    return 0;
}
