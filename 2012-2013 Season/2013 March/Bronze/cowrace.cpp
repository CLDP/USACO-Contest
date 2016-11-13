#include <iostream>
#include <cstdio>
using namespace std;

struct node {
     int s, t;     
};

const int MAXN = 1010;

node x[MAXN], y[MAXN];

int main() {
    freopen("cowrace.in", "r", stdin);
    freopen("cowrace.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> x[i].s >> x[i].t;
    for (int i = 0; i < m; ++i) cin >> y[i].s >> y[i].t;
    bool flag, begin = true;
    int i = 0, j = 0, d1 = 0, d2 = 0, ans = 0;
    while (i < n && j < m) {
        if (x[i].t == 0) {
            ++i;
            if (i == n) break;
        }
        if (y[j].t == 0) {
            ++j;
            if (j == m) break;
        }
        --x[i].t;
        d1 += x[i].s;   
        --y[j].t;
        d2 += y[j].s;
        if (d2 > d1) {
            if (begin) {
                begin = false;    
                flag = false;       
            } else {
                if (flag) {
                    ++ans;
                    flag = false;
                }
            }
        }
        
        if (d1 > d2) {
            if (begin) {
                begin = false;    
                flag = true;       
            } else {
                if (!flag) {
                    ++ans;
                    flag = true;
                }
            }  
        }
    }
    
    cout << ans << endl;
    
    return 0;    
}

