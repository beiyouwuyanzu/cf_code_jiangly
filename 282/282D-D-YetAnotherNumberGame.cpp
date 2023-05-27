// url:https://codeforces.com/contest/282/problem/D
// time:2023-04-27 09:02:23
// name:D-YetAnotherNumberGame

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    if (n != 2) {
        int s = 0;
        for (int i = 0; i < n; i++) {
            s ^= a[i];
        }
        if (s) {
            std::cout << "BitLGM\n";
        } else {
            std::cout << "BitAryo\n";
        }
        return 0;
    }
    
    std::vector win(a[0]+1, std::vector(a[1]+1, 0));
    for (int i = 0; i <= a[0]; i++) {
        for (int j = 0; j <= a[1]; j++) {
            for (int x = 1; x <= i; x++) {
                win[i][j] |= !win[i-x][j];
            }
            for (int x = 1; x <= j; x++) {
                win[i][j] |= !win[i][j-x];
            }
            for (int x = 1; x <= std::min(i, j); x++) {
                win[i][j] |= !win[i-x][j-x];
            }
        }
    }
    
    if (win[a[0]][a[1]]) {
        std::cout << "BitLGM\n";
    } else {
        std::cout << "BitAryo\n";
    }
    
    return 0;
}
