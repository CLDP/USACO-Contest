#include <iostream>
#include <cstdio>
#include <set>
#include <map>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200010;
const int INF = 1000000007;

struct edge {
    int a, b, c;
    bool operator < (const edge &B) const {
        return c < B.c;
    }
};

vector<pair<int, int> > X[MAXN];
edge Y[MAXN];
int f[MAXN], d[MAXN], c[MAXN];
multiset<int> S;
map<int, multiset<int> > SS[MAXN];

int find(int a) {
    if (a != f[a]) f[a] = find(f[a]);
    return f[a];
}

void unionn(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return ;
    if (d[a] > d[b]) f[b] = f[a]; else f[a] = f[b];
    d[a] = d[b] = d[a] + d[b];
}

void dfs(int a, int fa) {
    f[a] = fa;
    for (int i = 0; i < X[a].size(); ++i) {
        if (X[a][i].first != fa) {
            SS[a][c[X[a][i].first]].insert(X[a][i].second);
            dfs(X[a][i].first, a);
            d[X[a][i].first] = X[a][i].second;
        }
    }
    for (auto iter = SS[a].begin(); iter != SS[a].end(); ++iter) {
        if (iter->first != c[a]) S.insert(*iter->second.begin());
    }
}

void update(int a, int b) {
    if (f[a] != -1) {
        int temp = *SS[f[a]][c[a]].begin();
        SS[f[a]][c[a]].erase(SS[f[a]][c[a]].find(d[a]));
        if (SS[f[a]][c[a]].empty()) SS[f[a]].erase(c[a]);

        if (c[f[a]] != c[a]) {
            S.erase(S.find(temp));
            if (SS[f[a]].find(c[a]) != SS[f[a]].end() && !SS[f[a]][c[a]].empty()) 
                S.insert(*SS[f[a]][c[a]].begin());
        }

        if (c[f[a]] != b) {
            if (!SS[f[a]][b].empty()) {
                if (d[a] < *SS[f[a]][b].begin()) {
                    S.erase(S.find(*SS[f[a]][b].begin()));
                    S.insert(d[a]);
                }
            } else {
                S.insert(d[a]);
            }
        }

        SS[f[a]][b].insert(d[a]);
    }

    if (SS[a].find(c[a]) != SS[a].end()) S.insert(*SS[a][c[a]].begin());
    if (SS[a].find(b) != SS[a].end()) S.erase(S.find(*SS[a][b].begin()));
    c[a] = b;
}


int main() {
    freopen("grass.in", "r", stdin);
    freopen("grass.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    int N, M, K, Q;
    cin >> N >> M >> K >> Q;
    for (int i = 0; i < M; ++i) cin >> Y[i].a >> Y[i].b >> Y[i].c;
    sort(Y, Y + M);
    for (int i = 1; i <= N; ++i) {
        f[i] = i;
        d[i] = 1;
    }

    int cnt = 0;
    for (int i = 0; i < M; ++i) {
        if (find(Y[i].a) == find(Y[i].b)) continue;
        int a = Y[i].a, b = Y[i].b, c = Y[i].c;
        X[a].push_back(make_pair(b, c));
        X[b].push_back(make_pair(a, c));
        unionn(a, b);
        ++cnt;
        if (cnt == N - 1) break;
    }

    for (int i = 1; i <= N; ++i) cin >> c[i];
    dfs(1, -1);

    for (int i = 0; i < Q; ++i) {
        int a, b;
        cin >> a >> b;
        if (c[a] != b) update(a, b);
        cout << *S.begin() << endl;
    }

    return 0;
}
