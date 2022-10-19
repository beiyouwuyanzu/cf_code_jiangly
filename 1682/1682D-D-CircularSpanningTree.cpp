// url:https://codeforces.com/contest/1682/problem/D
// time:2022-05-22 18:22:56
// name:D-CircularSpanningTree

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    if (s == std::string(n, '0') || std::count(s.begin(), s.end(), '1') % 2 != 0) {
        std::cout << "NO\n";
        return;
    }
    
    std::cout << "YES\n";
    
    std::vector<bool> vis(n);
    std::vector<int> ones;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            ones.push_back(i);
        }
    }
    
    for (int i = 0; i < int(ones.size()); i++) {
        for (int j = ones[i]; (j + 1) % n != ones[(i + 1) % ones.size()]; j++) {
            std::cout << j % n + 1 << " " << (j + 1) % n + 1 << "\n";
        }
    }
    
    for (int i = 1; i < int(ones.size()); i++) {
        std::cout << (ones[0] + n - 1) % n + 1 << " " << ones[i] << "\n";
    }
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

