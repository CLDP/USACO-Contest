#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const int INF = 1000000000;
const int MX[4] = {0, 1, 0, -1};
const int MY[4] = {1, 0, -1, 0};

bool x[MAXN][MAXN], z[MAXN][MAXN];
int d[MAXN][MAXN];

bool check(int a, int b) {
    return a <= 1001 && a >= 0 && b <= 1001 && b >= 0;
}

int SPFA(int a, int b) {
    for (int i = 0; i <= 1001; ++i)
     for (int j = 0; j <= 1001; ++j) d[i][j] = INF;
    
    d[a][b] = 0;
    queue<pair<int, int> > que;
    que.push(make_pair(a, b));
    z[a][b] = true;
    while (!que.empty()) {
        a = que.front().first;
        b = que.front().second;
        que.pop();
        for (int i = 0; i < 4; ++i) {
            int p = a + MX[i];
            int q = b + MY[i];
            if (check(p, q)) {
                if (x[p][q] && d[p][q] > d[a][b] + 1) {
                    d[p][q] = d[a][b] + 1;
                    if (!z[p][q]) {
                        z[p][q] = true;
                        que.push(make_pair(p, q));
                    }
                }
                
                if (!x[p][q] && d[p][q] > d[a][b]) {
                    d[p][q] = d[a][b];
                    if (!z[p][q]) {
                        z[p][q] = true;
                        que.push(make_pair(p, q));
                    }
                }
            }
        }
        z[a][b] = false;
    }
}


int main() {
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 0; i < n; ++i) {
        int p, q;
        cin >> p >> q;
        x[p][q] = true;
    }
    
    SPFA(a, b);
    
    cout << d[0][0] << endl;
    
    return 0;
}
