//url:https://codeforces.com/contest/1617/problem/C
//time:2021-12-25 11:16:27
//name:C-PaprikaandPermutation

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> vis(n);
    
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if (x <= n && !vis[x - 1]) {
            vis[x - 1] = true;
        } else {
            v.push_back(x);
        }
    }
    
    std::sort(v.begin(), v.end());
    
    int j = 0;
    for (auto x : v) {
        while (vis[j]) {
            j++;
        }
        if (x <= 2 * (j + 1)) {
            std::cout << "-1\n";
            return;
        }
        j++;
    }
    
    std::cout << v.size() << "\n";
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

