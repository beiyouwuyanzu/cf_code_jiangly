// url:https://codeforces.com/contest/158/problem/D
// time:2023-04-26 19:53:21
// name:D-IceSculptures

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> t(n);
    for (int i = 0; i < n; i++) {
        std::cin >> t[i];
    }
    
    i64 ans = -1E18;
    for (int x = 3; x <= n; x++) {
        if (n % x) {
            continue;
        }
        for (int i = 0; i < n/x; i++) {
            i64 s = 0;
            for (int j = i; j < n; j += n/x) {
                s += t[j];
            }
            ans = std::max(ans, s);
        }
    }
    std::cout << ans << "\n";
    
    return 0;
}
