#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MX[4] = {-1, 1, 0, 0};
const int MY[4] = {0, 0, -1, 1};

int N;
vector<string> x;
bool z[5][5];


bool dfs(int a, int b, int c, int d) {
    if (a == 0) {
        if (b == 0) return true;
        for (int i = 0; i < 4; ++i) {
            int p = c + MX[i], q = d + MY[i];
            if (p >= 0 && p < N && q >= 0 && q < N && x[p][q] == ')' && !z[p][q]) {
                z[p][q] = true;
                if (dfs(a, b-1, p, q)) return true;
                z[p][q] = false;
            }
        }
        return false;
    }
    for (int i = 0; i < 4; ++i) {
        int p = c + MX[i], q = d + MY[i];
        if (p >= 0 && p < N && q >= 0 && q < N && x[p][q] == '(' && !z[p][q]) {
            z[p][q] = true;
            if (dfs(a-1, b, p, q)) return true;
            z[p][q] = false;
        }
    }
    return false;
}


int main() {
    freopen("hshoe.in", "r", stdin);
    freopen("hshoe.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string p;
        cin >> p;
        x.push_back(p);
    }
    if (x[0][0] == ')') {
        cout << 0 << endl;
        return 0;
    }
    
    for (int i = N * N / 2; i > 0; --i) {
        z[0][0] = true;
        if (dfs(i - 1, i, 0, 0)) {
            cout << i + i << endl;
            return 0;
        }
        z[0][0] = false;
    }
    
    cout << 0 << endl;
    
    return 0;
}
