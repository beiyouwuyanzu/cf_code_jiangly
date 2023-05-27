// url:https://codeforces.com/contest/280/problem/B
// time:2023-04-30 08:44:00
// name:B-MaximumXorSecondary

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
    
    int ans = 0;
    std::vector<int> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && a[i] > a[s.back()]) {
            ans = std::max(a[i] ^ a[s.back()], ans);
            s.pop_back();
        }
        if (!s.empty()) {
            ans = std::max(a[i] ^ a[s.back()], ans);
        }
        s.push_back(i);
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
