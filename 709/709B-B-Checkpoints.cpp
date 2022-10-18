//url:https://codeforces.com/contest/709/problem/B
//time:2021-12-24 11:59:51
//name:B-Checkpoints

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, a;
    std::cin >> n >> a;
    
    if (n == 1) {
        std::cout << "0\n";
        return 0;
    }
    
    std::vector<int> x(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    
    std::sort(x.begin(), x.end());
    
    int ans = 1E9;
    for (auto c : {0, 1}) {
        int l = a, r = a;
        l = std::min(l, x[c]);
        r = std::max(r, x[c]);
        l = std::min(l, x[c + n - 2]);
        r = std::max(r, x[c + n - 2]);
        ans = std::min(ans, r - l + std::min(r - a, a - l));
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
