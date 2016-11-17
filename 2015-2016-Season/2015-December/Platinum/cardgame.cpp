#include <iostream>
#include <set>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 50010;

int X[MAXN], Y[MAXN], Z[MAXN];

int main() {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);
    int N;
    cin >> N;
    set<int> S;
    for (int i = 0; i < N; ++i) {
        cin >> X[i];
        S.insert(X[i]);
    }
    set<int> C;
    for (int i = 1; i <= N + N; ++i) {
        if (S.find(i) == S.end()) C.insert(i);
    }
    int temp = 0;
    for (int i = 0; i < N; ++i) {
        set<int>::iterator iter = C.lower_bound(X[i] + 1);
        Y[i] = temp;
        if (iter == C.end()) continue;
        Y[i] = ++temp;
        C.erase(iter);
    }

    C.clear();
    for (int i = 1; i <= N + N; ++i) {
        if (S.find(i) == S.end()) C.insert(i);
    }
    temp = 0;
    for (int i = N - 1; i >= 0; --i) {
        set<int>::iterator iter = C.lower_bound(X[i] - 1);
        Z[i] = temp;
        if (iter == C.end() || *iter > X[i] - 1) {
            if (iter == C.begin()) continue;
            --iter;
        } 
        Z[i] = ++temp;
        C.erase(iter);
    }
    int ans = max(Y[N - 1], Z[0]);
    for (int i = 0; i < N; ++i) ans = max(ans, Y[i] + Z[i + 1]);

    cout << ans << endl;
    return 0;
}
