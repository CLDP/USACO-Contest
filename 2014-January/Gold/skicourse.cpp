#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 101;

int N, M;
int x[MAXN][MAXN], y[MAXN][MAXN], y2[MAXN][MAXN];
int l0[MAXN][MAXN], u0[MAXN][MAXN], f0[MAXN][MAXN];
int l1[MAXN][MAXN], u1[MAXN][MAXN], f1[MAXN][MAXN];
int l2[MAXN][MAXN], u2[MAXN][MAXN], f2[MAXN][MAXN];


int dp(int &R, int &P1, int &P2, int &T) {
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= M; ++j) {
         if (y[i][j] == 0) {
             u0[i][j] = u0[i-1][j] + 1;
             u1[i][j] = u1[i-1][j] + 1;
             u2[i][j] = u2[i-1][j] + 1;
             l0[i][j] = l0[i][j-1] + 1;
             l1[i][j] = l1[i][j-1] + 1;
             l2[i][j] = l2[i][j-1] + 1;
             f0[i][j] = min(f0[i-1][j-1] + 1, min(l0[i][j], u0[i][j]));
             f1[i][j] = min(f1[i-1][j-1] + 1, min(l1[i][j], u1[i][j]));
             f2[i][j] = min(f2[i-1][j-1] + 1, min(l2[i][j], u2[i][j]));
         } else 
         if (y[i][j] == 1) {
             u0[i][j] = u2[i][j] = 0;
             u1[i][j] = u1[i-1][j] + 1;
             l0[i][j] = l2[i][j] = 0;
             l1[i][j] = l1[i][j-1] + 1;
             f0[i][j] = f2[i][j] = 0;
             f1[i][j] = min(f1[i-1][j-1] + 1, min(l1[i][j], u1[i][j]));
         } else {
             u0[i][j] = u1[i][j] = 0;
             u2[i][j] = u2[i-1][j] + 1;
             l0[i][j] = l1[i][j] = 0;
             l2[i][j] = l2[i][j-1] + 1;
             f0[i][j] = f1[i][j] = 0;
             f2[i][j] = min(f2[i-1][j-1] + 1, min(l2[i][j], u2[i][j]));
         }
         if (f1[i][j] > R && f0[i][j] != f1[i][j]) {
             R = f1[i][j];
             P1 = i;
             P2 = j;
             T = 1;
         }
         if (f2[i][j] > R && f0[i][j] != f2[i][j]) {
             R = f2[i][j];
             P1 = i;
             P2 = j;
             T = 2;
         }
     }
     return 0;
}

bool check(int mid) {
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= M; ++j) y[i][j] = x[i][j];
     
    int ans = N * M;
    while (ans > 0) {
        int R = 0, P1, P2, T;
        dp(R, P1, P2, T);
        if (R < mid) return false;
        for (int i = P1 - R + 1; i <= P1; ++i)
         for (int j = P2 - R + 1; j <= P2; ++j) 
          if (y[i][j] != 0) {
              y[i][j] = 0;
              --ans;
          }
    }
    return true;
}


int main() {
    freopen("skicourse.in", "r", stdin);
    freopen("skicourse.out", "w", stdout);
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        string p;
        cin >> p;
        for (int j = 1; j <= M; ++j) x[i][j] = p[j - 1] == 'R' ? 1 : -1;
    }
    for (int i = 0; i <= N; ++i) x[i][0] = -2;
    for (int j = 0; j <= M; ++j) x[0][j] = -2;
    
    for (int i = 0; i <= N; ++i)
     for (int j = 0; j <= M; ++j) y[i][j] = x[i][j];
    
    int L = 1, R = 0, P1, P2, T;
    dp(R, P1, P2, T);
    
    ++R;
    while (L + 1 < R) {
        int mid = (L + R) >> 1;
        if (check(mid)) L = mid; else R = mid;
    }
    
    cout << L << endl;
    
    return 0;
}
