#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 5;
const int MX[4] = {-1, 1, 0, 0};
const int MY[4] = {0, 0, -1, 1};

int ans;
bool x[MAXN][MAXN];

bool check(int a, int b) {
    if (a < 0 || a > 4) return false;
    if (b < 0 || b > 4) return false;
    return !x[a][b];
}

int dfs(int a, int b, int c, int d, int t) {
    if (t == 1) {
        int p = -1, q;
        for (int i = 0; i < 4; ++i)
         if (check(a + MX[i], b + MY[i])) {
             p = a + MX[i];
             q = b + MY[i];
             break;
         }
        if (p == -1) return 0;
        
        if (p == c) {
            if (abs(q - d) == 1) ++ans;
        } else
        if (q == d) {
            if (abs(p - c) == 1) ++ans;
        }
        return 0;
    } else {
        int p, q, r, s;
        for (int i = 0; i < 4; ++i)
         if (check(a + MX[i], b + MY[i])) {
             p = a + MX[i];
             q = b + MY[i];
             x[p][q] = true;
             
             for (int j = 0; j < 4; ++j) 
              if (check(c + MX[j], d + MY[j])) {
                  r = c + MX[j];
                  s = d + MY[j];
                  x[r][s] = true;
                  dfs(p, q, r, s, t - 1);
                  x[r][s] = false;
              }
             
             x[p][q] = false;
         }
    }
    return 0;
}


int main() {
    freopen("grazing.in", "r", stdin);
    freopen("grazing.out", "w", stdout);
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        x[a-1][b-1] = true;
    }
    x[0][0] = true;
    x[4][4] = true;
    
    if (k % 2 == 0) {
        int times = (25 - k) / 2;
        dfs(0, 0, 4, 4, times);
    }
    
    cout << ans << endl;
    
    return 0;
}
