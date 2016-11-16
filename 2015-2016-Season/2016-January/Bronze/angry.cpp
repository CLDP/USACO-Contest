#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int X[110];

int main() {
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);
    int N; 
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> X[i];
    sort(X, X + N);
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int L = i, S = 1, R = i;
        int cnt = 1;
        int C = X[i];
        while (true) {
            bool flag = true;
            while (L > 0 && C - X[L - 1] <= S) {
                ++cnt;
                --L;
                flag = false;
            }
            if (flag) break;
            ++S;
            C = X[L];
        }
        S = 1, C = X[i];
        while (true) {
            bool flag = true;
            while (R < N - 1 && X[R + 1] - C <= S) {
                ++cnt;
                ++R;
                flag = false;
            }
            if (flag) break;
            ++S;
            C = X[R];
        }
        ans = max(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}
