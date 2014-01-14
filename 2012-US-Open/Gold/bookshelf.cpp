#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int SIZE[MAXN];
long long H[MAXN], W[MAXN], ans[MAXN];

int main() {
    freopen("bookshelf.in", "r", stdin);
    freopen("bookshelf.out", "w", stdout);
    int N, L, *S = SIZE, pos = 0, total = 0, len = 0;
    multiset<long long> best;
    cin >> N >> L;
    for (int i = 1; i <= N; ++i) {
        cin >> H[i] >> W[i];
        S[++total] = 1;
        while (total > 1 && H[i - S[total]] <= H[i]) {
            best.erase(best.find(ans[i - S[total] - S[total-1]] + H[i - S[total]]));
            S[total - 1] += S[total];
            --total;
        }
        
        best.insert(H[i] + ans[i - S[total]]);
        
        len += W[i];
        while (len > L) {
            len -= W[++pos];
            best.erase(best.find(ans[pos - 1] + H[pos + S[1] - 1]));
            --S[1];
            if (S[1] == 0) {
                ++S;
                --total;
            } else {
                best.insert(ans[pos] + H[pos + S[1]]);
            }
        }
        
        ans[i] = *best.begin();
    }
    
    cout << ans[N] << endl;
    
    return 0;
}
