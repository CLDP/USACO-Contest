#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2001;

int x[MAXN];
long long f[MAXN];

int main() {
    freopen("wifi.in", "r", stdin);
    freopen("wifi.out", "w", stdout);
    int N;
    long long A, B;
    cin >> N >> A >> B;
    A = A * 2; 
    B = B * 2;
    for (int i = 1; i <= N; ++i) cin >> x[i];
    sort(x + 1, x + N + 1);
    f[1] = A;
    for (int i = 2; i <= N; ++i) {
        f[i] = 2000000000;
        for (int j = i - 1; j >= 0; --j) {
            f[i] = min(f[i], f[j] + A + B / 2 * (x[i] - x[j+1]));
        }
    }
    
    cout << f[N] / 2;
    if (f[N] & 1) cout << ".5";
    cout << endl;
    
    return 0;
}
