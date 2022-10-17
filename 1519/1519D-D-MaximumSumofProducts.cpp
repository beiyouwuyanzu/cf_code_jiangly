//url:https://codeforces.com/contest/1519/problem/D
//time:2022-06-27 11:35:45
//name:D-MaximumSumofProducts

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n);
    i64 sum = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
        sum += 1LL * a[i] * b[i];
    }
    
    i64 ans = sum;
    for (int s = 0; s <= 2 * n - 2; s++) {
        i64 cur = sum;
        for (int i = s / 2; i >= 0 && s - i < n; i--) {
            cur -= 1LL * a[i] * b[i] + 1LL * a[s - i] * b[s - i];
            cur += 1LL * a[i] * b[s - i] + 1LL * a[s - i] * b[i];
            ans = std::max(ans, cur);
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}

