#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 100010;

int n, m;
int x[MAXN], z[2 * MAXN];


int query(int a) {
    int ans = 0;
    for (int i = (a + MAXN); i > 0; i -= (i & -i)) ans += z[i];
    return ans;
}

void insert(int a) {
    for (int i = (a + MAXN); i < 2 * MAXN; i += (i & -i)) ++z[i];
}


int main() {
    freopen("median.in", "r", stdin);
    freopen("median.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x[i]);
        x[i] = (x[i] >= m) ? 1 : -1;
        if (i > 0) x[i] += x[i-1];
    }
    insert(0);
    
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += query(x[i]);
        insert(x[i]);
    }
    
    cout << ans << endl;
    
    return 0;
}
