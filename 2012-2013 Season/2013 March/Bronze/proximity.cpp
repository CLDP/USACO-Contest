#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000010;

vector<int> x[MAXN];

int main() {
    freopen("proximity.in", "r", stdin);
    freopen("proximity.out", "w", stdout);
    int n, k, a, b = 0;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a;
        x[a].push_back(i);
        if (a > b) b = a;
    }
    
    for (int i = b; i >= 0; --i)
     if (x[i].size() > 1) {
         sort(x[i].begin(), x[i].end());
         for (int j = 0; j < x[i].size()-1; ++j) 
          if (x[i][j] + k >= x[i][j+1]) {
              cout << i << endl;
              return 0;            
          }                   
     }
    
    cout << -1 << endl;
    return 0;    
}

