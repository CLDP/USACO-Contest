#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

int N, M, ans = INF;
int x[15][15], y[16][16], l[16][16];
vector<int> P, Q;


int dfs2(int a, int b, int temp) {
    if (a == 0) {
        Q.push_back(N - 1);
        
        for (int j = 1; j < P.size(); ++j) {
            int a = P[j] + 1, b = N, c = P[j-1] + 1, d = Q[Q.size() - 2] + 1;
            temp = max(temp, y[a][b] - y[a][d] - y[c][b] + y[c][d]);
        }
        if (temp < ans) ans = temp;
        
        Q.erase(Q.end() - 1);
    } else
    for (int i = b; i < N + 1 - a - 1; ++i) {
        Q.push_back(i);
        
        int temp2 = temp;
        for (int j = 1; j < P.size(); ++j) {
            int a = P[j] + 1, b = i + 1, c = P[j-1] + 1, d = Q[Q.size() - 2] + 1;
            temp2 = max(temp2, y[a][b] - y[a][d] - y[c][b] + y[c][d]);
        }
        if (temp2 < ans) dfs2(a - 1, i + 1, temp2);
        Q.erase(Q.end() - 1);
    }
    return 0;
}


int dfs1(int a, int b, int c) {
    if (a == 0) {
        P.push_back(N - 1);
        dfs2(c, 0, 0);
        P.erase(P.end() - 1);
    } else
    for (int i = b; i < N + 1 - a - 1; ++i) {
        P.push_back(i);
        dfs1(a - 1, i + 1, c);
        P.erase(P.end() - 1);
    }
    return 0;
}


int main() {
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> x[i][j];
            l[i+1][j+1] = l[i+1][j] + x[i][j];
            y[i+1][j+1] = y[i][j+1] + l[i+1][j+1];
        }
    }
    
    P.push_back(-1);
    Q.push_back(-1);
    for (int i = max(0, M-N+1); i <= min(M, N-1); ++i) dfs1(i, 0, M - i);
    cout << ans << endl;
    
    return 0;
}

