//url:https://codeforces.com/contest/1696/problem/C
//time:2022-06-25 17:52:40
//name:C-FishingprincePlaysWithArray

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int k;
    std::cin >> k;
    
    std::vector<int> b(k);
    for (int i = 0; i < k; i++) {
        std::cin >> b[i];
    }
    
    auto get = [&](auto a) {
        int n = a.size();
        std::vector<std::array<i64, 2>> b;
        for (int i = 0; i < n; i++) {
            i64 x = a[i], c = 1;
            while (x % m == 0) {
                x /= m;
                c *= m;
            }
            if (!b.empty() && b.back()[0] == x) {
                b.back()[1] += c;
            } else {
                b.push_back({x, c});
            }
        }
        return b;
    };
    
    if (get(a) == get(b)) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
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

