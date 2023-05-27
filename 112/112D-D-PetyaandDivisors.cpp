// url:https://codeforces.com/contest/112/problem/D
// time:2023-04-27 10:31:52
// name:D-PetyaandDivisors

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    
    int m = *std::max_element(x.begin(), x.end());
    
    std::vector<std::vector<int>> divs(m + 1);
    for (int i = 1; i <= m; i++) {
        for (int j = i; j <= m; j += i) {
            divs[j].push_back(i);
        }
    }
    
    std::vector f(m + 1, -1);
    for (int i = 0; i < n; i++) {
        int ans = 0;
        for (auto d : divs[x[i]]) {
            ans += (f[d] < i - y[i]);
            f[d] = i;
        }
        std::cout << ans << "\n";
    }
    
    return 0;
}
