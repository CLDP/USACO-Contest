#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1000000000;


pair<int, int> z[10][50010];
int z0[10];

int getP(int j, int T) {
    int l = 0, r = z0[j];
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (z[j][mid].first < T) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return z[j][l].second;
}


int main() {
    freopen("cbs.in", "r", stdin);
    freopen("cbs.out", "w", stdout);
    int K, N;
    cin >> K >> N;
    vector<string> p(K, "");
    for (int i = 0; i < K; ++i) {
        cin >> p[i];
        z[i][0] = make_pair(-INF, -1);
        z0[i] = 1;
    }
    
    map<vector<int>, pair<int, int> > y;
    
    int ans = 0;
    vector<int> sum(K, 0);
    for (int i = 0; i < N; ++i) {
        vector<int> temp = sum;
        for (int j = 0; j < K; ++j) {
            if (p[j][i] == '(') ++temp[j]; else --temp[j];
            while (z[j][z0[j] - 1].first >= temp[j]) {
                --z0[j];
            }
            z[j][z0[j]++] = make_pair(temp[j], i);
        }
        
        if (y.find(temp) != y.end()) {
            int left = 0;
            for (int j = 0; j < K; ++j) {
                left = max(left, getP(j, temp[j]));
            }
            if (y[temp].first < left) {
                y[temp] = make_pair(i, 0);
            } else {
                ans += y[temp].second + 1;
                y[temp] = make_pair(i, y[temp].second + 1);
            }
        } else {
            y[temp] = make_pair(i, 0);
        }
        sum = temp;
    }
    cout << ans << endl;
    
    return 0;
}
