#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 11;
const int MAXM = 10010;
const int INF = 1000000000;

int n, m;
int f[MAXN][MAXM];
int x[MAXN];


int main() {
    freopen("tilechng.in", "r", stdin);
    freopen("tilechng.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> x[i];
    for (int i = 0; i < n; ++i)
     for (int j = 0; j <= m; ++j) f[i][j] = INF;
    
    for (int j = 0; j*j <= m; ++j) f[0][j*j] = (x[0]-j)*(x[0]-j);
    
    for (int i = 1; i < n; ++i)
     for (int j = 0; j*j <= m; ++j) 
      for (int k = 0; k <= m-j*j; ++k) 
       f[i][k+j*j] = min(f[i][k+j*j], f[i-1][k] + (x[i]-j)*(x[i]-j));
         
    
    if (f[n-1][m] != INF)
        cout << f[n-1][m] << endl;
    else
        cout << -1 << endl;
    
    return 0;    
}
