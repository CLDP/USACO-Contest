#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct pos {
    int x, y;
};

// up, right, down, left
const int MX[4] = {0, 1, 0, -1};
const int MY[4] = {1, 0, -1, 0};

pos P[4];

int main() {
    freopen("ballet.in", "r", stdin);
    freopen("ballet.out", "w", stdout);
    map<string, int> C;
    C["FL"] = 0; C["FR"] = 1;
    C["RL"] = 2; C["RR"] = 3;
    C["F"] = 0;  C["R"] = 1;
    C["B"] = 2;  C["L"] = 3; C["P"] = 4;
    P[0].x = P[2].x = P[2].y = P[3].y = 0;
    P[0].y = P[1].x = P[1].y = P[3].x = 1;
    
    int dir = 0, minX = 0, maxX = 1, minY = 0, maxY = 1, N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string q;
        cin >> q;
        int F = C[q.substr(0, 2)], M = C[q.substr(2, 1)];
        if (M < 4) {
            P[F].x += MX[(dir + M) % 4];
            P[F].y += MY[(dir + M) % 4];
            minX = min(minX, P[F].x); maxX = max(maxX, P[F].x);
            minY = min(minY, P[F].y); maxY = max(maxY, P[F].y);
        } else {
            dir = (dir + 1) % 4;
            for (int j = 0; j < 4; ++j) {
                if (j == F) continue;
                int dx = P[F].x - P[j].x, dy = P[F].y - P[j].y;
                P[j].y = P[F].y + dx;
                P[j].x = P[F].x - dy;
                minX = min(minX, P[j].x); maxX = max(maxX, P[j].x);
                minY = min(minY, P[j].y); maxY = max(maxY, P[j].y);
            }
        }
    }
    
    cout << (maxX - minX + 1) * (maxY - minY + 1) << endl;
    
    
    return 0;
}
