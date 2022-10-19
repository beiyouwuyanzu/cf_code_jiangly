// url:https://codeforces.com/contest/1641/problem/D
// time:2022-02-23 14:18:54
// name:D-TwoArrays

#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector a(n, std::pair(0, std::vector<int>(m)));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i].second[j];
        }
        std::cin >> a[i].first;
        std::sort(a[i].second.begin(), a[i].second.end());
    }
    
    std::sort(a.begin(), a.end());
    std::vector<std::tuple<std::vector<int>, int, int>> v;
    v.reserve(n * ((1 << m) - 1));
    for (int i = 0; i < n; i++) {
        std::vector<int> b;
        for (int s = 1; s < (1 << m); s++) {
            b.clear();
            for (int j = 0; j < m; j++) {
                if (s >> j & 1) {
                    b.push_back(a[i].second[j]);
                }
            }
            v.emplace_back(b, i, __builtin_parity(s) ? 1 : -1);
        }
    }
    std::sort(v.begin(), v.end());
    
    std::vector<std::vector<std::pair<int, int>>> q(n);
    
    std::vector<int> cnt(v.size());
    for (int i = 0, j = 0; i < int(v.size()); i = j) {
        j = i;
        while (j < int(v.size()) && std::get<0>(v[i]) == std::get<0>(v[j])) {
            j++;
        }
        for (int k = i; k < j; k++) {
            q[std::get<1>(v[k])].emplace_back(i, std::get<2>(v[k]));
        }
    }
    
    std::vector<int> l(n), r(n, n);
    std::vector<std::vector<int>> chk(n);
    
    while (true) {
        bool finish = true;
        for (int i = 0; i < n; i++) {
            chk[i].clear();
        }
        for (int i = 0; i < n; i++) {
            if (l[i] < r[i]) {
                chk[(l[i] + r[i] - 1) / 2].push_back(i);
                finish = false;
            }
        }
        if (finish) {
            break;
        }
        cnt.assign(cnt.size(), 0);
        for (int i = 0; i < n; i++) {
            for (auto [j, k] : q[i]) {
                cnt[j]++;
            }
            for (auto j : chk[i]) {
                int s = 0;
                for (auto [x, k] : q[j]) {
                    s += k * cnt[x];
                }
                if (s == i + 1) {
                    l[j] = i + 1;
                } else {
                    r[j] = i;
                }
            }
        }
    }
    
    int ans = 2E9 + 100;
    
    for (int i = 0; i < n; i++) {
        if (l[i] < n) {
            ans = std::min(ans, a[i].first + a[l[i]].first);
        }
    }
    
    if (ans > 2E9) {
        ans = -1;
    }
    std::cout << ans << "\n";
    
    return 0;
}
