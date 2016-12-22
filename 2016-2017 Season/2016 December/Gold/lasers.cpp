#include <iostream>
#include <cstdio>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int X[MAXN], Y[MAXN];
unordered_map<int, vector<int> > XX, YY;
unordered_map<int, int> DX, DY;

int main() {
    ios_base::sync_with_stdio(false);
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    int N, XL, YL, XB, YB;
    cin >> N >> XL >> YL >> XB >> YB;
    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
        XX[X[i]].push_back(i);
        YY[Y[i]].push_back(i);
    }

    if (XL == XB || YL == YB) {
        cout << 0 << endl;
        return 0;
    }

    DX[XL] = DY[YL] = 0;
    queue<pair<int, bool> > Q;
    for (int i = 0; i < N; ++i) {
        if (X[i] == XL) {
            Q.push(make_pair(i, 0));
            DY[Y[i]] = 1;
        }
        if (Y[i] == YL) {
            Q.push(make_pair(i, 1));
            DX[X[i]] = 1;
        }
    }

    while (!Q.empty()) {
        int a = Q.front().first;
        bool b = Q.front().second;
        Q.pop();
        if (b) {
            int curr = DX[X[a]];
            if (X[a] == XB) {
                cout << curr << endl;
                return 0;
            }
            vector<int> &XY = XX[X[a]];
            for (int i = 0; i < XY.size(); ++i) {
                int t = XY[i];
                if (DY.find(Y[t]) != DY.end()) continue;
                Q.push(make_pair(t, 0));
                DY[Y[t]] = curr + 1;
            }
        } else {
            int curr = DY[Y[a]];
            if (Y[a] == YB) {
                cout << curr << endl;
                return 0;
            }
            vector<int> &XY = YY[Y[a]];
            for (int i = 0; i < XY.size(); ++i) {
                int t = XY[i];
                if (DX.find(X[t]) != DX.end()) continue;
                Q.push(make_pair(t, 1));
                DX[X[t]] = curr + 1;
            }
        }
    }
    cout << -1 << endl;
    return 0;
}
