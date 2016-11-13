#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 310;
const int MAXM = 100000;
const int INF = 2000000000;

class node {
public:
       int v, w, c, f;
       node *next, *couple;
       node() { v = 0; w = 0; c = 0; f = 0; next = 0;}
};
  
int n, ans1, ans2;
int d[MAXN], que[MAXM], fa[MAXN];
node *x[MAXN], *ff[MAXN];
bool z[MAXN];
  
int newnode(int a, int b, int c, int d) {
    node *p = new node;
    node *q = new node;
    p->v = b;
    p->c = c;
    p->w = d;
    p->f = 0;
    p->couple = q;
    p->next = x[a];
    x[a] = p;
    q->v = a;
    q->w = -d;
    q->c = 0;
    q->f = 0;
    q->couple = p;
    q->next = x[b];
    x[b] = q;
    return 0;
}
  
int SPFA(int s, int t) {
    for (int i = 1; i <= n; ++i) {
        z[i] = 0;
        d[i] = INF;
    }
    d[s] = 0;
    que[1] = s;
    z[s] = 1;
    int l = 1, r = 1, i = 0;
    node *p;
    while (l <= r) {
        i = que[l++];
        p = x[i];
        while (p) {
            if (p->c > p->f && d[p->v] > d[i] + p->w) {
                d[p->v] = d[i] + p->w;
                fa[p->v] = i;
                ff[p->v] = p;
                if (!z[p->v]) {
                    z[p->v] = true;
                    que[++r] = p->v;
                }
            }
            p = p-> next;
        }
        z[i] = false;
    }
    return d[t];
}
  
int Min_Cost(int s, int t) {
    int now = 0, i = 0;
    node *p;
    while (SPFA(s,t) < INF) {
        i = t;
        now = INF;
        while (i != s) {
            p = ff[i];
            i = fa[i];
            if (p->c - p->f < now) now = p->c - p->f;
        }
        ans1 += now;
          
        i = t;
        while (i != s) {
            p = ff[i];
            i = fa[i];
            p->f += now;
            ans2 += now * p->w;
            p = p->couple;
            p->f -= now;
        }
    }
    return 0;
} 
int main() {
    freopen("recording.in", "r", stdin);
    freopen("recording.out", "w", stdout);
    
    int N, s, t;
    cin >> N;
    vector<int> p(N, 0), q(N, 0);
    for (int i = 0; i < N; ++i) {
        cin >> p[i] >> q[i];
        newnode(2, 2 * i + 3, 1, 0);
        newnode(2 * i + 3, 2 * i + 4, 1, -1);
        newnode(2 * i + 4, 2 * N + 3, 1, 0);
    }
    for (int i = 0; i < N; ++i) 
     for (int j = i + 1; j < N; ++j) {
         if (q[i] <= p[j]) newnode(2 * i + 4, 2 * j + 3, 1, 0);
         if (q[j] <= p[i]) newnode(2 * j + 4, 2 * i + 3, 1, 0);
     }
    
    newnode(1, 2, 2, 0);
    s = 1;
    t = 2 * N + 3;
    n = t;
    
    Min_Cost(s, t);
    
    cout << -ans2 << endl;
    
    return 0;
}
