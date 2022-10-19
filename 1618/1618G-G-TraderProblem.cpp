// url:https://codeforces.com/contest/1618/problem/G
// time:2021-12-22 10:58:34
// name:G-TraderProblem

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, q;
    std::cin >> n >> m >> q;
    
    std::vector<std::pair<int, int>> a;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        a.emplace_back(x, 1);
    }
    for (int i = 0; i < m; i++) {
        int x;
        std::cin >> x;
        a.emplace_back(x, 0);
    }
    
    const int N = n + m;
    
    std::sort(a.begin(), a.end());
    std::vector<i64> sum(N + 1);
    for (int i = 0; i < N; i++) {
        sum[i + 1] = sum[i] + a[i].first;
    }
    
    std::vector<i64> ans(q);
    std::vector<std::pair<int, int>> k;
    for (int i = 0; i < q; i++) {
        int x;
        std::cin >> x;
        k.emplace_back(x, i);
    }
    
    std::sort(k.begin(), k.end());
    
    i64 S = 0;
    
    std::vector<int> prev(N), next(N), cnt(N);
    for (int i = 0; i < N; i++) {
        prev[i] = i - 1;
        next[i] = i + 1;
        cnt[i] = a[i].second;
        S += cnt[i] * a[i].first;
    }
    
    std::vector<std::pair<int, int>> d;
    for (int i = 0; i < N - 1; i++) {
        d.emplace_back(a[i + 1].first - a[i].first, i);
    }
    std::sort(d.begin(), d.end());
    
    auto get = [&](int x) {
        return sum[x + 1] - sum[x + 1 - cnt[x]];
    };
    
    int i = 0;
    for (auto [k, j] : k) {
        while (i < N - 1 && d[i].first <= k) {
            int x = d[i].second;
            i++;
            int y = next[x];
            S -= get(x) + get(y);
            
            cnt[y] += cnt[x];
            
            int z = prev[x];
            if (z != -1) {
                next[z] = y;
            }
            prev[y] = z;
            
            S += get(y);
        }
        
        ans[j] = S;
    }
    
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}
