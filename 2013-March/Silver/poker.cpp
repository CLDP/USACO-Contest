#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    freopen("poker.in", "r", stdin);
    freopen("poker.out", "w", stdout);
    int N, pos = 0, a;
    cin >> N;
    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        cin >> a;
        if (a > pos) ans += a - pos;
        pos = a;
    }
    cout << ans << endl;
    
    return 0;
}
