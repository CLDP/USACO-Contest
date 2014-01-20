#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 2000000000;

int main() {
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);
    int N, K, pos = 0;
    cin >> N >> K;
    vector<int> L, R;
    for (int i = 0; i < N; ++i) {
        int a;
        string p;
        cin >> a >> p;
        if (p == "R") {
            L.push_back(pos);
            R.push_back(pos + a);
            pos += a;
        } else {
            L.push_back(pos - a);
            R.push_back(pos);
            pos -= a;
        }
    }
    sort(L.begin(), L.end());
    sort(R.begin(), R.end());
    
    int ans = 0, temp = 0, begin = -INF;
    for (int i = 0, j = 0; i < N || j < N; ) {
        if (i < N && L[i] <= R[j]) {
            ++temp;
            if (temp >= K && begin == -INF) begin = L[i];
            ++i;
        } else {
            --temp;
            if (temp < K && begin != -INF) {
                ans += R[j] - begin;
                begin = -INF;
            }
            ++j;
        }
    }
    cout << ans << endl;
    
    return 0;
}
