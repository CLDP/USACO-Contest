#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;


int main() {
    freopen("fuel.in", "r", stdin);
    freopen("fuel.out", "w", stdout);
    int N;
    long long G, B, D;
    cin >> N >> G >> B >> D;
    vector<pair<long long, long long> > x(N);
    for (int i = 0; i < N; ++i) cin >> x[i].first >> x[i].second;
    x.push_back(make_pair(D, 0));
    x.push_back(make_pair(0, 100000000));
    N += 2;
    sort(x.begin(), x.end());
    vector<int> next(N, 0);
    stack<pair<long long, int> > ss;
    ss.push(make_pair(0, N - 1));
    for (int i = N - 2; i >= 0; --i) {
        while (ss.top().first > x[i].second) ss.pop();
        next[i] = ss.top().second;
        ss.push(make_pair(x[i].second, i));
    }
    
    long long ans = 0;
    int pos = 0;
    while (pos < N - 1) {
        if (x[pos + 1].first - x[pos].first > G) {
            ans = -1;
            break;
        }
        if (x[next[pos]].first - x[pos].first <= G) {
            if (x[next[pos]].first - x[pos].first > B) {
                ans += (x[next[pos]].first - x[pos].first - B) * x[pos].second;
                B = x[next[pos]].first - x[pos].first;
            }
            B -= x[next[pos]].first - x[pos].first;
            pos = next[pos];
        } else {
            ans += (G - B) * x[pos].second;
            B = G - (x[pos + 1].first - x[pos].first);
            pos = pos + 1;
        }
    }
    
    cout << ans << endl;
    
    return 0;    
}
