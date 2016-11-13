#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1010;

int x[MAXN], y[MAXN];
bool z[MAXN], ans[MAXN];



int main() {
    freopen("relay.in", "r", stdin);
    freopen("relay.out", "w", stdout);
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> x[i];
    for (int i = 1; i <= n; ++i) 
     if (!ans[i]) {
         if (i == 8) {
             i = 8;      
         }
         memset(z, 0, sizeof(z));
         m = 0;
         int j = i;
         while (j != 0 && !z[j] && !ans[j]) {
             z[j] = true;
             y[m] = j;
             ++m;
             j = x[j];
         }      
         if (j != 0) {
             for (int k = 0; k < m; ++k) ans[y[k]] = true; 
         }
     }
    
    int num = 0;
    for (int  i = 1; i <= n; ++i) 
     if (!ans[i]) ++num;
    cout << num << endl;
    
    
    
    return 0;   
