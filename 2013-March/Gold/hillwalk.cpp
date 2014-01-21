#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

struct edge {
    int x1, y1, x2, y2, index;
    
    bool operator < (edge const &p) const {
        if (x2 < p.x2) {
            return 1LL * (y2 - p.y1) * (p.x2 - p.x1) < 1LL * (p.y2 - p.y1) * (x2 - p.x1);
        } else {
            return 1LL * (p.y2 - y1) * (x2 - x1) > 1LL * (y2 - y1) * (p.x2 - x1);
        }
    }
} edges[MAXN];

struct event {
    int index, x, y;
    
    bool operator < (event const &p) const {
        if (x == p.x) return y < p.y; else return x < p.x;
    }
} events[MAXN * 2];


int main() {
    freopen("hillwalk.in", "r", stdin);
    freopen("hillwalk.out", "w", stdout);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        edges[i].index = i;
        cin >> edges[i].x1 >> edges[i].y1 >> edges[i].x2 >> edges[i].y2;
        events[2 * i].index = i;
        events[2 * i].x = edges[i].x1;
        events[2 * i].y = edges[i].y1;
        events[2 * i + 1].index = i;
        events[2 * i + 1].x = edges[i].x2;
        events[2 * i + 1].y = edges[i].y2;
    }
    sort(events, events + 2 * N);
    
    set<edge> s;
    s.insert(edges[0]);
    int current = 0, ans = 1;
    for (int i = 1; i < 2 * N; ++i) {
        event ev = events[i];
        edge ed = edges[ev.index];
        if (ev.x == ed.x1) {
            s.insert(ed);
        } else {
            if (ev.index == current) {
                set<edge>::iterator iter = s.find(ed);
                if (iter == s.begin()) break;
                set<edge>::iterator iter2 = iter;
                --iter2;
                current = iter2->index;
                s.erase(iter);
                ++ans;
            } else {
                s.erase(ed);
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
