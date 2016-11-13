#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 50001;

int x[MAXN], y[MAXN];


int main() {
    freopen("greetings.in", "r", stdin);
    freopen("greetings.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        string p;
        cin >> x[i] >> p;
        if (p == "L") x[i] = -x[i];
    }
    for (int i = 0; i < M; ++i) {
        string p;
        cin >> y[i] >> p;
        if (p == "L") y[i] = -y[i];
    }
    
    int i = 0, j = 0, dir1 = (x[0] > 0 ? 1 : -1), dir2 = (y[0] > 0 ? 1 : -1);
    int pos1 = 0, pos2 = 0, ans = 0;
    bool flag = true;
    while (i < N || j < M) {
        if (x[i] != 0) {
            pos1 += dir1;
            x[i] -= dir1;
            if (x[i] == 0) {
                ++i;
                dir1 = (x[i] > 0 ? 1 : -1);
            }
        }
        if (y[j] != 0) {
            pos2 += dir2;
            y[j] -= dir2;
            if (y[j] == 0) {
                ++j;
                dir2 = (y[j] > 0 ? 1 : -1);
            }
        }
        if (pos1 == pos2 && !flag) {
            ++ans;
            flag = true;
        }
        if (pos1 != pos2) flag = false;
    }
    
    cout << ans << endl;
    
    return 0;
}
