#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;


int n;
long long M, K;
long long x[15][8];


long long cal(int t, long long dist, int a, int b) {
    return (dist + dist * x[t][a * 4 + b * 2] + x[t][a * 4 + b * 2 + 1]) % M;
}


bool dfsA(int a, long long dist);


bool dfsB(int a, long long dist, bool dis) {
    bool mv = rand() % 2;
    return dfsA(a + 1, cal(a, dist, dis, !mv)) && dfsA(a + 1, cal(a, dist, dis, mv));
}


bool dfsA(int a, long long dist) {
    if (a == n) return dist <= K || M - dist <= K;
    bool mv = rand() % 2;
    return dfsB(a, dist, mv) || dfsB(a, dist, !mv);
}


int main() {
    freopen("cowrun.in", "r", stdin);
    freopen("cowrun.out", "w", stdout);
    string p;
    cin >> n >> M >> K >> p;
    for (int i = 0; i < n; ++i) 
     for (int j = 0; j < 8; ++j) cin >> x[i][j];
     
    long long dist = 0;
    for (int i = 0; i < n; ++i) {
        if (dfsB(i, dist, true)) {
            cout << "B";
            dist = cal(i, dist, true, p[i] == 'B');
        } else {
            cout << "T";
            dist = cal(i, dist, false, p[i] == 'B');
        }
    }
    
    cout << endl;
    
    return 0;
}
