#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int n;


int main() {
    freopen("slowdown.in", "r", stdin);
    freopen("slowdown.out", "w", stdout);
    cin >> n;
    vector<double> T, D;
    for (int i = 0; i < n; ++i) {
        string p;
        int a;
        cin >> p >> a;
        if (p == "D") D.push_back(a); else T.push_back(a);
    }
    
    sort(D.begin(), D.end());
    sort(T.begin(), T.end());
    
    int lD = 0, lT = 0, lenD = D.size(), lenT = T.size();
    double ans = 0, speed = 1, pos = 0, time = 0;
    
    for (int i = 0; i < n; ++i) {
        if (lD == lenD) {
            pos += (T[lT] - time) / speed;
            time = T[lT];
            speed += 1;
            ++lT;
        } else
        if (lT == lenT) {
            time += (D[lD] - pos) * speed;
            pos = D[lD];
            speed += 1;
            ++lD;
        } else {
            double npos = pos + (T[lT] - time) / speed;
            if (npos > D[lD]) {
                time += (D[lD] - pos) * speed;
                pos = D[lD];
                speed += 1;
                ++lD;
            } else {
                pos += (T[lT] - time) / speed;
                time = T[lT];
                speed += 1;
                ++lT;
            }
        }
    }
    
    time += (1000 - pos) * speed;
    
    cout << (int)round(time) << endl;
    
    
    return 0;
}
