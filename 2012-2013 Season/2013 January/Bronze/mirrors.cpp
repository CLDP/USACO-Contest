#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

struct node {
    int a, b;
    bool dir;
};

int z[201];

int main() {
    freopen("mirrors.in", "r", stdin);
    freopen("mirrors.out", "w", stdout);  
    int N, A, B;
    cin >> N >> A >> B;
    vector<node> x;
    for (int i = 0; i < N; ++i) {
        node p;
        string q;
        cin >> p.a >> p.b >> q;
        if (q == "/") p.dir = false; else p.dir = true;
        x.push_back(p);
    }
    for (int i = -1; i < N; ++i) {
        if (i != -1) x[i].dir = !x[i].dir;
        int a = 0, b = 0, dir = 1;
        memset(z, 0, sizeof(z));
        while (true) {
            int T = 0;
            if (dir == 0) {
                int c = INF;
                for (int j = 0; j < N; ++j)
                 if (z[j] < 2 && x[j].a == a && x[j].b > b && x[j].b < c) {
                     c = x[j].b;
                     T = j;
                     if (x[j].dir) dir = 3; else dir = 1;
                 } 
                if (a == A && b <= B && B <= c) {
                    cout << i + 1 << endl;
                    return 0;
                }
                if (b == c) break;
                b = c;
            } else
            if (dir == 1) {
                int c = INF;
                for (int j = 0; j < N; ++j)
                 if (z[j] < 2 && x[j].b == b && x[j].a > a && x[j].a < c) {
                     c = x[j].a;
                     T = j;
                     if (x[j].dir) dir = 2; else dir = 0;
                 } 
                if (b == B && a <= A && A <= c) {
                    cout << i + 1 << endl;
                    return 0;
                }
                if (a == c) break;
                a = c;
            } else 
            if (dir == 2) {
                int c = -INF;
                for (int j = 0; j < N; ++j)
                 if (z[j] < 2 && x[j].a == a && x[j].b < b && x[j].b > c) {
                     c = x[j].b;
                     T = j;
                     if (x[j].dir) dir = 1; else dir = 3;
                 } 
                if (a == A && c <= B && B <= b) {
                    cout << i + 1 << endl;
                    return 0;
                }
                if (b == c) break;
                b = c;
            } else {
                int c = -INF;
                for (int j = 0; j < N; ++j)
                 if (z[j] < 2 && x[j].b == b && x[j].a < a && x[j].a > c) {
                     c = x[j].a;
                     T = j;
                     if (x[j].dir) dir = 0; else dir = 2;
                 } 
                if (b == B && c <= A && A <= a) {
                    cout << i + 1 << endl;
                    return 0;
                }
                if (a == c) break;
                a = c;
            }
            ++z[T];
        }
        if (i != -1) x[i].dir = !x[i].dir;
    }
    
    cout << -1 << endl;
    
    return 0;
}
