#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 501;
const int INF = 1000000000;
const int MX[4] = {-1, 0, 0, 1};
const int MY[4] = {0, -1, 1, 0};

int N, M;
int x[MAXN][MAXN];
bool z[MAXN][MAXN];

int dfs(int a, int b, int D) {
    z[a][b] = true;
    int temp = 1;
    for (int i = 0; i < 4; ++i) {
        if (a + MX[i] < 0 || a + MX[i] >= N) continue;
        if (b + MY[i] < 0 || b + MY[i] >= N) continue;
        if (z[a + MX[i]][b + MY[i]]) continue;
        if (abs(x[a][b] - x[a + MX[i]][b + MY[i]]) > D) continue;
        temp += dfs(a + MX[i], b + MY[i], D);
    }
    return temp;
}


bool check(int a) {
    memset(z, 0, sizeof(z));
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < N; ++j) {
         if (z[i][j]) continue;
         if (dfs(i, j, a) >= M) return true;
     }
    
    return false;
}


int main() {
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);
    int L = 0, R = 0;
    cin >> N;
    if (N & 1) M = N * N / 2 + 1; else M = N * N / 2;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < N; ++j) {
         cin >> x[i][j];
         R = max(R, x[i][j]);
     }
    
    if (check(0)) {
        cout << 0 << endl;
        return 0;
    }
    
    while (L + 1 < R) {
        int mid = (L + R) >> 1;
        if (check(mid)) R = mid; else L = mid;
    }
    
    cout << R << endl;
   
    return 0;
}

