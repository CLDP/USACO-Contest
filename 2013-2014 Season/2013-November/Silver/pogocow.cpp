#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

int n;
int f[MAXN][MAXN];
bool z[MAXN][MAXN];
vector<pair<int, int> > x;


int main() {
    freopen("pogocow.in", "r", stdin);
    freopen("pogocow.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        x.push_back(make_pair(a, b));
    }
    sort(x.begin(), x.end());
    
    for (int i = 0; i < n; ++i) {
        f[i][i] = x[i].second;
        z[i][i] = true;
    }
    
    int ans = 0;
    for (int j = n - 1; j >= 0; --j) {
        int k = n - 1;
        int temp = x[j].second;
        for (int i = 0; i <= j; ++i) {
            while (k > j && x[k].first - x[j].first >= x[j].first - x[i].first) {
                temp = max(temp, f[j][k]);
                --k;
            }
            f[i][j] = temp;
            if (i != j) f[i][j] += x[i].second;
            ans = max(ans, f[i][j]);
        }
    }
    
    for (int j = 0; j < n; ++j) {
        int k = 0;
        int temp = x[j].second;
        for (int i = n - 1; i >= j; --i) {
            while (k < j && x[j].first - x[k].first >= x[i].first - x[j].first) {
                temp = max(temp, f[j][k]);
                ++k;
            }
            f[i][j] = temp;
            if (i != j) f[i][j] += x[i].second;
            ans = max(ans, f[i][j]);
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
