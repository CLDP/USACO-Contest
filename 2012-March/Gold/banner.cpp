#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 100001;
const int MAXM = 10;

long long M, N, L, H, B, A, B1, B2, ans;
vector<long long> prime_div[MAXN];
bool z[MAXM];

long long deal(const int &len, const int &pos, const bool plus, const long long &num) {
    if (len == 0) {
        long long C1 = B1 / num * num, C2 = B2 / num * num;
        if (C1 == 0) C1 += num;
        if (C1 < B1) C1 += num;
        if (C1 > C2) return 0;
        
        long long temp = (M - A + 1) * (N + 1) * ((C2 - C1) / num + 1) * 2;
        temp -= (M - A + 1) * (C1 + C2) * ((C2 - C1) / num + 1);
        if (plus) ans += temp; else ans -= temp;
        return 0;
    }
    int lenC = prime_div[A].size();
    for (int i = pos; i < lenC - len + 1; ++i) {
        z[i] = true;
        deal(len - 1, i + 1, plus, num * prime_div[A][i]);
        z[i] = false;
    }
    return 0;
}


int main() {
    freopen("banner.in", "r", stdin);
    freopen("banner.out", "w", stdout);
    cin >> M >> N >> L >> H >> B;
    
    vector<bool> notP(MAXN, false);
    vector<int> prime;
    for (int i = 2; i < MAXN; ++i) {
        if (!notP[i]) {
            prime.push_back(i);
            int j = 1;
            while (i * j < MAXN) {
                notP[i * j] = true;
                prime_div[i * j].push_back(i);
                ++j;
            }
        }
    }
    int P = prime.size();
    
    if (L < N) {
        A = 0;
    } else {
        A = sqrt(L * L - N * N);
    }
    for ( ; A <= min(M, H); ++A) {
        if (A == 0) {
            if (L == 1) ans += (M + 1) * N % B;
            continue;
        }
        if (A == H) {
            if (H == 1) ans += (N + 1) * M % B;
            continue;
        }
        
        if (A <= L) {
            B1 = sqrt(L * L - A * A);
            while (A * A + B1 * B1 < L * L) ++B1;
        } else {
            B1 = 0;
        }
        
        B2 = sqrt(H * H - A * A);
        if (A * A + (B2+1) * (B2+1) <= H * H) ++B2;
        
        if (B1 == 0) {
            if (A == 1) ans += (N + 1) * M % B;
            B1 = 1;
        }
        if (B2 > N) B2 = N;
        
        if (B1 > B2) continue;
        
        ans += (M - A + 1) * (N + 1) * (B2 - B1 + 1) * 2;
        ans -= (M - A + 1) * (B1 + B2) * (B2 - B1 + 1);
        
        bool flag = false;
        int lenC = prime_div[A].size();
        for (int i = 1; i <= lenC; ++i) {
            deal(i, 0, flag, 1);
            flag = !flag;
        }
        
        ans %= B;
        if (ans < 0) ans += B;
    }
    
    cout << ans << endl;
    
    return 0;
}
