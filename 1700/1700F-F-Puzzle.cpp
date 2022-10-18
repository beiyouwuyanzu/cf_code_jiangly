//url:https://codeforces.com/contest/1700/problem/F
//time:2022-06-19 13:53:29
//name:F-Puzzle

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::array a{std::vector<int>(n), std::vector<int>(n)}, b(a);
    
    int cnta = 0, cntb = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
            cnta += a[i][j];
        }
    }
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> b[i][j];
            cntb += b[i][j];
        }
    }
    
    if (cnta != cntb) {
        std::cout << "-1\n";
        return 0;
    }
    
    i64 ans = 0;
    int cnt = 0;
    std::array<int, 2> ca{}, cb{};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            if (a[j][i]) {
                cnt++;
                ca[j]++;
            }
            if (b[j][i]) {
                cnt--;
                cb[j]++;
            }
            int t = std::min(ca[j], cb[j]);
            ca[j] -= t;
            cb[j] -= t;
        }
        for (int j = 0; j < 2; j++) {
            int t = std::min(ca[j], cb[!j]);
            ca[j] -= t;
            cb[!j] -= t;
            ans += t;
        }
        ans += std::abs(cnt);
    }
    
    std::cout << ans << "\n";
    
    return 0;
}

