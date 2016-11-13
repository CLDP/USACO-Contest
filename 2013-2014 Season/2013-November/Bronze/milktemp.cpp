#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int INF = 2000000000;

int A[20010], B[20010];

int main() {
    freopen("milktemp.in", "r", stdin);
    freopen("milktemp.out", "w", stdout);
    int n;
    long long x, y, z;
    cin >> n >> x >> y >> z;
    for (int i = 0; i < n; ++i) {
        cin >> A[i] >> B[i];
        ++B[i];
    }
    A[n] = B[n] = INF;
    
    sort(A, A+n);
    sort(B, B+n);
    
    long long temp = x * n;
    long long ans = temp;
    
    int i = 0, j = 0;
    while (i < n && j < n) {
        if (A[i] < B[j]) {
            int k = i;
            while (A[k] == A[i]) ++k;
            temp += (y - x) * (k - i);
            if (ans < temp) ans = temp;
            i = k;
        } else
        if (A[i] > B[j]) {
            int k = j;
            while (B[k] == B[j]) ++k;
            temp += (z - y) * (k - j);
            if (ans < temp) ans = temp;
            j = k;    
        } else {
            int k1 = i, k2 = j;
            while (A[k1] == A[i]) ++k1;
            while (B[k2] == B[j]) ++k2;
            temp += (y - x) * (k1 - i) + (z - y) * (k2 - j);
            if (ans < temp) ans = temp;
            
            i = k1;
            j = k2;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
