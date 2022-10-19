// url:https://codeforces.com/contest/504/problem/C
// time:2021-06-24 15:59:07
// name:C-MishaandPalindromeDegree

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n), c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
        c[a[i]]++;
    }
    int cntOdd = std::count_if(c.begin(), c.end(), [&](int x) { return x % 2 == 1; });
    if (cntOdd > 1) {
        std::cout << "0\n";
        return 0;
    }
    int k = 0;
    while (k < n && a[k] == a[n - k - 1]) {
        k++;
    }
    if (k == n) {
        std::cout << i64(n) * (n + 1) / 2 << "\n";
        return 0;
    }
    i64 ans = 0;
    int p = (n - 1) / 2;
    while (a[p] == a[n - p - 1]) {
        p--;
    }
    c.assign(n, 0);
    for (int i = k; i <= p; i++) {
        c[a[i]]++;
        c[a[n - i - 1]]--;
    }
    if (c == std::vector(n, 0)) {
        ans += 2ll * (k + 1) * (n / 2 - p);
    }
    ans += i64(k + 1) * (k + 1);
    auto count = [&]() {
        c.assign(n, 0);
        for (int i = k; i <= n / 2; i++) {
            c[a[i]]++;
        }
        for (int i = n / 2 + 1; i < n - k; i++) {
            c[a[i]]--;
        }
        int neg = std::count_if(c.begin(), c.end(), [&](int x) { return x < 0; });
        int pos = n / 2 + 1;
        while (neg > 0) {
            neg -= (c[a[pos]] < 0);
            c[a[pos]] += 2;
            neg += (c[a[pos]] < 0);
            pos++;
        }
        return i64(k + 1) * (n - k - pos);
    };
    ans += count();
    std::reverse(a.begin(), a.end());
    ans += count();
    std::cout << ans << "\n";
    return 0;
}
