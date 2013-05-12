#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 260;

struct seg {
    int x1, y1, x2, y2;
};


int n;
int l[MAXN];
bool x[MAXN][MAXN], z[MAXN];
seg y[MAXN];

bool find(int v) {
    int k;
    for (int i = 1; i <= n; ++i) 
     if (!z[i] && x[v][i]) {
         z[i] = 1;
         k = l[i];
         l[i] = v;
         if (!k || find(k)) return 1;
         l[i] = k;
     }
    return 0;
}


int main() {
    freopen("steeple.in", "r", stdin);
    freopen("steeple.out", "w", stdout);
    
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> y[i].x1 >> y[i].y1 >> y[i].x2 >> y[i].y2;
        if (y[i].x1 > y[i].x2) swap(y[i].x1, y[i].x2);
        if (y[i].y1 > y[i].y2) swap(y[i].y1, y[i].y2);
    }
    
    for (int i = 1; i <= n; ++i) 
     if (y[i].x1 == y[i].x2) {
         for (int j = 1; j <= n; ++j) 
          if (y[j].y1 == y[j].y2) {
              if (y[j].x1 > y[i].x1) continue;
              if (y[j].x2 < y[i].x1) continue;
              if (y[i].y1 > y[j].y1) continue;
              if (y[i].y2 < y[j].y1) continue;
              x[i][j] = true;
          }
     }
    
    
    for (int i = 1; i <= n; ++i) {
        memset(z, 0, sizeof(z));
        find(i);
    }
    
    int ans = n;
    for (int i = 1; i <= n; ++i) ans -= (l[i] > 0);
    
    cout << ans << endl;
    return 0;
}
