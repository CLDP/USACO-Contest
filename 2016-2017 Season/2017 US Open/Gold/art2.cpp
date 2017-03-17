#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

struct node {
    int L, R, N;
    node() { L = R = MAXN; }
};

struct event {
    int a, b, c;
    event() {}
    event(int _a, int _b, int _c): a(_a), b(_b), c(_c) {}
    bool operator < (const event &B) const {
        if (a != B.a) return a < B.a;
        if (b != B.b) return b < B.b;
        return c < B.c;
    }
};

node X[MAXN];

int main() {
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        if (X[a].L == MAXN) {
            X[a].L = X[a].R = i;
        } else {
            X[a].R = i;
        }
    }

    vector<event> Y;
    for (int i = 1; i <= N; ++i) {
        if (X[i].L == MAXN) continue;
        Y.push_back(event(X[i].L, -1, i));
        Y.push_back(event(X[i].R, 1, i));
    }
    int ans = 0;
    sort(Y.begin(), Y.end());
    stack<int> S;
    for (int i = 0; i < Y.size(); ++i) {
        if (Y[i].b == -1) {
            S.push(Y[i].c);
            continue;
        }
        ans = max(ans, (int)S.size());
        if (S.top() != Y[i].c) {
            cout << -1 << endl;
            return 0;
        }
        S.pop();
    }
    cout << ans << endl;

    return 0;
}
