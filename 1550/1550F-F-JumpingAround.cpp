//url:https://codeforces.com/contest/1550/problem/F
//time:2021-07-14 18:23:41
//name:F-JumpingAround

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q, s, d;
    std::cin >> n >> q >> s >> d;
    s--;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> f(n, -1);
    std::priority_queue<std::pair<int, int>> h;
    
    std::set<int> jump, stones;
    for (int i = 0; i < n; i++) {
        stones.insert(i);
    }
    
    auto getK = [&](int u) {
        int x = a[u];
        auto it = jump.lower_bound(x);
        
        int ans = 1e9;
        if (it != jump.end()) {
            ans = std::min(ans, *it - x);
        }
        if (it != jump.begin()) {
            ans = std::min(ans, x - *std::prev(it));
        }
        
        return ans;
    };
    
    h.emplace(0, s);
    
    while (!h.empty()) {
        auto [x, u] = h.top();
        h.pop();
        
        if (f[u] >= 0) {
            continue;
        }
        
        f[u] = -x;
        
        for (auto v : {a[u] - d, a[u] + d}) {
            jump.insert(v);
            
            int j = std::partition_point(a.begin(), a.end(), [&](int x) { return x < v; }) - a.begin();
            
            auto it = stones.lower_bound(j);
            if (it != stones.end()) {
                h.emplace(-std::max(f[u], a[*it] - v), *it);
            }
            
            if (it != stones.begin()) {
                it--;
                h.emplace(-std::max(f[u], v - a[*it]), *it);
            }
        }
        
        stones.erase(u);
        auto it = stones.lower_bound(u);
        
        if (it != stones.end()) {
            h.emplace(-std::max(f[u], getK(*it)), *it);
        }
        if (it != stones.begin()) {
            it--;
            h.emplace(-std::max(f[u], getK(*it)), *it);
        }
    }
    
    while (q--) {
        int i, k;
        std::cin >> i >> k;
        i--;
        
        if (k >= f[i]) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
    
    return 0;
}

