#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int INF = 1000000000;

int N, A, B;
vector<int> x, y;
int f[MAXN][MAXN][2];
bool z[MAXN][MAXN][2];


int dp(int a, int b, int c) {
    if (z[a][b][c]) return f[a][b][c];
    z[a][b][c] = true;
    f[a][b][c] = INF;
    if (a == 0) {
        if (c == 1) {
            f[a][b][c] = 0;
            for (int i = 1; i <= b; ++i) f[a][b][c] -= (y[i] - y[i-1]) * (A + B - 1 - i);
        }
        return f[a][b][c];
    }
    if (b == 0) {
        if (c == 0) {
            f[a][b][c] = 0;
            for (int i = 1; i <= a; ++i) f[a][b][c] += (x[i] - x[i-1]) * (A + B - 1 - i);
        }
        return f[a][b][c];
    }
    
    if (c == 0) {
        f[a][b][c] = min(f[a][b][c], dp(a-1, b, 0) + (x[a] - x[a-1]) * (A + B - 1 - a - b));
        f[a][b][c] = min(f[a][b][c], dp(a-1, b, 1) + (x[a] - y[b]) * (A + B - 1 - a - b));
    } else {
        f[a][b][c] = min(f[a][b][c], dp(a, b-1, 0) + (x[a] - y[b]) * (A + B - 1 - a - b));
        f[a][b][c] = min(f[a][b][c], dp(a, b-1, 1) + (y[b-1] - y[b]) * (A + B - 1 - a - b));
    }
    
    return f[a][b][c];
}


int main() {
    freopen("cowrun.in", "r", stdin);
    freopen("cowrun.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        if (a > 0) x.push_back(a); else y.push_back(a);
    }
    x.push_back(0);
    y.push_back(0);
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    reverse(y.begin(), y.end());
    
    A = x.size();
    B = y.size();
    cout << min(dp(A - 1, B - 1, 0), dp(A - 1, B - 1, 1)) << endl;
    
    return 0;
}

