#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MAXN = 302;

int N;
string x[MAXN];
int l[MAXN][MAXN], f[MAXN][MAXN][MAXN], g[MAXN][MAXN][MAXN], h[MAXN][MAXN][MAXN];



int main() {
    freopen("eight.in", "r", stdin);
    freopen("eight.out", "w", stdout);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> x[i];
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < N; ++j) {
         l[i+1][j+1] = x[i][j] == '.' ? l[i+1][j] + 1 : 0;
     }
    
    for (int i = 0; i < N - 2; ++i)
     for (int j = i + 2; j < N; ++j) {
         for (int k = 0; k < N; ++k) g[i][j][k] = h[i][j][k] = k;
         
         int U = 0, D = 0;
         while (U < N) {
             while (U < N && l[U+1][j+1] < j - i + 1) ++U;
             if (U == N) break;
             D = U + 1;
             int DD = -1;
             while (D < N && x[D][i] == '.' && x[D][j] == '.') {
                 if (l[D+1][j+1] >= j - i + 1 && D - U > 1) DD = D;
                 ++D;
             }
             if (DD == -1) {
                 U = D;
                 continue;
             }
             
             while (U < D && x[U][i] == '.' && x[U][j] == '.') {
                 if (l[U+1][j+1] >= j - i + 1 && D - U > 1) g[i][j][U] = DD;
                 ++U;
             }
         }
         
         U = N - 1;
         while (U >= 0) {
             while (U >= 0 && l[U+1][j+1] < j - i + 1) --U;
             if (U == 0) break;
             D = U - 1;
             int DD = -1;
             while (D >= 0 && x[D][i] == '.' && x[D][j] == '.') {
                 if (l[D+1][j+1] >= j - i + 1 && U - D > 1) DD = D;
                 --D;
             }
             if (DD == -1) {
                 U = D;
                 continue;
             }
             
             while (U > D && x[U][i] == '.' && x[U][j] == '.') {
                 if (l[U+1][j+1] >= j - i + 1 && U - D > 1) h[i][j][U] = DD;
                 --U;
             }
         }
     }
    
    int ans = 0;
    // left = j, right = j + i, mid = k
    for (int i = 2; i < N; ++i)
     for (int j = 0; j < N - i; ++j) {
         for (int k = 2; k < N - 2; ++k) {
             f[j][j+i][k] = max(f[j+1][j+i][k], f[j][j+i-1][k]);
             f[j][j+i][k] = max(f[j][j+i][k], (i - 1) * (k - h[j][j+i][k] - 1));
             if (g[j][j+i][k] == 0) continue;
             ans = max(ans, (i - 1) * (g[j][j+i][k] - k - 1) * f[j][j+i][k]);
         }
     }
    
    if (ans == 0) ans = -1;
    cout << ans << endl;
     
    return 0;
}

