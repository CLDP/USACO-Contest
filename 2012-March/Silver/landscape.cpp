#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 1010;
const int INF = 1000000000;

int f[MAXN][MAXN];


int main() {
    freopen("landscape.in", "r", stdin);
    freopen("landscape.out", "w", stdout);
    int n, X, Y, Z;
    cin >> n >> X >> Y >> Z;
    vector<int> p, q;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        for (int j = 0; j < a; ++j) p.push_back(i);
        for (int j = 0; j < b; ++j) q.push_back(i);
    }
    
    for (int i = 0; i <= p.size(); ++i)
     for (int j = 0; j <= q.size(); ++j) f[i][j] = INF;
     
    f[0][0] = 0;
    for (int i = 0; i < p.size(); ++i)
     for (int j = 0; j < q.size(); ++j) {
         f[i+1][j] = min(f[i+1][j], f[i][j] + Y);
         f[i][j+1] = min(f[i][j+1], f[i][j] + X);
         f[i+1][j+1] = min(f[i+1][j+1], f[i][j] + abs(p[i] - q[j]) * Z);
     }
    
    cout << f[p.size()][q.size()] << endl;
    
    return 0;
}
