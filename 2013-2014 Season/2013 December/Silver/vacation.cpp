#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 201;
const long long INF = 2000000000;

long long x[MAXN][MAXN];



int main() {
    freopen("vacation.in", "r", stdin);
    freopen("vacation.out", "w", stdout);
    int n, m, K, q;
    cin >> n >> m >> K >> q;
    for (int i = 1; i <= n; ++i)
     for (int j = 1; j <= n; ++j)
      if (i != j) x[i][j] = INF;
    
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        x[a][b] = min(x[a][b], c);
    }
    
    for (int k = 1; k <= n; ++k)
     for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
       if (x[i][k] + x[k][j] < x[i][j]) x[i][j] = x[i][k] + x[k][j];
    
    int ans1 = 0;
    long long ans2 = 0;
    for (int i = 0; i < q; ++i) {
        int a, b;
        long long temp = INF;
        cin >> a >> b;
        for (int k = 1; k <= K; ++k)
         if (x[a][k] + x[k][b] < temp) temp = x[a][k] + x[k][b];
        
        if (temp < INF) {
            ++ans1;
            ans2 += temp;
        }
    }
    
    cout << ans1 << endl;
    cout << ans2 << endl;
    
    return 0;
}
