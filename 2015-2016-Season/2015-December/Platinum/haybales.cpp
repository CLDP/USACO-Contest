#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000000;
const long long INF = 1LL * 1000000000 * 1000000000;

long long x[MAXN], s[MAXN], y[MAXN];

int clear(int t, int l, int r) {
    if (s[t] == 0) return 0;
    s[t + t] += s[t];
    s[t + t + 1] += s[t];
    x[t] += s[t] * (r - l + 1);
    y[t + t] += s[t];
    y[t + t + 1] += s[t];
    s[t] = 0;
    return 0;
}

long long get(int t, int l, int r) {
    return x[t] + s[t] * (r - l + 1);
}

int insert(int a, int b, int l, int r, int c, int t) {
    if (a <= l && r <= b) {
        s[t] += c;
        y[t] += c;
        return 0;
    }
    if (b < l || r < a) return 0;
    clear(t, l, r);
    int mid = (l + r) >> 1;
    insert(a, b, l, mid, c, t + t);
    insert(a, b, mid + 1, r, c, t + t + 1);
    x[t] = get(t + t, l, mid) + get(t + t + 1, mid + 1, r);
    y[t] = min(y[t + t], y[t + t + 1]);
    return 0;
}

long long query_m(int a, int b, int l, int r, int t) {
    if (a <= l && r <= b) return y[t];
    if (b < l || r < a) return INF;
    clear(t, l, r);
    int mid = (l + r) >> 1;
    return min(query_m(a, b, l, mid, t + t), query_m(a, b, mid + 1, r, t + t + 1));
}

long long query_s(int a, int b, int l, int r, int t) {
    if (a <= l && r <= b) return get(t, l, r);
    if (b < l || r < a) return 0;
    clear(t, l, r);
    int mid = (l + r) >> 1;
    return query_s(a, b, l, mid, t + t) + query_s(a, b, mid + 1, r, t + t + 1);
}


int main() {
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    int N, M, a, b, c;
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        cin >> a;
        insert(i, i, 1, N, a, 1);
    }
    for (int i = 0; i < M; ++i) {
        char d;
        cin >> d;
        switch (d) {
            case 'P':  cin >> a >> b >> c; 
                       insert(a, b, 1, N, c, 1);
                       break;
            case 'M':  cin >> a >> b;
                       cout << query_m(a, b, 1, N, 1) << endl;
                       break;
            case 'S':  cin >> a >> b;
                       cout << query_s(a, b, 1, N, 1) << endl;
                       break;
        }
    }

    return 0;
}
