#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 20010;

int x[MAXN];
int pos[5][MAXN];
map<int, int> y, z;

bool compare(const int &a, const int &b) {
    int tmp = 0;
    for (int i = 0; i < 5; ++i) tmp += (pos[i][a] < pos[i][b]);
    return tmp > 2;
}


int main() {
    freopen("photo.in", "r", stdin);
    freopen("photo.out", "w", stdout);
    int n, a;
    cin >> n;
    for (int i = 0; i < 5; ++i) 
     for (int j = 0; j < n; ++j) {
         cin >> a;
         if (i == 0) {
             y[j] = a;
             z[a] = j;
         }
         pos[i][z[a]] = j;
     }
    for (int i = 0; i < n; ++i) x[i] = i;
    sort(x, x + n, compare);
    for (int i = 0; i < n; ++i) cout << y[x[i]] << endl;
    return 0;
}
