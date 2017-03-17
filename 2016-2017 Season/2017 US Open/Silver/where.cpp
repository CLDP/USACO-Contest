#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

struct node {
    int a, b, c, d;
    bool mark;
    node() {}
    node(int _a, int _b, int _c, int _d): a(_a), b(_b), c(_c), d(_d), mark(false) {}
    bool operator < (const node &B) const {
        return (c - a + 1) * (d - b + 1) < (B.c - B.a + 1) * (B.d - B.b + 1);
    }
};

string X[21];
vector<node> Y;
bool Z[20][20];


void dfs(int &a, int &b, int &c, int &d, int i, int j) {
    Z[i][j] = true;
    if (i > a && !Z[i - 1][j] && X[i - 1][j] == X[i][j]) dfs(a, b, c, d, i - 1, j);
    if (i < c && !Z[i + 1][j] && X[i + 1][j] == X[i][j]) dfs(a, b, c, d, i + 1, j);
    if (j > b && !Z[i][j - 1] && X[i][j - 1] == X[i][j]) dfs(a, b, c, d, i, j - 1);
    if (j < d && !Z[i][j + 1] && X[i][j + 1] == X[i][j]) dfs(a, b, c, d, i, j + 1);
}

bool check(int a, int b, int c, int d) {
    char A = ' ', B = ' ';
    for (int i = a; i <= c; ++i) {
        for (int j = b; j <= d; ++j) {
            if (A == X[i][j] || B == X[i][j]) continue;
            if (A == ' ') {
                A = X[i][j];
                continue;
            }
            if (B == ' ') {
                B = X[i][j];
                continue;
            }
            return false;
        }
    }
    memset(Z, 0, sizeof(Z));
    int CA = 0, CB = 0;
    for (int i = a; i <= c; ++i) {
        for (int j = b; j <= d; ++j) {
            if (!Z[i][j]) {
                dfs(a, b, c, d, i, j);
                if (X[i][j] == A) ++CA; else ++CB;
            }
        }
    }
    return (CA == 1 && CB > 1) || (CA > 1 && CB == 1);
}

bool inside(const node &A, const node &B) {
    return B.a <= A.a && B.b <= A.b && A.c <= B.c && A.d <= B.d;
}

int main() {
    freopen("where.in", "r", stdin);
    freopen("where.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> X[i];

    for (int i = 0; i < N; ++i) {
        for (int k = i; k < N; ++k) {
            for (int j = 0; j < N; ++j) {
                int l = N - 1;
                while (l >= j && !check(i, j, k, l)) --l;
                if (l >= j) Y.push_back(node(i, j, k, l));
            }
        }
    }
    if (Y.size() == 0) {
        cout << 0 << endl;
        return 0;
    }

    sort(Y.begin(), Y.end());
    for (int i = Y.size() - 1; i >= 0; --i) {
        if (Y[i].mark) continue;
        for (int j = i - 1; j >= 0; --j) {
            if (Y[j].mark) continue;
            if (inside(Y[j], Y[i])) Y[j].mark = true;
        }
    }
    int ans = 0;
    for (int i = 0; i < Y.size(); ++i) ans += (!Y[i].mark);
    cout << ans << endl;

    return 0;
}
