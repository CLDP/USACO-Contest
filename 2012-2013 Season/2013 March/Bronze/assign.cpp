#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 16;

vector<int> same[MAXN], diff[MAXN];
int type[MAXN];
int n, ans;

void dfs(int a) {
    if (a == n) {
        ++ans;
    } else {
        for (int i = 0; i < 3; ++i) {
            type[a] = i;
            bool flag = true;
            for (int j = 0; j < same[a].size(); ++j) {
                if (type[a] != type[same[a][j]]) {
                    flag = false;
                    break;            
                }
            }    
            if (!flag) continue;
            for (int j = 0; j < diff[a].size(); ++j) {
                if (type[a] == type[diff[a][j]]) {
                    flag = false;
                    break;            
                }    
            }
            if (!flag) continue;
            dfs(a + 1);
        }
    }
    return ;
}


int main() {
    freopen("assign.in", "r", stdin);
    freopen("assign.out", "w", stdout);
    int k, a, b;
    string p;
    cin >> n >> k;
    for (int i = 0; i < k; ++i) {
        cin >> p;
        cin >> a >> b;
        --a;
        --b;
        if (p == "S") {
            if (a < b)
                same[b].push_back(a);   
            else 
                same[a].push_back(b);  
        } else {
            if (a < b)
                diff[b].push_back(a);  
            else 
                diff[a].push_back(b);  
        }    
    }
    
    dfs(0);
    
    cout << ans << endl;
    
    return 0;    
}

