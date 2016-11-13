#include <iostream>
#include <cstdio>
using namespace std;


int x[9][9];
int f[9][511][8];


bool check(int a) {
    int c = 0;
    while (a > 0) {
        c += (a & 1);
        a = a >> 1;     
    }
    
    return c % 2 == 0;
}

int diff(int a, int b) {
    int ans = 0;
    for (int i = 8; i >= 0; --i) {
        ans += (x[a][i] != b % 2);
        b = b / 2;
    }
    return ans;
}

int get(int b, int a) {
    int p[3];
    for (int i = 2; i >= 0; --i) {
        p[i] = 0;
        p[i] += b & 1; b /= 2;  
        p[i] += b & 1; b /= 2;  
        p[i] += b & 1; b /= 2;  
    }
    int ans = 0;
    if (p[0] % 2 == 1) ans += 4;
    if (p[1] % 2 == 1) ans += 2;
    if (p[2] % 2 == 1) ans += 1;
    return ans ^ a;
}


int main() {
    freopen("bsudoku.in", "r", stdin);
    freopen("bsudoku.out", "w", stdout);
    for (int i = 0; i < 9; ++i)
     for (int j = 0; j < 9; ++j) {
         char p;
         cin >> p;
         while (p != '0' && p != '1') cin >> p;
         x[i][j] = p - '0';    
     }
     
    for (int i = 0; i < 9; ++i)
     for (int j = 0; j < 511; ++j) 
      for (int k = 0; k < 8; ++k) {
         f[i][j][k] = 1000;
      }
      
    f[0][0][0] = 0;
    
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 511; ++j) {
            for (int k = 0; k < 511; ++k) 
             if (check(k)) {
                 if (i == 0) {
                     f[i][k][get(k, 0)] = diff(i, k);
                 } else
                 if (i == 3 || i == 6) {
                     f[i][k ^ j][get(k, 0)] = min(f[i][k ^ j][get(k, 0)], f[i - 1][j][0] + diff(i, k));
                 } else {
                     for (int l = 0; l < 8; ++l)
                      f[i][k ^ j][get(k, l)] = min(f[i][k ^ j][get(k, l)], f[i - 1][j][l] + diff(i, k));
                 }
            }
        }
    }
    
    cout << f[8][0][0] << endl;
    
    return 0;    
}
