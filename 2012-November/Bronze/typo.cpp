#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    freopen("typo.in", "r", stdin);
    freopen("typo.out", "w", stdout);
    string p;
    cin >> p;
    int a = 0;
    for (int i = 0; i < p.size(); ++i) a += (p[i] == '(');
    
    if (a == p.size() / 2) {
        cout << 0 << endl;
    } else 
    if (a < p.size() / 2) {
        // ) -> (
        int temp = 0, ans = 0;
        for (int i = 0; i < p.size(); ++i) {
            if (p[i] == '(') ++temp; else --temp;
            ans += (p[i] == ')');
            if (temp < 0) break;
        }
        cout << ans << endl;
    } else {
        // ( -> )
        int temp = 0, ans = 0;
        for (int i = p.size() - 1; i >= 0; --i) {
            if (p[i] == ')') ++temp; else --temp;
            ans += (p[i] == '(');
            if (temp < 0) break;
        }
        cout << ans << endl;
    }
    
    return 0;
}
