#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 10010;
const int MAXM = 50010;

vector<int> x[MAXN];
int T[MAXN], D[MAXN], in[MAXN];


int main() {
    freopen("msched.in", "r", stdin);
    freopen("msched.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> T[i];
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        x[a-1].push_back(b-1);
        ++in[b-1];
    }
    queue<int> que;
    for (int i = 0; i < N; ++i)
     if (in[i] == 0) que.push(i);
   
    int ans = 0;
    while (!que.empty()) {
        int a = que.front();
        que.pop();
        D[a] += T[a];
        if (D[a] > ans) ans = D[a];
        
        for (int i = 0; i < x[a].size(); ++i) {
            --in[x[a][i]];
            if (in[x[a][i]] == 0) que.push(x[a][i]);
            D[x[a][i]] = max(D[x[a][i]], D[a]);
        }
    }
    
    cout << ans << endl;
    
    return 0;
}

