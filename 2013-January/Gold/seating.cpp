#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1200000;

int N, K, nn;
int l[MAXN], r[MAXN], l0[MAXN], r0[MAXN], k[MAXN], bj[MAXN];

int build(int a, int b) {
    int t = ++nn;
    if (a != b) {
        int mid = (a + b) >> 1;
        l[t] = nn + 1;
        build(a, mid);
        r[t] = nn + 1;
        build(mid + 1, b);
        l0[t] = r0[t] = k[t] = l0[l[t]] + l0[r[t]];
    } else {
        l0[t] = r0[t] = k[t] = 1;
    }
    
    return 0;
}

int clear(int t, int c, int d) {
    if (bj[t] == 1) {
        // Insert note
        bj[l[t]] = 1;
        bj[r[t]] = 1;
        bj[t] = 0;
        l0[l[t]] = r0[l[t]] = k[l[t]] = 0;
        l0[r[t]] = r0[r[t]] = k[r[t]] = 0;
    } else {
        // Delete note
        bj[l[t]] = -1;
        bj[r[t]] = -1;
        bj[t] = 0;
        int mid = (c + d) >> 1;
        l0[l[t]] = r0[l[t]] = k[l[t]] = mid - c + 1;
        l0[r[t]] = r0[r[t]] = k[r[t]] = d - mid;
    }
    return 0;
}


int update(int t, int c, int d) {
    int mid = (c + d) >> 1;
    if (l0[l[t]] == mid - c + 1) {
        l0[t] = l0[l[t]] + l0[r[t]];
    } else {
        l0[t] = l0[l[t]];
    }
    if (r0[r[t]] == d - mid) {
        r0[t] = r0[r[t]] + r0[l[t]];
    } else {
        r0[t] = r0[r[t]];
    }
    
    k[t] = max(r0[l[t]] + l0[r[t]], max(k[l[t]], k[r[t]]));
    
    return 0;
}


int insert_help(int t, int a, int b, int c, int d) {
    if (bj[t] == 1) return 0;
    if (bj[t] == -1) clear(t, c, d);
    
    if (a <= c && d <= b) {
        bj[t] = 1;
        l0[t] = r0[t] = k[t] = 0;
        return 0;
    }
    
    int mid = (c + d) >> 1;
    if (a <= mid) insert_help(l[t], a, b, c, mid);
    if (mid + 1 <= b) insert_help(r[t], a, b, mid + 1, d);
    update(t, c, d);
    
    return 0;
}

int insert(int t, int L, int c, int d) {
    if (bj[t] == 1) return 0;
    if (bj[t] == -1) clear(t, c, d);
    
    int mid = (c + d) >> 1;
    if (k[l[t]] >= L) {
        insert(l[t], L, c, mid);
        update(t, c, d);
        return 0;
    }
    if (L == 1 && c == d) {
        l0[t] = r0[t] = k[t] = 0;
        return 0;
    } 
    if (r0[l[t]] + l0[r[t]] >= L) {
        insert_help(t, mid + 1 - r0[l[t]], mid - r0[l[t]] + L, c, d);
        update(t, c, d);
        return 0;
    } else {
        insert(r[t], L, mid + 1, d);
        update(t, c, d);
        return 0;
    }
}

int del(int t, int a, int b, int c, int d) {
    if (bj[t] == -1) return 0;
    if (bj[t] == 1) clear(t, c, d);
    if (a <= c && d <= b) {
        bj[t] = -1;
        l0[t] = r0[t] = k[t] = d - c + 1;
        return 0;
    }
    int mid = (c + d) >> 1;
    if (a <= mid) del(l[t], a, b, c, mid);
    if (mid + 1 <= b) del(r[t], a, b, mid + 1, d);
    
    update(t, c, d);
    
    return 0;
}


int main() {
    freopen("seating.in", "r", stdin);
    freopen("seating.out", "w", stdout);
    int N, K;
    cin >> N >> K;
    build(1, N);
    
    int ans = 0;
    for (int i = 0; i < K; ++i) {
        string p;
        cin >> p;
        if (p == "A") {
            int a;
            cin >> a;
            if (k[1] < a) {
                ++ans;
                continue;
            }
            insert(1, a, 1, N);
        } else {
            int a, b;
            cin >> a >> b;
            del(1, a, b, 1, N);
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
