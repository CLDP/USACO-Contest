#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;


int main() {
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);
    int N;
    long long L;
    cin >> N >> L;
    vector<int> ans(N + 1, 0);
    vector<vector<int> > p(N + 1, vector<int>(19, 0));
    vector<long long> d(N + 1, 0);
    ans[1] = 1;
    for (int i = 2; i <= N; ++i) {
        scanf("%d%lld", &p[i][0], &d[i]);
        d[i] = d[i] + d[p[i][0]];
        for (int j = 1; j <= 18; ++j) p[i][j] = p[p[i][j-1]][j-1];
        int v = i;
        for (int j = 18; j >= 0; --j) 
         if (d[i] - d[p[v][j]] <= L) v = p[v][j];
        ++ans[i];
        --ans[p[v][0]];
    }
    for (int i = N; i >= 1; --i) ans[p[i][0]] = ans[p[i][0]] + ans[i];
    for (int i = 1; i <= N; ++i) printf("%d\n", ans[i]);
    
    return 0;
}
