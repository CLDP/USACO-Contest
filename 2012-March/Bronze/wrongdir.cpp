#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
const int MX[4] = {0, 1, 0, -1};
const int MY[4] = {1, 0, -1, 0};

// y is the main direction
int x[MAXN], y[MAXN];


int main() {
    freopen("wrongdir.in", "r", stdin);
    freopen("wrongdir.out", "w", stdout);
    string p;
    cin >> p;
    int n = p.size();
    for (int i = n - 1; i >= 0; --i) {
        if (p[i] == 'F') {
            x[i] = x[i + 1];
            y[i] = y[i + 1] + 1;
        } else
        if (p[i] == 'L') {
            x[i] = -y[i + 1];
            y[i] = x[i + 1];
        } else {
            x[i] = y[i + 1];
            y[i] = - x[i + 1];
        }
    }
    
    set<pair<int, int> > z;
    
    int posX = 0, posY = 0, dir = 0;
    for (int i = 0; i < n; ++i) {
        if (p[i] != 'F') {
            int a = posX + MX[dir];
            int b = posY + MY[dir];
            switch (dir) {
                case 0: a += x[i + 1]; b += y[i + 1]; break;
                case 1: a += y[i + 1]; b -= x[i + 1]; break;
                case 2: a -= x[i + 1]; b -= y[i + 1]; break;
                case 3: a -= y[i + 1]; b += x[i + 1]; break;
            }
            z.insert(make_pair(a, b));
        }
        if (p[i] != 'L') {
            int a = posX;
            int b = posY;
            switch ((dir + 3) % 4) {
                case 0: a += x[i + 1]; b += y[i + 1]; break;
                case 1: a += y[i + 1]; b -= x[i + 1]; break;
                case 2: a -= x[i + 1]; b -= y[i + 1]; break;
                case 3: a -= y[i + 1]; b += x[i + 1]; break;
            }
            z.insert(make_pair(a, b));
        }
        if (p[i] != 'R') {
            int a = posX;
            int b = posY;
            switch ((dir + 1) % 4) {
                case 0: a += x[i + 1]; b += y[i + 1]; break;
                case 1: a += y[i + 1]; b -= x[i + 1]; break;
                case 2: a -= x[i + 1]; b -= y[i + 1]; break;
                case 3: a -= y[i + 1]; b += x[i + 1]; break;
            }
            z.insert(make_pair(a, b));
        }
        
        if (p[i] == 'F') {
            posX += MX[dir];
            posY += MY[dir];
        } else
        if (p[i] == 'L') {
            dir = (dir + 3) % 4;
        } else {
            dir = (dir + 1) % 4;
        }
    }
    
    cout << z.size() << endl;
    
    return 0;
}
