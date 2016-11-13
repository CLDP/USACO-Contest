#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 40010;

vector<int> x[MAXN];
string y[MAXN];
bool z[MAXN];
int fa[MAXN];
int A1[MAXN], A2[MAXN], A3[MAXN], A4[MAXN], D1[MAXN], D2[MAXN], D3[MAXN], D4[MAXN];
int P1[MAXN], P2[MAXN];

int change(int a) {
    z[a] = true;
    int era = -1;
    for (int i = 0; i < x[a].size(); ++i) {
        if (z[x[a][i]]) {
            era = i;
        } else {
            change(x[a][i]);
        }
    }
    if (era != -1) {
        fa[a] = x[a][era];
        x[a].erase(x[a].begin() + era);
    }
    z[a] = false;
    return 0;
}


int dfs_down(int a) {
    if (y[a] == "(") {
        D1[a] = 1;
        D3[a] = -1;
        D2[a] = D4[a] = -MAXN;
    } else {
        D1[a] = -1;
        D4[a] = D2[a] = -MAXN;
        D3[a] = 1;
    }
    P1[a] = P2[a] = a;
    
    for (int i = 0; i < x[a].size(); ++i) {
        dfs_down(x[a][i]);
        int dir = (y[a] == "(" ? 1 : -1);
        
        if (D1[x[a][i]] + dir >= D1[a]) {
            P1[a] = x[a][i];
            D2[a] = D1[a];
            D1[a] = D1[x[a][i]] + dir;
        } else
        if (D1[x[a][i]] + dir >= D2[a]) {
            D2[a] = D1[x[a][i]] + dir;
        }
        
        if (D3[x[a][i]] - dir >= D3[a]) {
            P2[a] = x[a][i];
            D4[a] = D3[a];
            D3[a] = D3[x[a][i]] - dir;
        } else
        if (D3[x[a][i]] - dir >= D4[a]) {
            D4[a] = D3[x[a][i]] - dir;
        }
    }
    
    return 0;
}


int dfs_up(int a) {
    A1[a] = D1[a]; A2[a] = D2[a];
    A3[a] = D3[a]; A4[a] = D4[a];
    if (fa[a] != 0) {
        int b = fa[a], dir = (y[a] == "(" ? 1 : -1);
        if (P1[b] == a) {
            if (A2[b] + dir >= A1[a]) {
                A2[a] = A1[a];
                A1[a] = A2[b] + dir;
                P1[a] = b;
            } else
            if (A2[b] + dir >= A2[a]) {
                A2[a] = A2[b] + dir;
            }
        } else {
            if (A1[b] + dir >= A1[a]) {
                A2[a] = A1[a];
                A1[a] = A1[b] + dir;
                P1[a] = b;
            } else
            if (A1[b] + dir >= A2[a]) {
                A2[a] = A1[b] + dir;
            }
        }
        
        if (P2[b] == a) {
            if (A4[b] - dir >= A3[a]) {
                A4[a] = A3[a];
                A3[a] = A4[b] - dir;
                P2[a] = b;
            } else
            if (A4[b] - dir >= A4[a]) {
                A4[a] = A4[b] - dir;
            }
        } else {
            if (A3[b] - dir >= A3[a]) {
                A4[a] = A3[a];
                A3[a] = A3[b] - dir;
                P2[a] = b;
            } else
            if (A3[b] - dir >= A4[a]) {
                A4[a] = A3[b] - dir;
            }
        }
    }

    for (int i = 0; i < x[a].size(); ++i) dfs_up(x[a][i]);
    
    return 0;
}


int main() {
    freopen("btree.in", "r", stdin);
    freopen("btree.out", "w", stdout);
    int N;
    cin >> N;
    for (int i = 2; i <= N; ++i) {
        int a;
        cin >> a;
        x[a].push_back(i);
        x[i].push_back(a);
    }
    
    for (int i = 1; i <= N; ++i) cin >> y[i];
    
    change(1);
    dfs_down(1);
    dfs_up(1);
                                      
    int ans = 0;
    for (int i = 2; i <= N; ++i) {
        if (y[i] != y[fa[i]]) {
            if (y[i] == "(") {
                if (P1[i] == fa[i] && P2[fa[i]] == i) {
                    ans = max(ans, min(A2[i], A4[fa[i]]));
                } else
                if (P2[fa[i]] == i) {
                    ans = max(ans, min(A1[i], A4[fa[i]]));
                } else
                if (P1[i] == fa[i]) {
                    ans = max(ans, min(A2[i], A3[fa[i]]));
                } else {
                    ans = max(ans, min(A1[i], A3[fa[i]]));
                }
            } else {
                if (P2[i] == fa[i] && P1[fa[i]] == i) {
                    ans = max(ans, min(A4[i], A2[fa[i]]));
                } else
                if (P1[fa[i]] == i) {
                    ans = max(ans, min(A3[i], A2[fa[i]]));
                } else
                if (P2[i] == fa[i]) {
                    ans = max(ans, min(A4[i], A1[fa[i]]));
                } else {
                    ans = max(ans, min(A3[i], A1[fa[i]]));
                }
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
