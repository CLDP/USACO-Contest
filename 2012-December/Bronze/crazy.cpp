#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 3001;

struct fence {
    int x1, y1, x2, y2;
};

int x[MAXN][MAXN];
fence y[MAXN];
pair<int, int> z[MAXN];

int bfs(int a, int b, int n, int m, int s) {
    queue<pair<int, int> > que;
    que.push(make_pair(a, b));
    while (!que.empty()) {
        a = que.front().first;
        b = que.front().second;
        que.pop();
        if (a > 0 && x[a-1][b] == 0) {
            x[a-1][b] = s;
            que.push(make_pair(a-1, b));
        }
        if (a < n-1 && x[a+1][b] == 0) {
            x[a+1][b] = s;
            que.push(make_pair(a+1, b));
        }
        if (b > 0 && x[a][b-1] == 0) {
            x[a][b-1] = s;
            que.push(make_pair(a, b-1));
        } 
        if (b < m-1 && x[a][b+1] == 0) {
            x[a][b+1] = s;
            que.push(make_pair(a, b+1));
        } 
    }
    return 0;
}


int main() {
    freopen("crazy.in", "r", stdin);
    freopen("crazy.out", "w", stdout);
    int N, C;
    cin >> N >> C;
    set<int> X, Y;
    for (int i = 0; i < N; ++i) {
        cin >> y[i].x1 >> y[i].y1 >> y[i].x2 >> y[i].y2;
        X.insert(y[i].x1);
        X.insert(y[i].x2);
        Y.insert(y[i].y1);
        Y.insert(y[i].y2);
    }
    for (int i = 0; i < C; ++i) {
        cin >> z[i].first >> z[i].second;
        X.insert(z[i].first);
        Y.insert(z[i].second);
    }
    
    int mX = 0, mY = 0;
    map<int, int> changeX, changeY;
    
    int s = 0;
    for (set<int>::iterator iter = X.begin(); iter != X.end(); ++iter) {
        changeX[*iter] = (s++) * 3 + 1;
        mX = s * 3;
    }
    s = 0;
    for (set<int>::iterator iter = Y.begin(); iter != Y.end(); ++iter) {
        changeY[*iter] = (s++) * 3 + 1;
        mY = s * 3;
    }
    
    for (int i = 0; i < N; ++i) {
        if (y[i].x1 == y[i].x2) {
            int p = changeX[y[i].x1], q1 = changeY[y[i].y1], q2 = changeY[y[i].y2];
            if (q1 > q2) swap(q1, q2);
            for (int j = q1; j <= q2; ++j) x[p][j] = -1;
        } else {
            int p1 = changeX[y[i].x1], p2 = changeX[y[i].x2], q = changeY[y[i].y1];
            if (p1 > p2) swap(p1, p2);
            for (int j = p1; j <= p2; ++j) x[j][q] = -1;
        }
    }
    
    s = 1;
    for (int i = 0; i < mX; ++i)
     for (int j = 0; j < mY; ++j) {
         if (x[i][j] == 0) {
             bfs(i, j, mX, mY, s);
             ++s;
         }
     }
    
    vector<int> ans(s, 0);
    for (int i = 0; i < C; ++i) {
        int p = changeX[z[i].first], q = changeY[z[i].second];
        ++ans[x[p][q]];
    }
    
    int ansT = 0;
    for (int i = 1; i < s; ++i) ansT = max(ansT, ans[i]);
    cout << ansT << endl;
    
    return 0;
}
