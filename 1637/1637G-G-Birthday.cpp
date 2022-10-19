// url:https://codeforces.com/contest/1637/problem/G
// time:2022-02-12 21:03:44
// name:G-Birthday

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    if (n == 2) {
        std::cout << "-1\n";
        return;
    }
    
    int k = 1;
    while (k < n) {
        k *= 2;
    }
    
    std::vector<int> cnt(k + 1);
    for (int i = 1; i <= n; i++) {
        cnt[i]++;
    }
    
    std::vector<std::pair<int, int>> ans;
    
    auto move = [&](int x, int y) {
        assert(cnt[x] > 0);
        cnt[x]--;
        assert(cnt[y] > 0);
        cnt[y]--;
        assert(x + y <= k);
        cnt[x + y]++;
        cnt[std::abs(x - y)]++;
        ans.emplace_back(x, y);
    };
    
    auto work = [&](auto self, int n, int x) {
        if (n <= 2) {
            return;
        }
        
        int v = 1;
        while (v < n) {
            v *= 2;
        }
        
        if (n == v) {
            n--;
        }
        for (int i = n; i > v / 2; i--) {
            move(x * i, x * (v - i));
        }
        
        self(self, n - v / 2, x * 2);
        self(self, v - n - 1, x);
    };
    
    work(work, n, 1);
    
    for (int i = 1; i < k; i *= 2) {
        while (cnt[i] > 1) {
            move(i, i);
        }
    }
    
    for (int i = 1; i < k; i *= 2) {
        while (cnt[i] > 0) {
            move(i, 0);
            move(i, i);
        }
    }
    
    while (cnt[0] > 0) {
        move(0, k);
    }
    
    assert(cnt[k] == n);
    std::cout << ans.size() << "\n";
    for (auto [x, y] : ans) {
        std::cout << x << " " << y << "\n";
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
