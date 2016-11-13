#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M;
int s[250010];
vector<int> x[250010];
vector<int> y[1000010];
bool z[1000010];

int main() {
    freopen("invite.in", "r", stdin);
    freopen("invite.out", "w", stdout);
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int a;
        cin >> a;
        for (int j = 0; j < a; ++j) {
            int b;
            cin >> b;
            x[i].push_back(b);
            y[b].push_back(i);
        }
        s[i] = a;
    }
    
    int ans = 1;
    z[1] = true;
    queue<int> que;
    que.push(1);
    while (!que.empty()) {
        int a = que.front();
        que.pop();
        for (int i = 0; i < y[a].size(); ++i) {
            --s[y[a][i]];
            if (s[y[a][i]] == 1) {
                int b = y[a][i];
                for (int j = 0; j < x[b].size(); ++j)
                 if (!z[x[b][j]]) {
                     z[x[b][j]] = true;
                     que.push(x[b][j]);
                     ++ans;
                 }
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
