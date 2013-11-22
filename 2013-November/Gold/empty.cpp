#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    freopen("empty.in", "r", stdin);
    freopen("empty.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    
    vector<int> x(n, 0);
    for (int i = 0; i < k; ++i) {
        long long X, Y, A, B;
        cin >> X >> Y >> A >> B;
        for (int j = 1; j <= Y; ++j) x[(A * j + B) % n] += X;
    }
    
    int temp = 0;
    for (int i = 0; i < n; ++i) {
        if (x[i] > 0) {
            temp += x[i] - 1;
            x[i] = 1;
        } else {
            if (temp > 0) {
                --temp;
                x[i] = 1;
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if (x[i] == 0) {
            if (temp == 0) {
                cout << i << endl;
                break;
            }
            --temp;
        }
    }
    
    return 0;
}
