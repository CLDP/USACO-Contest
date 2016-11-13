#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1001;

struct node {
    long long x1, y1, x2, y2;
};

int N, C, nn;
node x[MAXN];
int z[MAXN], f[MAXN], d[MAXN];
bool inside[MAXN][MAXN];


long long cross(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3) {
    long long temp = (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
    if (temp > 0) return 1;
    if (temp < 0) return -1;
    return 0;
}

bool cross(long long x1, long long y1, long long x2, long long y2, 
    long long x3, long long y3, long long x4, long long y4) {
    return max(x1, x2) >= min(x3, x4)
        && max(x3, x4) >= min(x1, x2)
        && max(y1, y2) >= min(y3, y4)
        && max(y3, y4) >= min(y1, y2)
        && cross(x1, y1, x4, y4, x3, y3) * cross(x4, y4, x2, y2, x3, y3) >= 0
        && cross(x3, y3, x2, y2, x1, y1) * cross(x2, y2, x4, y4, x1, y1) >= 0;
}


int cal(int t, long long a, long long b) {
    vector<int> y(nn + 1, 0);
    
    for (int i = 0; i < N; ++i) {
        if (cross(a, b, 98127397, 100000007, x[i].x1, x[i].y1, x[i].x2, x[i].y2)) ++y[z[i]];
    }
    
    for (int i = 1; i <= nn; ++i) 
     if (y[i] & 1) inside[t][i] = true;
     
    return 0;
}

int find(int a) {
    if (f[a] != a) f[a] = find(f[a]);
    return f[a];
}


int Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;
    if (d[a] > d[b]) f[b] = f[a]; else f[a] = f[b];
    d[a] += d[b];
    d[b] = d[a];
    return 0;
}


int main() {
    freopen("crazy.in", "r", stdin);
    freopen("crazy.out", "w", stdout);
    cin >> N >> C;
    for (int i = 0; i < N; ++i) {
        cin >> x[i].x1 >> x[i].y1 >> x[i].x2 >> x[i].y2;
    }
    
    nn = 0;
    for (int i = 0; i < N; ++i) {
        if (z[i] == 0) {
            z[i] = ++nn;
            int t = i;
            while (x[t].x2 != x[i].x1 || x[t].y2 != x[i].y1) {
                for (int j = 0; j < N; ++j) {
                    if (z[j]) continue;
                    if (x[j].x1 == x[t].x2 && x[j].y1 == x[t].y2) {
                        z[j] = nn;
                        t = j;
                        break;
                    } else 
                    if (x[j].x2 == x[t].x2 && x[j].y2 == x[t].y2) {
                        swap(x[j].x1, x[j].x2);
                        swap(x[j].y1, x[j].y2);
                        z[j] = nn;
                        t = j;
                        break;
                    }
                }
            }
        }
    }
    
    vector<int> ans(nn + 1, 0);
    for (int i = 1; i <= C; ++i) {
        long long a, b;
        cin >> a >> b;
        cal(i, a, b);
        d[i] = 1;
        f[i] = i;
    }
    
    for (int i = 1; i <= C; ++i) {
        for (int j = i + 1; j <= C; ++j) {
            bool flag = true;
            for (int k = 1; k <= nn; ++k) {
                 if (!(flag &= (inside[i][k] == inside[j][k]))) break;
            }
            if (flag) Union(i, j);
        }
    }
    
    int final = 0;
    for (int i = 1; i <= C; ++i) final = max(final, d[i]);
    cout << final << endl;
    
    return 0;
}
