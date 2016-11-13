#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int n, m;
set<string> change[40];
vector<string> NO[110];


bool compare(const vector<string> &a, const vector<string> &b) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return false;
}

long long getN(const vector<string> &now) {
    long long ans = 1;
    for (int i = now.size(); i < m; ++i) ans *= change[i].size();
    
    vector<string> lower = now;
    vector<string> upper = now;
    while (lower.size() < m) {
        lower.push_back("A");
        upper.push_back("zzzzzzzzzzz");
    }
    
    for (int i = 0; i < n; ++i)
     if (!compare(NO[i], lower) && !compare(upper, NO[i])) --ans;
    
    return ans;
}


int main() {
    freopen("nocow.in", "r", stdin);
    freopen("nocow.out", "w", stdout);
    long long k;
    cin >> n >> k;
    string p;
    getline(cin, p);
    getline(cin, p);
    m = -4;
    for (int i = 0; i < p.size(); ++i)
     if (p[i] == ' ') ++m;
     
    istringstream IP(p);
    IP >> p >> p >> p >> p;
    for (int i = 0; i < m; ++i) {
        IP >> p;
        NO[0].push_back(p);
        if (change[i].find(p) == change[i].end()) {
            change[i].insert(p);
        }
    }
    
    for (int i = 1; i < n; ++i) {
        cin >> p >> p >> p >> p;
        for (int j = 0; j < m; ++j) {
            cin >> p;
            NO[i].push_back(p);
            if (change[j].find(p) == change[j].end()) {
                change[j].insert(p);
            }
        }
        cin >> p;
    }
    
    sort(NO, NO+n, compare);
    
    int i = 0;
    vector<string> ans;
    while (i < m) {
        set<string>::iterator iter = change[i].begin();
        ans.push_back(*iter);
        while (true) {
            int total = getN(ans);
            if (k > total) {
                k -= total;
                ++iter;
                ans[i] = *iter;
            } else {
                break;
            }
        }
        ++i;
    }
    cout << ans[0];
    for (int i = 1; i < ans.size(); ++i) cout << " " << ans[i];
    cout << endl;
    
    return 0;
}
