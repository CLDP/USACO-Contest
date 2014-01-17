#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    freopen("cowfind.in", "r", stdin);
    freopen("cowfind.out", "w", stdout);
    string p;
    cin >> p;
    vector<int> y(p.size(), 0);
    
    for (int i = p.size() - 2; i >= 0; --i) {
        y[i] = y[i+1];
        if (p[i] == ')' && p[i+1] == ')') ++y[i]; 
    }
    
    int ans = 0;
    for (int i = 0; i < p.size(); ++i) 
     if (p[i] == '(' && p[i+1] == '(') ans += y[i+2];
    
    cout << ans << endl;
    
    return 0;
}
