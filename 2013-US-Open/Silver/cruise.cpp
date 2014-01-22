#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1001;

int L[MAXN], R[MAXN], E[MAXN];
string p[MAXN];

int main() {
    freopen("cruise.in", "r", stdin);
    freopen("cruise.out", "w", stdout);
    int N, M, K;
    cin >> N >> M >> K; 
    for (int i = 1; i <= N; ++i) cin >> L[i] >> R[i];
    for (int i = 0; i < M; ++i) cin >> p[i];
    
    for (int i = 1; i <= N; ++i) {
        int pos = i;
        for (int j = 0; j < M; ++j) {
            pos = p[j] == "L" ? L[pos] : R[pos];
        }
        E[i] = pos;
    }
    
    int circle = 0, pos = 1;
    while (K > 0) {
        --K;
        pos = E[pos];
        ++circle;
        if (pos == 1) K %= circle;
    }
    
    cout << pos << endl;
    
    return 0;    
}
