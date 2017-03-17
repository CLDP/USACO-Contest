#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 1010;

struct node {
    int x1, x2, y1, y2;
    node() {
        x1 = 10000, x2 = -1, y1 = 10000, y2 = -1;
    }

    void update(int a, int b) {
        x1 = min(x1, a);
        x2 = max(x2, a);
        y1 = min(y1, b);
        y2 = max(y2, b);
    }
};

struct event {
    int x1, x2;
    int in;

    event() {}
    event(int _x1, int _x2, int _in): x1(_x1), x2(_x2), in(_in) {}
};


int v[MAXN];
int X[MAXN][MAXN];
node Y[MAXN * MAXN];
vector<event> Z[MAXN];
bool ans[MAXN * MAXN];


void update(int a, int b, int c) {
    for (int i = a; i < MAXN; i += (i & -i)) v[i] += c;
    for (int i = b + 1; i < MAXN; i += (i & -i)) v[i] -= c;
}

int query(int a) {
    int ans = 0;
    for (int i = a; i > 0; i -= (i & -i)) ans += v[i];
    return ans;
}

int main() {
    freopen("art.in", "r", stdin);
    freopen("art.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> X[i][j];
            if (X[i][j] > 0) Y[X[i][j]].update(i, j);
            ans[X[i][j]] = true;
        }
    }
    int cnt = 0;
    for (int i = 1; i <= N * N; ++i) cnt += ans[i];
    if (cnt == 1) {
        cout << N * N - 1 << endl;
        return 0;
    }
    memset(ans, 0, sizeof(ans));

    for (int i = 1; i <= N * N; ++i) {
        if (Y[i].x1 == 10000) continue;
        Z[Y[i].x1].push_back(event(Y[i].y1, Y[i].y2, 1));
        Z[Y[i].x2 + 1].push_back(event(Y[i].y1, Y[i].y2, -1));
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < Z[i].size(); ++j) {
            update(Z[i][j].x1, Z[i][j].x2, Z[i][j].in);
        }
        for (int j = 1; j <= N; ++j) {
            if (query(j) > 1) ans[X[i][j]] = true;
        }
    }

    cnt = 0;
    for (int i = 1; i <= N * N; ++i) {
        if (ans[i]) continue;
        ++cnt;
    }
    cout << cnt << endl;

    return 0;
}
