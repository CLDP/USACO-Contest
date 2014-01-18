#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 501;
const int INF = 2000000000;
const int MX[4] = {0, 0, -1, 1};
const int MY[4] = {-1, 1, 0, 0};

int n, m;
int x[MAXN][MAXN];
vector<pair<int, int> > y;
bool z[MAXN][MAXN];



bool check(int t) {
    memset(z, 0, sizeof(z));
    queue<pair<int, int> > que;
    que.push(y[0]);
    z[y[0].first][y[0].second] = true;
    while (!que.empty()) {
        int a = que.front().first;
        int b = que.front().second;
        que.pop();
        for (int i = 0; i < 4; ++i) {
            if (a + MX[i] < 0 || a + MX[i] >= n) continue;
            if (b + MY[i] < 0 || b + MY[i] >= m) continue;
            if (z[a + MX[i]][b + MY[i]] || abs(x[a + MX[i]][b + MY[i]] - x[a][b]) > t) continue;
            que.push(make_pair(a + MX[i], b + MY[i]));
            z[a + MX[i]][b + MY[i]] = true;
        }
    }
    
    for (int i = 1; i < y.size(); ++i)
     if (!z[y[i].first][y[i].second]) return false;
    
    return true;
}

int main() {
    freopen("ccski.in", "r", stdin);
    freopen("ccski.out", "w", stdout);
    cin >> n >> m;
    int l = INF, r = 0;
    for (int i = 0; i < n; ++i) 
     for (int j = 0; j < m; ++j) {
         cin >> x[i][j];
         l = min(l, x[i][j]);
         r = max(r, x[i][j]);
     }
     
    for (int i = 0; i < n; ++i) 
     for (int j = 0; j < m; ++j) {
         int a;
         cin >> a;
         if (a == 1) y.push_back(make_pair(i, j)); 
     }
    
    if (y.size() == 0 || check(0)) {
        cout << 0 << endl;
        return 0;
    }
    r = r - l;
    l = 0;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid; else l = mid;
    }
    
    cout << r << endl;
    
    return 0;
}
