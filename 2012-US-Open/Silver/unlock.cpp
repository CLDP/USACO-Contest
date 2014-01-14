#include <iostream>
#include <cstdio>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

const int BASE = 10;
const int MAXN = 21;
const int MOVE[4][12] = {-1, 1, 0, 0, 0, 0, 0, 0, -1, 1, 0, 0,
                         0, 0, -1, 1, 0, 0, 0, 0, 0, 0, -1, 1,
                         0, 0, 0, 0, -1, 1, 0, 0, -1, 1, 0, 0,
                         0, 0, 0, 0, 0, 0, -1, 1, 0, 0, -1, 1};

struct state {
    int t[4], d;
};


int N[3];
vector<pair<int, int> > x[3];
int sx[3], sy[3], w[3], h[3];
bool all[MAXN][MAXN][MAXN][MAXN];

bool outside(int a) {
    return a < -10 || a > 10;
}


bool check(state &p) {
    if (outside(sx[1]) || outside(sy[1]) || outside(sx[2]) || outside(sy[2])) return false;
    set<pair<int, int> > hash;
    for (int i = 1; i < 3; ++i) {
        for (int j = 0; j < N[i]; ++j) {
            if (hash.find(make_pair(x[i][j].first + sx[i], x[i][j].second + sy[i])) != hash.end()) return false;
            hash.insert(make_pair(x[i][j].first + sx[i], x[i][j].second + sy[i]));
        }
    }
    for (int j = 0; j < N[0]; ++j) {
        if (hash.find(x[0][j]) != hash.end()) return false;
        hash.insert(x[0][j]);
    }
    return true;
}


bool intersect(int a, int b) {
    return sx[a] + w[a] < sx[b] || sx[b] + w[b] < sx[a] || sy[a] + h[a] < sy[b] || sy[b] + h[b] < sy[a];
}


int main() {
    freopen("unlock.in", "r", stdin);
    freopen("unlock.out", "w", stdout);
    cin >> N[0] >> N[1] >> N[2];
    for (int i = 0; i < 3; ++i) {
        sx[i] = sy[i] = 10;
        w[i] = h[i] = 0;
        for (int j = 0; j < N[i]; ++j) {
            int a, b;
            cin >> a >> b;
            x[i].push_back(make_pair(a, b));
            sx[i] = min(sx[i], a);
            sy[i] = min(sy[i], b);
            w[i] = max(w[i], a);
            h[i] = max(h[i], b);
        }
        w[i] -= sx[i];
        h[i] -= sy[i];
    }
    for (int i = 1; i < 3; ++i) {
        for (int j = 0; j < N[i]; ++j) {
            x[i][j].first -= sx[i];
            x[i][j].second -= sy[i];
        }
    }
    
    queue<state> que;
    state p;
    p.t[0] = sx[1];  p.t[1] = sy[1];
    p.t[2] = sx[2];  p.t[3] = sy[2];
    p.d = 0;
    que.push(p);
    all[sx[1] + BASE][sy[1] + BASE][sx[2] + BASE][sy[2] + BASE] = true;
    
    while (!que.empty()) {
        p = que.front();
        que.pop();
        ++p.d;
        for (int i = 0; i < 12; ++i) {
            state q = p;
            q.d = 0;
            for (int j = 0; j < 4; ++j) q.t[j] += MOVE[j][i];  
            sx[1] = q.t[0];  sy[1] = q.t[1];
            sx[2] = q.t[2];  sy[2] = q.t[3];
            if (!check(q)) continue;
            if (all[sx[1] + BASE][sy[1] + BASE][sx[2] + BASE][sy[2] + BASE]) continue;
            
            all[sx[1] + BASE][sy[1] + BASE][sx[2] + BASE][sy[2] + BASE] = true;
            if (intersect(0, 1) && intersect(0, 2) && intersect(1, 2)) {
                cout << p.d << endl;
                return 0;
            }
            q.d = p.d;
            que.push(q);
        }
        
    }
    
    cout << -1 << endl;
    
    return 0;
}
