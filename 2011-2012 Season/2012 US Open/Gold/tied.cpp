#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct point {
    int x, y;
};

int N, M, a, b;
point x[10], y[10001];


bool check(int ss) {
    vector<pair<int, int> > X;
    for (int i = 0; i < N; ++i)
     if (ss & (1 << i)) X.push_back(make_pair(x[i].x, x[i].y));
    sort(X.begin(), X.end());
    
    stack<pair<int, int> > s;
    for (int i = 0; i < M - 1; ++i) {
        if (min(y[i].x, y[i+1].x) > X[0].first || X[0].first > max(y[i].x, y[i+1].x)) continue;
        if (y[i].x == y[i+1].x) continue;
        
        double mid = 1.0 * (X[0].first - y[i+1].x) * (y[i].y - y[i+1].y) / (y[i].x - y[i+1].x) + y[i+1].y;
        int j = 0;
        while (j < X.size() && X[j].second < mid) ++j;
        
        if (y[i].x < y[i+1].x) {
            if (s.empty() || s.top().first != j) {
                s.push(make_pair(j, 1));
                continue;
            }
            if (s.top().second == -1) s.pop();
        } else {
            if (s.empty() || s.top().first != j) {
                s.push(make_pair(j, -1));
                continue;
            }
            if (s.top().second == 1) s.pop();
        }
    }
    
    return s.empty();
}


int main() {
    freopen("tied.in", "r", stdin);
    freopen("tied.out", "w", stdout);
    cin >> N >> M >> a >> b;
    ++M;
    for (int i = 0; i < N; ++i) cin >> x[i].x >> x[i].y;
    for (int j = 0; j < M; ++j) cin >> y[j].x >> y[j].y;
    
    if (check((1 << N) - 1)) {
        cout << 0 << endl;
        return 0;
    }
    
    for (int i = 1; i < N; ++i) {
        vector<int> s(i, 0);
        for (int j = 0; j < N - i; ++j) s.push_back(1);
        
        bool flag = false;
        while (s[0] == 0 || flag) {
            int ss = 0;
            for (int j = 0; j < N; ++j) ss += (1 << j) * s[j];
            if (check(ss)) {
                cout << i << endl;
                return 0;
            }
            
            next_permutation(s.begin(), s.end());
            if (s[0] == 1) flag = true;
            if (s[0] == 0 && flag) break;
        }
    }
    cout << N << endl;
    
    return 0;
}

