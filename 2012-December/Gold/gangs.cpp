#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int update_state(int &cur_gang, int &cur_cows, int cow_gang) {
    if (cur_cows == 0) cur_gang = cow_gang;
    if (cur_gang == cow_gang) {
        ++cur_cows;
    } else {
        --cur_cows;
    }
    return 0;
}


int max_cows(int cur_gang, int cur_cows, vector<int> G) {
    sort(G.begin() + 1, G.end());
    while (G.back() > 0) {
        for (int i = G.size() - 1; i > 0; --i) {
            update_state(cur_gang, cur_cows, i);
            --G[i];
            if(G[i - 1] <= G[i]) break;
        }
    }
    
    for (int i = 0; i < G[0]; ++i) update_state(cur_gang, cur_cows, 0);
      
    return cur_gang == 0 ? cur_cows : 0;
}

int main() {
    freopen("gangs.in", "r", stdin);
    freopen("gangs.out", "w", stdout);

    int N, M; 
    cin >> N >> M;
    vector<int> G(M);
    for (int i = 0; i < N; ++i) cin >> G[i];

    int cur_gang = 0, cur_cows = 0;
    int res = max_cows(cur_gang, cur_cows, G);
    if (res > 0) {
        cout << "YES" << endl << res << endl;
        for (int i = 0; i < N; ++i) {
            int prev_cur_gang = cur_gang, prev_cur_cows = cur_cows;
            
            for (int j = 0; ; ++j) {
                if (G[j] == 0) continue;
                
                --G[j];
                update_state(cur_gang, cur_cows, j);
                if (max_cows(cur_gang, cur_cows, G) == res) {
                    cout << j + 1 << endl;
                    break;
                }
                ++G[j];
                cur_gang = prev_cur_gang;
                cur_cows = prev_cur_cows;
            }
        }
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
