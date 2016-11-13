#include <iostream>
#include <cstdio>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 50010;

int x[MAXN], y[MAXN];


int main() {
    freopen("3lines.in", "r", stdin);
    freopen("3lines.out", "w", stdout);
    int n;
    cin >> n;
    map<int, int> cx, cy;
    map<int, set<int> > xx, yy;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        ++cx[x[i]];
        ++cy[y[i]];
        xx[x[i]].insert(y[i]);
        yy[y[i]].insert(x[i]);
    }
    
    if (cx.size() <= 3 || cy.size() <= 3) {
        cout << 1 << endl;
        return 0;
    }
    
    map<int, int>::iterator iter = cx.begin();
    for (; iter != cx.end(); ++iter) {
        set<int>::iterator iter2 = xx[iter->first].begin();
        while (iter2 != xx[iter->first].end()) {
            --cy[*iter2];
            if (cy[*iter2] == 0) cy.erase(*iter2);
            ++iter2;
        }
        
        if (cy.size() <= 2) {
            cout << 1 << endl;
            return 0;
        }
        
        iter2 = xx[iter->first].begin();
        while (iter2 != xx[iter->first].end()) {
            ++cy[*iter2];
            ++iter2;
        }
    }
    
    iter = cy.begin();
    for (; iter != cy.end(); ++iter) {
        set<int>::iterator iter2 = yy[iter->first].begin();
        while (iter2 != yy[iter->first].end()) {
            --cx[*iter2];
            if (cx[*iter2] == 0) cx.erase(*iter2);
            ++iter2;
        }
        
        if (cx.size() <= 2) {
            cout << 1 << endl;
            return 0;
        }
        
        iter2 = yy[iter->first].begin();
        while (iter2 != yy[iter->first].end()) {
            ++cx[*iter2];
            ++iter2;
        }
    }
    
    cout << 0 << endl;
    
    return 0;
}
