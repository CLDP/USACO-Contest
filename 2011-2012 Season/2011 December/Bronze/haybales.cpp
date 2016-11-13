#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10010;

int n;
int x[MAXN];


int main() {
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);
    cin >> n;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        sum += x[i];
    }
    
    sum /= n;
    int ans = 0;
    for (int i = 0; i < n; ++i)
     if (x[i] > sum) ans += x[i] - sum;
    
    cout << ans << endl;
    
    return 0;
}
