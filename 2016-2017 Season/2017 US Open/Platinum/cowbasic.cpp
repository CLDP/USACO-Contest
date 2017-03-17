#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INF = 1000000007;

int M;

struct block {
    vector<vector<int> > x;
    block() {
        x = vector<vector<int> > (M + 2, vector<int> (M + 2, 0));
    }
    block operator * (const block &B) {
        block ans;
        for (int i = 1; i <= M + 1; ++i) {
            for (int j = 1; j <= M + 1; ++j) {
                for (int k = 1; k <= M + 1; ++k) {
                    ans.x[i][k] = (ans.x[i][k] + 1LL * x[i][j] * B.x[j][k]) % INF;
                }
            }
        }
        return ans;
    }

    vector<int> operator * (const vector<int> &B) {
        vector<int> ans(M + 2, 0);
        for (int i = 1; i <= M + 1; ++i) {
            if (B[i] == 0) continue;
            for (int j = 1; j <= M + 1; ++j) {
                ans[j] = (ans[j] + 1LL * x[i][j] * B[i]) % INF;
            }
        }
        return ans;
    }
};

vector<vector<string> > X;
map<string, int> C;

block bpower(block B, int T) {
    block ans;
    for (int i = 1; i <= M + 1; ++i) ans.x[i][i] = 1;
    for (int i = 1; i <= M + 1; ++i) {
        int cnt = 0;
        for (int j = 1; j <= M + 1; ++j) cnt += (B.x[i][j] != 0);
        if (cnt == 0) B.x[i][i] = 1;
    }
    for (int i = 0; (1 << i) <= T; ++i) {
        if (T & (1 << i)) ans = ans * B;
        B = B * B;
    }
    return ans;
}


block cal(int a, int b) {
    block ans;
    for (int i = 1; i <= M + 1; ++i) ans.x[i][i] = 1;
    for (int i = a; i <= b; ++i) {
        if (isdigit(X[i][0][0])) {
            // This is a loop
            int T = atoi(X[i][0].c_str());
            int cnt = 1, j = i;
            while (cnt > 0) {
                ++j;
                if (isdigit(X[j][0][0])) ++cnt;
                if (X[j][0] == "}") --cnt;
            }
            block A = cal(i + 1, j - 1);
            A = bpower(A, T);
            ans = A * ans;
            i = j;
        } else
        if (islower(X[i][0][0])) {
            // This is a statement
            vector<int> x(M + 2, 0);
            for (int j = 1; j < X[i].size(); ++j) {
                if (isdigit(X[i][j][0])) x[M + 1] += atoi(X[i][j].c_str());
                if (islower(X[i][j][0])) ++x[C[X[i][j]]];
            }
            ans.x[C[X[i][0]]] = ans * x;
        } 
    }
    return ans;
}


int main() {
    freopen("cowbasic.in", "r", stdin);
    freopen("cowbasic.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    string P;
    while (getline(cin, P)) {
        istringstream PIN(P);
        string Q;
        vector<string> Y;
        while (PIN >> Q) Y.push_back(Q);
        X.push_back(Y);
    }
    for (int i = 0; i < X.size(); ++i) {
        string Q = X[i][0];
        if (islower(Q[0]) && Q != "MOO" && C.find(Q) == C.end()) C[Q] = ++M;
    }

    block B = cal(0, X.size() - 2);
    cout << B.x[C[X[X.size() - 1][1]]][M + 1] << endl;

    return 0;
}
