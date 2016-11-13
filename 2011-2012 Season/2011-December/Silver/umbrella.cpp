#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 5001;
const int MAXM = 100001;

int n, m;
int x[MAXN], w[MAXM], f[MAXN];


int main() {
    freopen("umbrella.in", "r", stdin);
    freopen("umbrella.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> x[i];
    for (int j = 0; j < m; ++j) cin >> w[j];
    for (int j = m - 1; j >= 1; --j) 
     if (w[j] < w[j-1]) w[j-1] = w[j];
    
    sort(x, x + n);
    
    f[0] = w[0];
    
    for (int i = 1; i < n; ++i) { 
        f[i] = w[x[i] - x[0]];
        for (int j = 0; j < i; ++j) 
         if (f[j] + w[x[i] - x[j + 1]] < f[i]) f[i] = f[j] + w[x[i] - x[j + 1]];
    }
    
    cout << f[n-1] << endl;
    
    return 0;
}
