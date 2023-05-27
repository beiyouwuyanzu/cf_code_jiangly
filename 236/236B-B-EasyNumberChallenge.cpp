// url:https://codeforces.com/contest/236/problem/B
// time:2023-04-30 11:30:57
// name:B-EasyNumberChallenge

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1E6;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::vector<int> d(N + 1);
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            d[j]++;
        }
    }
    
    int a, b, c;
    std::cin >> a >> b >> c;
    
    int ans = 0;
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            for (int k = 1; k <= c; k++) {
                ans += d[i * j * k];
            }
        }
    }
    std::cout << ans << "\n";
    
    return 0;
}
