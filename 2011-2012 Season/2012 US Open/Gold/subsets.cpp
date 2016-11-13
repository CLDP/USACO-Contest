#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 2000000000;


int N, sum, ans, temp;
int x[20], L;
bool f[1 << 20];

int dfs(int a, int b, int c) {
    if (a == 0 && temp == 0) {
        f[b] = true;
        return 0;
    }
    
    sum -= x[--a];
    
    temp += x[a]; ++L;
    if (abs(temp) <= sum && x[a] < c) dfs(a, b + (1 << a), c);
    temp -= x[a]; --L;
    if (abs(temp) <= sum) dfs(a, b, c);
    temp -= x[a];
    if (abs(temp) <= sum && L > 0) dfs(a, b + (1 << a), x[a]);
    temp += x[a];
    
    sum += x[a];
    
    return 0;
}



int main() {
    freopen("subsets.in", "r", stdin);
    freopen("subsets.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> x[i];
        sum += x[i];
    }
    sort(x, x + N);
    dfs(N, 0, INF);
    
    for (int i = 3; i < (1 << N); ++i) ans += f[i];
    cout << ans << endl;
    
    return 0;
}
