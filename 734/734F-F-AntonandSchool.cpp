// url:https://codeforces.com/contest/734/problem/F
// time:2021-12-23 19:15:33
// name:F-AntonandSchool

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> b(n), c(n), s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
        s[i] = b[i] + c[i];
    }
    
    i64 S = std::accumulate(s.begin(), s.end(), 0LL);
    
    if (S % (2 * n) != 0) {
        std::cout << "-1\n";
        return 0;
    }
    S /= 2 * n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (s[i] >= S && (s[i] - S) % n == 0) {
            a[i] = (s[i] - S) / n;
        } else {
            std::cout << "-1\n";
            return 0;
        }
    }
    
    std::vector<int> cnt(30);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 30; j++) {
            cnt[j] += a[i] >> j & 1;
        }
    }
    
    for (int i = 0; i < n; i++) {
        i64 rb = 0;
        i64 rc = 0;
        
        for (int j = 0; j < 30; j++) {
            rb += (1LL << j) * (a[i] >> j & 1 ? cnt[j] : 0);
            rc += (1LL << j) * (a[i] >> j & 1 ? n : cnt[j]);
        }
        
        if (rb != b[i] || rc != c[i]) {
            std::cout << "-1\n";
            return 0;
        }
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " \n"[i == n - 1];
    }
    
    return 0;
}
