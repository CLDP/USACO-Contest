#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;


int main() {
    freopen("squares.in", "r", stdin);
    freopen("squares.out", "w", stdout);  
    int N, K;
    cin >> N >> K;
    vector<pair<int, int> > S;
    for (int i = 0; i < N; ++i) {
        int x, y; 
        cin >> x >> y;
        S.push_back(make_pair(x, y));
    }
    sort(S.begin(), S.end());

    set<pair<int, int> > st;
    vector<pair<int, int> > res;
    set<pair<int, int> >::iterator ita, itb;
    for (int i = 0, j = 0; i < N && res.size() < 2; ++i) {
        for( ; S[j].first + K <= S[i].first; ++j) st.erase(make_pair(S[j].second, j));

        ita = itb = st.insert(make_pair(S[i].second, i)).first;
        if (ita-- != st.begin() && S[i].second < ita->first + K) {
            res.push_back(make_pair(i, ita->second));
        }
        if  (++itb != st.end() && itb->first < S[i].second + K) {
            res.push_back(make_pair(i, itb->second));
        }
    }

    long long result = 0;
    if (res.size() > 1) {
        result = -1;
    } else 
    if (res.size() == 1) {
        int dx = S[res[0].first].first - S[res[0].second].first;
        int dy = S[res[0].first].second - S[res[0].second].second;
        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;
        result = 1ll * (K - dx) * (K - dy);
    }
    cout << result << endl;
    
    return 0;
}
