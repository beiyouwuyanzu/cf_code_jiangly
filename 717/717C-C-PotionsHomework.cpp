// url:https://codeforces.com/contest/717/problem/C
// time:2023-03-15 16:21:08
// name:C-PotionsHomework

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
    std::sort(a.begin(), a.end());
    
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        ans += 1LL * a[i] * a[n - 1 - i];
    }
    std::cout << ans % 10007 << "\n";
    
    return 0;
}

