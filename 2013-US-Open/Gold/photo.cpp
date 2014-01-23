#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 200001;
const int INF = 1000000000;


int main() {
    freopen("photo.in", "r", stdin);
    freopen("photo.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    vector<pair<int, int> > x(M), y(M);
    for (int i = 0; i < M; ++i) {
        cin >> x[i].first >> x[i].second;
        y[i].second = x[i].first;
        y[i].first = x[i].second;
    }
    y.push_back(make_pair(0, 0));
    y.push_back(make_pair(N + 1, N + 1));
    sort(y.begin(), y.end());
    
    vector<int> maxI(N + 2, 0), minI(N + 2, 0);
    M += 2;
    int pos = N;
    for (int i = M - 1; i >= 0; --i) {
        while (pos >= y[i].second) {
            maxI[pos] = y[i].first;
            --pos;
        }
    }
    pos = 0;
    for (int i = 0; i < M; ++i) {
        while (pos < y[i].second) {
            minI[pos] = y[i].first;
            ++pos;
        }
    }
    
    vector<int> f(N + 2, -INF);
    f[N + 1] = 1;
    set<pair<int, int> > s;
    int L = N + 1, R = N + 1;
    for (int i = N; i >= 0; --i)
     for (int j = maxI[i] + 1; j <= minI[i]; ++j) f[i] = max(f[i], 1 + f[j]);
        
    if (f[0] < 0) cout << -1 << endl; else cout << f[0] - 2 << endl;
    
    return 0;    
}
