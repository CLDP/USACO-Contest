#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int N, W;
int x[18];
int f[1 << 18], fa[1 << 18];

int cal(int a) {
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (a & (1 << i)) ans += x[i];
    }
    return ans;
}

int main() {
    freopen("skyscraper.in", "r", stdin);
    freopen("skyscraper.out", "w", stdout);
    cin >> N >> W;
    for (int i = 0; i < N; ++i) cin >> x[i];
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < (1 << N); ++j) {
            int temp = cal(j);
            if (temp - f[j] <= W) f[j] = temp;
        }
        
        if (f[(1 << N) - 1] == cal((1 << N) - 1)) {
            cout << i << endl;
            int a = (1 << N) - 1;
            while (a != 0) {
                int b = fa[a];
                vector<int> ans;
                for (int i = 0; i < N; ++i) 
                 if ((a & (1 << i)) && !(b & (1 << i))) ans.push_back(i);
                
                cout << ans.size();
                for (int i = 0; i < ans.size(); ++i) cout << " " << ans[i] + 1;
                cout << endl;
                
                a = b;
            }
            break;
        }
        
        for (int j = 1; j < N; ++j) {
            vector<int> t(N - j, 0);
            for (int k = 0; k < j; ++k) t.push_back(1);
            int begin = 0;
            for (int k = 0; k < N; ++k) begin += t[k] * (1 << k);
            
            while (true) {
                next_permutation(t.begin(), t.end());
                int a = 0;
                for (int k = 0; k < N; ++k) a += t[k] * (1 << k);
                if (a == begin) break;
                for (int k = 0; k < N; ++k) {
                    if (t[k] == 1) continue;
                    int now = a + (1 << k);
                    if (f[a] > f[now]) {
                        f[now] = f[a];
                        int b = a;
                        while (f[now] == f[b]) {
                            fa[now] = b;
                            b = fa[b];
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}
