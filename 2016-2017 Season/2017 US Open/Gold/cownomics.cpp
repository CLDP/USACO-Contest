#include <iostream>
#include <string>
#include <unordered_set>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 510;
const int INF = 100000007;

string X[MAXN], Y[MAXN];
int x[MAXN], y[MAXN], B[MAXN];

int change(char C) {
    switch (C) {
        case 'A' : return 0;
        case 'C' : return 1;
        case 'T' : return 2;
        case 'G' : return 3;
    }
    return -1;
}

void add(int &a, int b) {
    a = ((a + b) % INF + INF) % INF;
}

int main() {
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> X[i];
    for (int i = 0; i < N; ++i) cin >> Y[i];
    B[0] = 1;
    for (int i = 1; i <= M; ++i) B[i] = B[i - 1] * 4 % INF;

    int L = 0, R = M;
    while (L + 1 < R) {
        int mid = (L + R) / 2;
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < mid; ++j) x[i] = (x[i] * 4 + change(X[i][j])) % INF;
            for (int j = 0; j < mid; ++j) y[i] = (y[i] * 4 + change(Y[i][j])) % INF;
        }
        bool flagR = false;
        for (int i = mid; i <= M; ++i) {
            unordered_set<int> S;
            for (int j = 0; j < N; ++j) S.insert(x[j]);
            bool flag = true;
            for (int j = 0; j < N; ++j) {
                if (S.find(y[j]) == S.end()) continue;
                flag = false;
                break;
            }
            if (flag) {
                flagR = true;
                break;
            }
            if (i == M) break;
            for (int j = 0; j < N; ++j) {
                add(x[j], -B[mid - 1] * change(X[j][i - mid]));
                x[j] = (x[j] * 4 + change(X[j][i]));
                add(y[j], -B[mid - 1] * change(Y[j][i - mid]));
                y[j] = (y[j] * 4 + change(Y[j][i]));
            }
        }
        if (flagR) R = mid; else L = mid;
    }
    cout << R << endl;
    return 0;
}
