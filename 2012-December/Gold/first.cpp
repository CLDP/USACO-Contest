#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 30010;
const int MAXS = 300010;


struct node {
    char p;
    int s[27];
};

int n, nn = 1;
node x[MAXS];
string y[MAXN];
bool ans[MAXN], z[27][27];


int main() {
    freopen("first.in", "r", stdin);
    freopen("first.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string p;
        cin >> p;
        y[i] = p;
        int temp = 1;
        for (int j = 0; j < p.size(); ++j) {
            if (x[temp].s[p[j] - 'a' + 1] == 0) {
                ++nn;
                x[temp].s[p[j] - 'a' + 1] = nn;
                x[nn].p = p[j];
            }
            temp = x[temp].s[p[j] - 'a' + 1];
        }
        if (x[temp].s[0] == 0) {
            ++nn;
            x[temp].s[0] = nn;
            x[nn].p = 'a' - 1;
        }
    }

    int ansT = 0;
    for (int i = 0; i < n; ++i) {
        int temp = 1;
        memset(z, 0, sizeof(z));
        vector<int> in(27, 0);
        for (int j = 0; j < y[i].size(); ++j) {
            for (int k = 0; k < 27; ++k) {
                if (k == y[i][j] - 'a' + 1) continue;
                if (x[temp].s[k] == 0)  continue;
                if (!z[y[i][j]- 'a' + 1][k]) {
                    z[y[i][j]- 'a' + 1][k] = true;
                    ++in[k];
                }
            }
            temp = x[temp].s[y[i][j] - 'a' + 1];
        }
        
        bool flag = true;
        for (int j = 1; j <= 26; ++j)
         if (z[j][0]) flag = false;
        if (!flag) continue;
        
        vector<bool> cz(27, false);
        while (true) {
            flag = false;
            
            int j;
            for (j = 1; j <= 26; ++j) {
                if (cz[j]) continue;
                if (in[j] != 0) continue;
                flag = true;
                break;
            }
            if (!flag) break;
            
            cz[j] = true;
            for (int k = 1; k <= 26; ++k)
             if (z[j][k]) --in[k];
        }
        
        int total = 0;
        for (int j = 1; j <= 26; ++j) total += cz[j];
        ans[i] = (total == 26);
        ansT += ans[i];
    }
    
    cout << ansT << endl;
    for (int i = 0; i < n; ++i)
     if (ans[i]) cout << y[i] << endl;
    
    return 0;
}
