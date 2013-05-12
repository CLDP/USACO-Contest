#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 51;
const int INF = 10000;
const int MX[4] = {-1, 1, 0, 0};
const int MY[4] = {0, 0, -1, 1};

int n, m;
int x[MAXN][MAXN];
vector<pair<int, int> > spots[3];

int dfs(int a, int b, int num) {
    if (a < 0 || b < 0 || a == n || b == m || x[a][b] != 1) return 0;
    x[a][b] = 2;
    spots[num].push_back(make_pair(a, b));
    for (int i = 0; i < 4; ++i) dfs(a + MX[i], b + MY[i], num);
    return 0;
}

int dist(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int try_point(int a, int b) {
    if (x[a][b] == 2) return INF;
    int ans = 0;
    for (int i = 0; i < 3; ++i) {
        int tmp = INF, len = spots[i].size();
        for (int j = 0; j < len; ++j) {
            int tmp2 = dist(spots[i][j].first, spots[i][j].second, a, b) - 1;
            if (tmp2 < tmp) tmp = tmp2;
        }
        ans += tmp;
    }
    return ans + 1;
}


int main() {
    freopen("pageant.in", "r", stdin);
    freopen("pageant.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string p;
        cin >> p;
        for (int j = 0; j < m; ++j) x[i][j] = (p[j] == 'X');
    }
    
    int num = 0, ans = INF;
    for (int i = 0; i < n; ++i)
     for (int j = 0; j < m; ++j) 
      if (x[i][j] == 1) dfs(i, j, num++);
    
    for (int i = 0; i < n; ++i)
     for (int j = 0; j < m; ++j) {
         int tmp = try_point(i, j);
         if (tmp < ans) ans = tmp;
     }
     
    int dist3[3];
    for (int i = 0; i < 3; ++i) {
        dist3[i] = INF;
        int len1 = spots[i].size(), len2 = spots[(i + 1) % 3].size();
        for (int j = 0; j < len1; ++j)
         for (int k = 0; k < len2; ++k) {
             int tmp = dist(spots[i][j].first, spots[i][j].second, 
                            spots[(i + 1) % 3][k].first, spots[(i + 1) % 3][k].second) - 1;
             if (tmp < dist3[i]) dist3[i] = tmp;
         }
    }
    
    for (int i = 0; i < 3; ++i)
     if (dist3[i] + dist3[(i + 1) % 3] < ans) ans = dist3[i] + dist3[(i + 1) % 3];
    
    cout << ans << endl;
    
    return 0;
}
