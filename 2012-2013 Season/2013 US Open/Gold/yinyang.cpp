#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
typedef set<pair<int, int> >::iterator iter;

int tree_size[MAXN];
set<pair<int, int> > E[MAXN];

int bx, cx;
pair<int, int> B[MAXN * 2 + 1];
pair<int, int> C[MAXN * 2 + 1];


int subtree(int a, int p) {
    int ans = 1;
    for (iter i = E[a].begin(); i != E[a].end(); ++i)
     if (i->first != p) ans += subtree(i->first, a);
    return tree_size[a] = ans;
}

int count(int a, int p, int w, int minW, int maxW) {
    if (w == minW || w == maxW) {
        if (w == minW) minW = w - 1;
        if (w == maxW) maxW = w + 1;
        ++C[cx + w].second;
    } else {
        ++C[cx + w].first;
    }
    for (iter i = E[a].begin(); i != E[a].end(); ++i)
     if (i->first != p) count(i->first, a, w + i->second, minW, maxW);
    
    return 0;
}


long long solve(int a) {
    int N = subtree(a, -1), p = -1;
    while (true) {
        bool flag = true;
        for (iter i = E[a].begin(); i != E[a].end(); ++i) {
            int b = i->first;
            if (b != p && tree_size[b] >= N / 2) {
                flag = false;
                p = a;
                a = b;
                break;
            }
        }
        if (flag) break;
    }
    
    long long ans = 0;
    bx = N;
    fill(B, B + 2 * bx + 1, make_pair(0, 0));
    B[bx].second = 1;
    
    for (iter i = E[a].begin(); i != E[a].end(); ++i) {
        int b = i->first;
        cx = tree_size[b];
        fill(C, C + 2 * cx + 1, make_pair(0, 0));
        count(b, a, i->second, i->second, i->second);
        
        for (int w = -cx; w <= cx; ++w) {
            ans += 1LL * C[cx + w].first * (B[bx - w].first + B[bx - w].second);
            ans += 1LL * C[cx + w].second * B[bx - w].first;
        }
        
        ans += 1LL * C[cx].second * (B[bx].second - 1);
        
        for (int w = -cx; w <= cx; ++w) {
            B[bx + w].first += C[cx + w].first;
            B[bx + w].second += C[cx + w].second;
        }
    }
    
    for (iter i = E[a].begin(); i != E[a].end(); ++i) {
        int b = i->first;
        E[b].erase(make_pair(a, i->second));
        ans += solve(b);
    }
    
    return ans;
}


int main() {
    freopen("yinyang.in", "r", stdin);
    freopen("yinyang.out", "w", stdout);
    int N;
    cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        c = c * 2 - 1;
        E[a].insert(make_pair(b, c));
        E[b].insert(make_pair(a, c));
    }
    
    cout << solve(0) << endl;
    return 0;
}

