#include <cstdio>

const int MAXN = 110;

bool x[MAXN][MAXN];
bool z[MAXN][MAXN];
int qx[MAXN*MAXN], qy[MAXN*MAXN];



int main() {
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);
    int n, a, b;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a, &b);
        x[a][b] = true;
    }
    
    int l = 0, r = 1;
    qx[0] = 0;
    qy[0] = 0;
    z[0][0] = true;
    while (l < r) {
        a = qx[l];
        b = qy[l];
        ++l;
        if (a <= 100 && !z[a+1][b] && !x[a+1][b]) {
            z[a+1][b] = true;
            qx[r] = a+1;
            qy[r] = b; 
            ++r;
        }   
        if (a > 0 && !z[a-1][b] && !x[a-1][b]) {
            z[a-1][b] = true;
            qx[r] = a-1;
            qy[r] = b; 
            ++r;
        }     
        if (b <= 100 && !z[a][b+1] && !x[a][b+1]) {
            z[a][b+1] = true;
            qx[r] = a;
            qy[r] = b+1; 
            ++r;
        }
        if (b > 0 && !z[a][b-1] && !x[a][b-1]) {
            z[a][b-1] = true;
            qx[r] = a;
            qy[r] = b-1; 
            ++r;
        }     
    }
    for (int i = 1; i <= 100; ++i)
     for (int j = 1; j <= 100; ++j)
      if (!z[i][j]) x[i][j] = true;
    
    
    int ans = 0;
    for (int i = 1; i <= 100; ++i) 
     for (int j = 1; j <= 100; ++j)
      if (x[i][j]) {
          if (!x[i-1][j]) ++ans;
          if (!x[i+1][j]) ++ans;
          if (!x[i][j-1]) ++ans;
          if (!x[i][j+1]) ++ans;             
      }
    
    printf("%d\n", ans);
    
    
    return 0;   
}
