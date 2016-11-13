#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 2000000000;

int x[12], y[12], p[12], ans, n;
bool z[12];


bool check() {
    int cz[12];
    for (int k = 0; k < n; ++k) {
        memset(cz, 0, sizeof(cz));
        int i = k;
        cz[i] = 1;   
        while (true) {
            int temp = INF;
            int pos = -1;
            for (int j = 0; j < n; ++j) {
                if (j == i) continue;
                if (y[j] == y[i] && x[j] > x[i] && x[j] < temp) {
                    temp = x[j];
                    pos = j;
                }
            }
            if (pos == -1) break;
            i = pos;
            if (cz[i] == 2) return true;  ++cz[i];
            i = p[i];
            if (cz[i] == 2) return true;  ++cz[i];
        }
    }
    return false;
}


int dfs(int a) {
    if (a == n) {
        if (check()) ++ans;
        return 0;
    }
    if (z[a]) {
        dfs(a + 1);
        return 0;
    }
    z[a] = true;
    for (int i = a + 1; i < n; ++i) {
        if (z[i]) continue;
        z[i] = true;
        p[i] = a;
        p[a] = i;
        dfs(a + 1);
        z[i] = false;
    }
    z[a] = false;
    
    return 0;
}


int main() {
    freopen("wormhole.in", "r", stdin);
    freopen("wormhole.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
    dfs(0);
    cout << ans << endl;
    
    return 0;
}
