#include <iostream>
#include <fstream>
using namespace std;

const int MAXN = 1001;

int f[MAXN];

int main() {
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);
    string p;
    cin >> p;
    
    int L = f[1] = 1;
    for (int i = 0; i < p.size(); ++i) {
        int dir = (p[i] == '(' ? 1 : -1);
        L += dir;
        for (int j = (dir < 0 ? 1 : L); 1 <= j && j <= L; j -= dir) {
            f[j] = (f[j] + f[j - dir]) % 2012;
        }
        f[L + 1] = 0;
    }
    
    cout << (L == 1 ? f[1] : 0) << endl;
    
    return 0;
}
