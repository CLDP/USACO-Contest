#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100001;

int N, M, K;
long long S;
vector<int> X[MAXN];
int Y[MAXN];

void search(int P, long long T) { 
    if (M >= K) return ;
    if (P != -1 && T < X[P][0]) {
        P = upper_bound(Y, Y + P, (int)T) - Y - 1;
    }
    if (P == -1) {
        ++M;
        return ;
    }
    search(P - 1, T);
    for (int i = 0; i < X[P].size() && X[P][i] <= T; ++i) {
        search(P - 1, T - X[P][i]);
    }
}

void count(int P, long long T) {
    if (P != -1 && T < X[P][0]) {
        P = upper_bound(Y, Y + P, (int)T) - Y - 1;
    }
    if (P == -1) {
        S += T + 1;
        return ;
    }
    count(P - 1, T);
    for (int i = 0; i < X[P].size() && X[P][i] <= T; i++) {
        count(P - 1, T - X[P][i]);
    }
}

int Z[11];

int main() {
    ios_base::sync_with_stdio(false);
    freopen("roboherd.in", "r", stdin);
    freopen("roboherd.out", "w", stdout);
    cin >> N >> K;
    long long ans = 0, L = 0, R = 0;
    for (int i = 0; i < N; ++i) {
        cin >> M;
        for (int j = 0; j < M; ++j) cin >> Z[j];
        sort(Z, Z + M);
        ans += Z[0];
        if (M == 1) {
            --i;
            --N;
            continue;
        }
        for (int j = 1; j < M; ++j) X[i].push_back(Z[j] - Z[0]);
        R += X[i].back();
    }

    sort(X, X + N);
    for (int i = 0; i < N; ++i) Y[i] = X[i][0];

    while (L < R) {
        long long mid = (L + R) >> 1;
        M = 0;
        search(N - 1, mid);
        if (M >= K) {
            R = mid;
        } else {
            L = mid + 1;
        }
    }
    if (R > 0) count(N - 1, R - 1);
    cout << (ans + R) * K - S << endl;

    return 0;
}
