#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100001;

struct cow {
    long long speed, mod;
    int rank;
};

cow x[MAXN];
long long max_speed;
int bit[MAXN];


bool compareM(const cow &a, const cow &b) {
    return a.mod < b.mod;
}

bool compareS(const cow &a, const cow &b) {
    return a.speed < b.speed;
}

long long query(int a) {
    int ans = 0;
    while (a > 0) {
        ans += bit[a];
        a -= a & -a;
    }
    return ans;
}

int update(int a) {
    while (a < MAXN) {
        ++bit[a];
        a += a & -a;
    }
    return 0;
}



int main() {
    freopen("running.in", "r", stdin);
    freopen("running.out", "w", stdout);
    int N;
    long long L, C;
    cin >> N >> L >> C;
    for (int i = 0; i < N; ++i) {
        cin >> x[i].speed;
        max_speed = max(max_speed, x[i].speed);
    }
    
    for (int i = 0; i < N; ++i) x[i].mod = (L * C * x[i].speed) % (C * max_speed);
    sort(x, x + N, compareM);
    int rank = 1;
    for (int i = 0; i < N; ) {
        int j = i + 1;
        while (j < N && x[j].mod == x[i].mod) ++j;
        while (i < j) {
            x[i].rank = rank;
            ++i;
        }
        ++rank;
    }
    
    sort(x, x + N, compareS);
    
    long long ans = 0, sum_floors = 0;
    for (int i = 0; i < N; ++i) {
        long long floor = L * x[i].speed / max_speed;
        ans += (floor - 1) * i - sum_floors + query(x[i].rank);;
        sum_floors += floor;
        update(x[i].rank);
    }
    
    cout << ans << endl;
    
    return 0;
}

