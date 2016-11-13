#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;


const int MAXN = 21;
const int MAXL = 16;
const int MAXK = 1001;

int n, k;
int combo_len[MAXN];
char combos[MAXN][MAXL];
int contains[MAXN][MAXL], attach[MAXN][MAXN];
int dp[MAXK][MAXN];


int main() {
    freopen("combos.in", "r", stdin);
    freopen("combos.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> combos[i];
        combo_len[i] = strlen(combos[i]);
    }
    
    memset(contains, 0, sizeof(contains));
    
    for (int i = 0; i < n; ++i) {
        contains[i][0] = 0;
        for (int r = combo_len[i], len = 0; r >= 0; --r, ++len) {
            int num = 0;
            
            for (int j = 0; j < n; ++j)
             if (r >= combo_len[j] && strncmp(combos[i] + r - combo_len[j], combos[j], combo_len[j]) == 0)
                 ++num;
            
            contains[i][len + 1] = contains[i][len] + num;
        }
    }
    
    for (int i = 0; i < n; ++i)
     for (int j = 0; j < n; ++j)
      for (int len = max(1, combo_len[j] - combo_len[i]); len <= combo_len[j]; ++len) 
       if (strncmp(combos[i] + combo_len[i] - (combo_len[j] - len), combos[j], combo_len[j] - len) == 0) {
           attach[i][j] = len;
           break;
       }
    
    memset(dp, -63, sizeof(dp));
    
    for (int i = 0; i < n; ++i) dp[combo_len[i]][i] = contains[i][combo_len[i]];
    
    int ans = 0;
    for (int t = 0; t <= k; ++t) 
     for (int i = 0; i < n; ++i)
      if (dp[t][i] >= 0) {
          if (dp[t][i] > ans) ans = dp[t][i];
          for (int j = 0; j < n; ++j) {
              int tmp = t + attach[i][j];
              if (tmp <= k) dp[tmp][j] = max(dp[tmp][j], dp[t][i] + contains[j][attach[i][j]]);
          }
      }
    
    cout << ans << endl;

    return 0;
}
