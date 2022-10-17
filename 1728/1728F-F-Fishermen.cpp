//url:https://codeforces.com/contest/1728/problem/F
//time:2022-09-09 10:26:22
//name:F-Fishermen

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
    
    std::map<int, int> id;
    std::vector<std::vector<int>> adj;
    for (int i = 0; i < n; i++) {
        for (int x = 1; x <= n; x++) {
            int b = a[i] * x;
            if (!id.contains(b)) {
                id[b] = id.size();
                adj.push_back({});
            }
            adj[id[b]].push_back(i);
        }
    }
    
    i64 ans = 0;
    int cnt = 0;
    
    const int N = adj.size();
    
    std::vector<int> vis(N, -1), yx(n, -1);
    
    std::function<bool(int, int)> find = [&](int x, int s) {
        vis[x] = s;
        for (auto y : adj[x]) {
            if (yx[y] == -1 || (vis[yx[y]] != s && find(yx[y], s))) {
                yx[y] = x;
                return true;
            }
        }
        return false;
    };
    
    for (auto [x, i] : id) {
        if (cnt < n && find(i, cnt + 1)) {
            ans += x;
            cnt++;
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
