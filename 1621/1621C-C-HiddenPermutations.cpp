// url:https://codeforces.com/contest/1621/problem/C
// time:2022-01-03 17:50:16
// name:C-HiddenPermutations

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> p(n, -1);
    for (int i = 0; i < n; i++) {
        if (p[i] != -1) {
            continue;
        }
        
        std::vector<int> a;
        
        int y = -1;
        while (true) {
            std::cout << "? " << i + 1 << std::endl;
            int x;
            std::cin >> x;
            x--;
            if (y == -1) {
                y = x;
            } else if (x == y) {
                break;
            }
            a.push_back(x);
        }
        
        for (int j = 0; j < int(a.size()); j++) {
            p[a[j]] = a[(j + 1) % a.size()];
        }
    }
    
    std::cout << "!";
    for (int i = 0; i < n; i++) {
        std::cout << " " << p[i] + 1;
    }
    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

