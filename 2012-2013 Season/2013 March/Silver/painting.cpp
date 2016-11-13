#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct node {
    int x1, y1, x2, y2;
    
    bool operator < (node const &b) const {
         return x1 < b.x1;
    }
};

struct event {
    int y, i;
    bool begin;
    
    bool operator < (event const &b) const {
        return y < b.y;
    }
};

int main() {
    freopen("painting.in", "r", stdin);
    freopen("painting.out", "w", stdout);
    int N;
    cin >> N;
    vector<node> x(N);
    vector<event> E;
    for (int i = 0; i < N; ++i) {
        cin >> x[i].x1 >> x[i].y1 >> x[i].x2 >> x[i].y2;
        event p;
        p.y = x[i].y1;
        p.i = i;
        p.begin = true;
        E.push_back(p);
        p.y = x[i].y2;
        p.i = i;
        p.begin = false;
        E.push_back(p);
    }
    
    sort(E.begin(), E.end());
    
    int ans = 0;
    set<node> z;
    for (int i = 0; i < E.size(); ++i) {
        if (E[i].begin) {
            z.insert(x[E[i].i]);
            set<node>::iterator iter = z.find(x[E[i].i]);
            if (iter != z.begin()) {
                --iter;
                if (iter->x1 <= x[E[i].i].x1 && x[E[i].i].x2 <= iter->x2) {
                    z.erase(x[E[i].i]);
                    continue;
                }
            }
            ++ans;
        } else {
            if (z.find(x[E[i].i]) != z.end()) z.erase(x[E[i].i]);
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
