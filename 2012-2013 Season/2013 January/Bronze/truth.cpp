#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1001;

struct node {
    int a, b;
    bool c;
};

vector<int> x[MAXN], y[MAXN];
vector<node> H;
int z[MAXN], nn;

int dfs(int a, int b) {
    z[a] = b;
    
    for (int i = 0; i < x[a].size(); ++i) 
     if (z[x[a][i]] == 0) dfs(x[a][i], b);
    
    for (int i = 0; i < y[a].size(); ++i) 
     if (z[y[a][i]] == 0) dfs(y[a][i], b % 2 + 1);
    
    return 0;
}

bool check() {
    for (int i = 0; i < H.size(); ++i) {
        if (H[i].c && z[H[i].a] == z[H[i].b]) return false;
        if (!H[i].c && z[H[i].a] != z[H[i].b]) return false;
    }
    return true;
}


int main() {
    freopen("truth.in", "r", stdin);
    freopen("truth.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int a, b;
        string c;
        cin >> a >> b >> c;
        node p;
        p.a = a;
        p.b = b;
        p.c = c == "L";
        if (c == "L") {
            y[a].push_back(b);
            y[b].push_back(a);
        } else {
            x[a].push_back(b);
            x[b].push_back(a);
        }
        memset(z, 0, sizeof(z));
        for (int j = 1; j <= N; ++j) {
            if (z[j] == 0) {
                z[j] = 1;
                dfs(j, z[j]);
            }
        }
        H.push_back(p);
        if (!check()) {
            cout << i << endl;
            return 0;
        }
    }
    cout << M << endl;
    return 0;
}
