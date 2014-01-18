#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 50001;

int N;
string x[MAXN], y[MAXN], z[MAXN];

int find(string x[], string p) {
    int l = 0, r = N + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (x[mid] < p) 
            l = mid;
        else
            r = mid;
    }
    return l;
}


int main() {
    freopen("scramble.in", "r", stdin);
    freopen("scramble.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> x[i];
        sort(x[i].begin(), x[i].end());
        z[i] = y[i] = x[i];
        for (int j = 0; j < x[i].size(); ++j) y[i][j] = x[i][x[i].size() - 1 - j];
    }
    
    x[N] = y[N] = "\0";
    sort(x, x + N + 1);
    sort(y, y + N + 1);
    
    for (int i = 0; i < N; ++i) {
        string p = z[i];
        for (int j = 0; j < p.size(); ++j) p[j] = z[i][p.size() - 1 - j];
        if (p == z[i]) {
            cout << find(y, p) + 1 << " " << find(x, p) + 1 << endl;
        } else {
            cout << find(y, z[i]) + 1 << " " << find(x, p) << endl;
        }
    }
    
    return 0;
}
