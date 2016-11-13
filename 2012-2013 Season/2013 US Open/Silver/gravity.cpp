#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 501;
const int INF = 1000000000;
const int MX[4] = {1, 0, -1, 0};
const int MY[4] = {0, -1, 0, 1};

struct state {
    int x, y, dir;
};


int N, M, sx, sy, ex, ey;
int d[MAXN][MAXN][4];
int z[MAXN][MAXN][4];

bool outside(int a, int b) {
    return a < 0 || a >= N || b < 0 || b >= M;
}


int main() {
    freopen("gravity.in", "r", stdin);
    freopen("gravity.out", "w", stdout);
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) 
      for (int k = 0; k < 4; ++k) d[i][j][k] = INF;
    
    vector<string> x(N);
    queue<state> que;
    for (int i = 0; i < N; ++i) {
        cin >> x[i];
        for (int j = 0; j < M; ++j) {
            if (x[i][j] == 'C') {
                state s;
                s.x = sx = i;
                s.y = sy = j;
                s.dir = 0;
                que.push(s);
                z[i][j][0] = true;
                d[i][j][0] = 0;
                x[i][j] = '.';
            }
            if (x[i][j] == 'D') {
                ex = i;
                ey = j;
                x[i][j] = '.';
            }
        }
    }
    
    int ans = INF;
    while (!que.empty()) {
        state s = que.front();
        que.pop();
        if (s.x == ex && s.y == ey) ans = min(ans, d[s.x][s.y][s.dir]);
        if (outside(s.x + MX[s.dir], s.y + MY[s.dir])) continue;
        
        if (x[s.x + MX[s.dir]][s.y + MY[s.dir]] == '.') {
            state ss = s;
            while (!outside(s.x + MX[s.dir], s.y + MY[s.dir]) && 
                    x[s.x + MX[s.dir]][s.y + MY[s.dir]] == '.') {
                s.x += MX[s.dir];
                s.y += MY[s.dir];
                if (s.x == ex && s.y == ey) ans = min(ans, d[ss.x][ss.y][ss.dir]);
            }
            if (outside(s.x + MX[s.dir], s.y + MY[s.dir])) continue;
            if (d[s.x][s.y][s.dir] > d[ss.x][ss.y][ss.dir]) {
                d[s.x][s.y][s.dir] = d[ss.x][ss.y][ss.dir];
                if (!z[s.x][s.y][s.dir]) que.push(s);
                z[s.x][s.y][s.dir] = true;
            }
            z[ss.x][ss.y][ss.dir] = false;
            continue;
        }
        
        for (int i = 0; i < 4; i += 2) {
            if (i == s.dir) continue;
            if (d[s.x][s.y][i] > d[s.x][s.y][s.dir] + 1) {
                d[s.x][s.y][i] = d[s.x][s.y][s.dir] + 1;
                if (!z[s.x][s.y][i]) {
                    z[s.x][s.y][i] = true;
                    state ss = s;
                    ss.dir = i;
                    que.push(ss);
                }
            }
        }
        
        for (int i = 1; i < 4; i += 2) {
            state ss = s;
            ss.x += MX[(s.dir + i) % 4];
            ss.y += MY[(s.dir + i) % 4];
            if (outside(ss.x, ss.y)) continue;
            if (x[ss.x][ss.y] != '.') continue;
            if (d[ss.x][ss.y][ss.dir] > d[s.x][s.y][s.dir]) {
                d[ss.x][ss.y][ss.dir] = d[s.x][s.y][s.dir];
                if (!z[ss.x][ss.y][ss.dir]) que.push(ss);
                z[ss.x][ss.y][ss.dir] = true;
            }
        }
        z[s.x][s.y][s.dir] = false;
    }
    
    if (ans == INF) ans = -1;
    cout << ans << endl;
    
    return 0;    
}
