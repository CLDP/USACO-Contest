#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;


const int MAXN = 50010;
const int INF = 1000000000;

struct point {
    long long x, y;
};

struct segment {
    point a, b;
};


int n;
point x[MAXN], y[MAXN];
vector<int> upper, lower;


int check_zero(long long a) {
    if (a == 0) return 0;
    if (a > 0) return 1; else return -1;
}

long long cross_product(long long x1, long long y1, long long x2, long long y2) {
    return x1 * y2 - x2 * y1;
}

long long cross(int a, int b, int c) {
    return cross_product(x[b].x - x[a].x, x[b].y - x[a].y, x[c].x - x[b].x, x[c].y - x[b].y);
}

int check(int a, int b, int c) {
    return check_zero(cross(a, b, c));
}

bool compare(const point &a, const point &b) {
    if (a.y < b.y) return true;
    if (a.y == b.y) return a.x < b.x;
    return false;
}

int granhamscan(vector<pair<int, int> > &T) {
    sort(x+1, x+n+1, compare);
    
    x[0].y = -INF;
    x[n+1].y = INF;
    
    lower.clear();
    upper.clear();
    for (int i = 1; i <= n; ++i) {
        if (x[i].y != x[i-1].y) lower.push_back(i);
        if (x[i].y != x[i+1].y) upper.push_back(i);
    }
    
    vector<int> ans_lower;
    ans_lower.push_back(lower[0]);
    ans_lower.push_back(lower[1]);
    int i = 2;
    while (i < lower.size()) {
        if (check(ans_lower[ans_lower.size() - 2], ans_lower[ans_lower.size() - 1], 
            lower[i]) == 1 && ans_lower.size() > 1) {
            ans_lower.erase(ans_lower.end() - 1, ans_lower.end());
        } else {
            ans_lower.push_back(lower[i]);
            ++i;
        }
    }
    
    vector<int> ans_upper;
    ans_upper.push_back(upper[0]);
    ans_upper.push_back(upper[1]);
    i = 2;
    while (i < upper.size()) {
        if (check(ans_upper[ans_upper.size() - 2], ans_upper[ans_upper.size() - 1], 
            upper[i]) == -1 && ans_upper.size() > 1) {
            ans_upper.erase(ans_upper.end() - 1, ans_upper.end());
        } else {
            ans_upper.push_back(upper[i]);
            ++i;
        }
    }
    
    for (int i = 0; i < ans_lower.size() - 1; ++i) T.push_back(make_pair(ans_lower[i], ans_lower[i+1]));
    
    for (int i = 0; i < ans_upper.size() - 1; ++i) T.push_back(make_pair(ans_upper[i], ans_upper[i+1]));
                 
    if (ans_upper[0] != ans_lower[0]) 
        T.push_back(make_pair(ans_upper[0], ans_lower[0]));
    if (ans_upper[ans_upper.size()-1] != ans_lower[ans_lower.size()-1])
        T.push_back(make_pair(ans_upper[ans_upper.size()-1], ans_lower[ans_lower.size()-1]));
    
    return 0;
}

long long cross(point a, point b, point c) {
    return check_zero((a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y));
}

bool check_intersect(segment s1, segment s2) {
    return max(s1.a.x, s1.b.x) >= min(s2.a.x, s2.b.x)
        && max(s2.a.x, s2.b.x) >= min(s1.a.x, s1.b.x)
        && max(s1.a.y, s1.b.y) >= min(s2.a.y, s2.b.y)
        && max(s2.a.y, s2.b.y) >= min(s1.a.y, s1.b.y)
        && cross(s1.a, s2.b, s2.a) * cross(s2.b, s1.b, s2.a) >= 0
        && cross(s2.a, s1.b, s1.a) * cross(s1.b, s2.b, s1.a) >= 0;
}

bool boundary(point now, segment s) {
    long long x1 = s.a.x, x2 = s.b.x, y1 = s.a.y, y2 = s.b.y;
    long long x = now.x, y = now.y;
    return ((y1 - y) * (x2 - x) - (y2 - y) * (x1 - x) == 0) &&
           (((y1 - y) * (y2 - y) <= 0 && (x1 - x) * (x2 - x) <= 0));
}


bool check_inside(point now, vector<pair<int, int> > &T) {
    int ans = 0;
    segment tmp;
    tmp.a = now;
    tmp.b.x = 5234137;
    tmp.b.y = 6345237;
    for (int i = 0; i < T.size(); ++i) {
        segment P;
        P.a = x[T[i].first];
        P.b = x[T[i].second];
        if (boundary(now, P)) return true;
        if (check_intersect(tmp, P)) ++ans;
    }
    return ans & 1;
}


int main() {
    freopen("curling.in", "r", stdin);
    freopen("curling.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> x[i].x >> x[i].y;
    for (int i = 1; i <= n; ++i) cin >> y[i].x >> y[i].y;
    
    vector<pair<int, int> > T;
    granhamscan(T);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (check_inside(y[i], T)) ++ans;
    }
    cout << ans << " ";
    
    for (int i = 1; i <= n; ++i) {
        swap(x[i].x, y[i].x);
        swap(x[i].y, y[i].y);
    }
    T.clear();
    granhamscan(T);
    ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (check_inside(y[i], T)) ++ans;
    }
    cout << ans << endl;
    
    return 0;
}
