// url:https://codeforces.com/contest/1736/problem/C2
// time:2022-10-10 19:02:38
// name:C2-GoodSubarrays(HardVersion)

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (auto &i : a) {
        std::cin >> i;
        i--;
    }
    
    for (int i = 0; i < n; i++) {
        a[i] -= i;
        a[i] = std::min(a[i], 0);
    }
    
    auto b = a;
    for (int i = 1; i < n; i++) {
        b[i] = std::min(b[i - 1], b[i]);
    }
    
    std::vector<i64> s(n + 1);
    for (int i = 0; i < n; i++) {
        s[i + 1] = s[i] + b[i];
    }
    
    int q;
    std::cin >> q;
    
    std::vector<std::vector<std::array<int, 2>>> qry(n);
    
    for (int i = 0; i < q; i++) {
        int p, x;
        std::cin >> p >> x;
        x -= p;
        p--;
        x = std::min(0, x);
        if (p > 0) {
            x = std::min(x, b[p - 1]);
        }
        qry[p].push_back({x, i});
    }
    std::vector<i64> ans(q);
    
    std::vector<int> t{n};
    std::vector<i64> st{0};
    i64 sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (auto [x, j] : qry[i]) {
            ans[j] = 1LL * n * (n + 1) / 2 + s[i];
            auto it = std::partition_point(t.begin() + 1, t.end(), [&](int j) {
                return a[j] < x;
            });
            
            int k = it - t.begin() - 1;
            ans[j] += st[k] + 1LL * (t[k] - i) * x;
        }
        while (t.size() > 1 && a[i] <= a[t.back()]) {
            t.pop_back();
            st.pop_back();
        }
        st.push_back(st.back() + 1LL * (t.back() - i) * a[i]);
        t.push_back(i);
    }
    
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }    
    return 0;
}

