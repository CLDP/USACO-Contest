#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100001;

int n, m, root;

// Adjacent arry
vector<int> x[MAXN];

// Binary Index Tree
vector<int> BIT[MAXN];

// Size,     depth,   father,  heavy_fa, p_time,  height in heavy edge
int s[MAXN], d[MAXN], f[MAXN], ff[MAXN], g[MAXN], h[MAXN], P[MAXN][18];


// Find size and depth
int dfs(int a, int depth, bool *z) {
    s[a] = 1;
    d[a] = depth;
    z[a] = true;
    vector<int>::iterator iter = x[a].begin();
    while (iter != x[a].end()) {
        if (z[*iter]) {
            iter = x[a].erase(iter);
            continue;
        }
        dfs(*iter, depth + 1, z);
        s[a] += s[*iter];
        f[*iter] = a;
        ++iter;
    }
    
    return 0;
}


// Find heavy-light decomposition
int dfs_heavy(int a, int b) {
    vector<int>::iterator iter = x[a].begin();
    while (iter != x[a].end()) {
        if (s[*iter] * 2 > s[a]) {
            if (b == -1) {
                BIT[a].push_back(0);
                BIT[a].push_back(0);
                dfs_heavy(*iter, a);
                ff[*iter] = a;
                h[*iter] = d[*iter] - d[a];
            } else {
                BIT[b].push_back(0);
                dfs_heavy(*iter, b);
                ff[*iter] = b;
                h[*iter] = d[*iter] - d[b];
            }
        } else {
            dfs_heavy(*iter, -1);
        }
        ++iter;
    }
    return 0;
}


// Insert into heavy edge of b, add a, at c
int insert(int a, int b, int c) {
    int len = BIT[b].size();
    for (int i = h[c]; i < len; i += (i & -i)) BIT[b][i] += a;
    return 0;
}


// Query heavy edge of b, at c, need to find sum{x[c],...,x[end]}
int query(int b, int c) {
    int ans = 0;
    for (int i = h[c] - 1; i > 0; i -= (i & -i)) ans -= BIT[b][i];
    for (int i = BIT[b].size() - 1; i > 0; i -= (i & -i)) ans += BIT[b][i];
    return ans;
}


// Pre-calculate the array for LCA
int find_P() {
    for (int i = 1; i <= n; ++i)
     for (int j = 0; 1 << j < n; ++j) P[i][j] = -1;
    
    for (int i = 1; i <= n; ++i) P[i][0] = f[i];
    
    for (int j = 1; 1 << j < n; ++j)
     for (int i = 1; i <= n; ++i)
      if (P[i][j-1] != -1) P[i][j] = P[P[i][j-1]][j-1];
    
    return 0;
}


int find_LCA(int a, int b) {
    if (d[a] < d[b]) swap(a, b);
    
    int log = 1;
    while (1 << log <= d[a]) ++log;
    --log;
    
    for (int i = log; i >= 0; --i)
     if (d[a] - (1 << i) >= d[b]) a = P[a][i];
    
    if (a == b) return a;
    
    for (int i = log; i >= 0; --i)
     if (P[a][i] != -1 && P[a][i] != P[b][i]) {
         a = P[a][i];
         b = P[b][i];
     }
    
    return f[a];
}


int deal(int t, int addr) {
    while (t != root) {
        if (ff[t] > 0) {
            insert(addr, ff[t], t);
            t = ff[t];
        } else {
            g[t] += addr;
            t = f[t];
        }
    }
    return 0;
}


int main() {
    freopen("grassplant.in", "r", stdin);
    freopen("grassplant.out", "w", stdout);
    // This problem is great!!
    // Lots of useful technic are used!!
    cin >> n >> m;
    int a, b;
    for (int i = 0; i < n - 1; ++i) {
        cin >> a >> b;
        x[a].push_back(b);
        x[b].push_back(a);
    }
    root = n / 2;
    
    bool *z = new bool[n + 1];
    memset(z, 0, sizeof(bool) * (n + 1));
    dfs(root, 0, z);
    delete[] z;
    
    dfs_heavy(root, -1);
    
    find_P();
    
    char c;
    for (int i = 0; i < m; ++i) {
        cin >> c >> a >> b;
        if (c == 'P') {
            int t = a;
            deal(a, 1);
            deal(b, 1);
            deal(find_LCA(a, b), -2);
        } else {
            if (b == f[a]) swap(a, b);
            if (ff[b] > 0) {
                cout << query(ff[b], b) << endl;
            } else {
                cout << g[b] << endl;
            }
        }
    }
    
    return 0;
}
