#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 1000000;

const int MX[4] = {1, 0, -1, 0};
const int MY[4] = {0, 1, 0, -1};
map<int, map<int, int> > z;
int sy = MAXN, sx = MAXN, d;

int main() {
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);
    int n, x, y;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        z[y][x] = 1;
        if (y < sy || (y == sy && x < sx)) {
            sy = y;
            sx = x;
        }
    }

    y = sy;
    x = sx;
    int ans = 0;
    do {
        y += MX[d];
        x += MY[d];
        ++ans;
        for (d = (d+3) % 4; ; d = (d+1) % 4)
            if ((d == 0 && z[y][x]) || (d == 1 && z[y-1][x]) ||
                (d == 2 && z[y-1][x-1]) || (d == 3 && z[y][x-1])) break;
    } while (y != sy || x != sx);

    cout << ans << endl;
}

