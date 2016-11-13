#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;


const int MAXN = 100010;

int x[MAXN];


int main() {
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);
    int N, K;
    cin >> N >> K;
    for (int i = 0; i < N; ++i) cin >> x[i];
    map<int, int> z;
    int ans = 0, cnt = 0;
    for (int i = 0, j = 0; i < N; ++i) {
        if (z[x[i]] == 0) ++cnt;
        ++z[x[i]];
        
        while (cnt > K + 1) {
            --z[x[j]];
            if (z[x[j]] == 0) --cnt;
            ++j;
        }
        
        ans = max(ans, z[x[i]]);
    }
    
    cout << ans << endl;
    
    return 0;
}
