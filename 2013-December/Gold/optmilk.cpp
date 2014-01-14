#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 40010;
const int MAXM = 200000;
const int INF = 1000000000;

int N, D, nn;
long long x[MAXN];
// s1 - no left, no right,   s2 - left, no right
// s3 - no left, right,      s4 - left, right
int l[MAXM], r[MAXM];
long long s1[MAXM], s2[MAXM], s3[MAXM], s4[MAXM];


int build(int a, int b) {
    int k = ++nn, mid = (a + b) >> 1;
    if (a < b) {
        l[k] = nn + 1;
        build(a, mid);
        r[k] = nn + 1;
        build(mid + 1, b);
        s1[k] = max(s1[l[k]] + max(s1[r[k]], s2[r[k]]), s3[l[k]] + s1[r[k]]);
        s2[k] = max(s2[l[k]] + max(s1[r[k]], s2[r[k]]), s4[l[k]] + s1[r[k]]);
        s3[k] = max(s1[l[k]] + max(s3[r[k]], s4[r[k]]), s3[l[k]] + s3[r[k]]);
        s4[k] = max(s2[l[k]] + max(s3[r[k]], s4[r[k]]), s4[l[k]] + s3[r[k]]);
    } else {
        s1[k] = 0;
        s2[k] = s3[k] = -INF;
        s4[k] = x[a];
    }
    return 0;
}


int update(int t, int a, int c, int d, long long val) {
    if (a == c && d == a) {
        s1[t] = 0;
        s2[t] = s3[t] = -INF;
        s4[t] = val;
        return 0;
    }
    
    int mid = (c + d) >> 1;
    if (a <= mid) update(l[t], a, c, mid, val);
    if (mid + 1 <= a) update(r[t], a, mid + 1, d, val);
    
    s1[t] = max(s1[l[t]] + max(s1[r[t]], s2[r[t]]), s3[l[t]] + s1[r[t]]);
    s2[t] = max(s2[l[t]] + max(s1[r[t]], s2[r[t]]), s4[l[t]] + s1[r[t]]);
    s3[t] = max(s1[l[t]] + max(s3[r[t]], s4[r[t]]), s3[l[t]] + s3[r[t]]);
    s4[t] = max(s2[l[t]] + max(s3[r[t]], s4[r[t]]), s4[l[t]] + s3[r[t]]);
    
    return 0;
}


int main() {
    freopen("optmilk.in", "r", stdin);
    freopen("optmilk.out", "w", stdout);
    cin >> N >> D;
    for (int i = 1; i <= N; ++i) cin >> x[i];
    build(1, N);
    
    long long ans = 0;
    for (int i = 0; i < D; ++i) {
        int a, b;
        cin >> a >> b;
        update(1, a, 1, N, b);
        ans += max(max(s1[1], s2[1]), max(s3[1], s4[1]));
    }
    
    cout << ans << endl;
    
    return 0;
}
