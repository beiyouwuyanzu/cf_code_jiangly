// url:https://codeforces.com/contest/710/problem/A
// time:2021-07-07 22:04:13
// name:A-KingMoves

#include <bits/stdc++.h>

using i64 = long long;

const std::vector<std::pair<int, int>> moves = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    char a, b;
    std::cin >> a >> b;
    int x = a - 'a', y = b - '1';
    
    int ans = 0;
    for (auto move : moves) {
        int x1 = x + move.first;
        int y1 = y + move.second;
        if (0 <= x1 && x1 < 8 && 0 <= y1 && y1 < 8) {
            ans++;
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
