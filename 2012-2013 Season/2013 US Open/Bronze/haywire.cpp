#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

int N;
int x[12][3];
int f[1 << 12];

int main() {
    freopen("haywire.in", "r", stdin);
    freopen("haywire.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; ++i) 
     for (int j = 0; j < 3; ++j) {
         cin >> x[i][j];
         --x[i][j];
     }
    
    for (int i = 1; i < (1 << N); ++i) f[i] = INF;
    for (int i = 0; i < N; ++i) f[1 << i] = 0;
    for (int i = 1; i < N; ++i) {
        vector<int> s(N - i, 0);
        for (int j = 0; j < i; ++j) s.push_back(1);
        
        bool flag = false;
        while (s[0] != 1 || flag) {
            int ss = 0, sum = 0;
            for (int j = 0; j < N; ++j) {
                if (s[j] == 0) continue;
                ss += (1 << j);
                for (int k = 0; k < 3; ++k) sum += (s[x[j][k]] + 1) % 2;
            }
            
            for (int j = 0; j < N; ++j) {
                if (s[j]) continue;
                f[ss + (1 << j)] = min(f[ss + (1 << j)], f[ss] + sum);
            }
            
            next_permutation(s.begin(), s.end());
            if (s[0] == 1) flag = true;
            if (flag && s[0] == 0) break;
        }
    }
    
    cout << f[(1 << N) - 1] << endl;
    
    return 0;    
}
