#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

string p, q;


bool check(long long a) {
    int i = q.size() - 1, tmp = 0;
    while (a > 0) {
        if (q[i] != (a % 3) + '0') ++tmp;
        if (tmp > 1) return false;
        a /= 3;
        --i;
        if (i == -1) break;
    }
    if (a > 0 || i != -1) return false;
    return true;
}

long long get(string p) {
    long long ans = 0;
    for (int i = 0; i < p.size(); ++i) ans = ans * 2 + p[i] - '0';
    return ans;
}

    
int main() {
    freopen("digits.in", "r", stdin);
    freopen("digits.out", "w", stdout);
    cin >> p >> q;
    for (int i = 0; i < p.size(); ++i) {
        p[i] = (p[i] == '0') ? '1' : '0';
        if (check(get(p))) {
            cout << get(p) << endl;
            break;
        }
        p[i] = (p[i] == '0') ? '1' : '0';
    }
    
    return 0;    
}
