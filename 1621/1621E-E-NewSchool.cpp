// url:https://codeforces.com/contest/1621/problem/E
// time:2022-01-03 18:32:16
// name:E-NewSchool

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::sort(a.begin(), a.end());
    
    std::vector<std::vector<int>> b(m);
    std::vector<int> ave(m);
    for (int i = 0; i < m; i++) {
        int k;
        std::cin >> k;
        b[i].resize(k);
        
        i64 sum = 0;
        
        for (int j = 0; j < k; j++) {
            std::cin >> b[i][j];
            sum += b[i][j];
        }
        ave[i] = (sum + k - 1) / k;
    }
    
    std::vector<int> s(n + 1, 1);
    s[n] = 0;
    for (int i = 0; i < m; i++) {
        ave[i] = std::lower_bound(a.begin(), a.end(), ave[i]) - a.begin();
        s[ave[i]]--;
    }
    for (int i = n - 1; i >= 0; i--) {
        s[i] += s[i + 1];
    }
    
    int v = *std::min_element(s.begin(), s.end());
    if (v >= 0) {
        std::vector<int> prev(n + 1, -1);
        for (int i = 0, j = -1; i <= n; i++) {
            if (s[i] == 0) {
                j = i;
            }
            prev[i] = j;
        }
        
        for (int i = 0; i < m; i++) {
            i64 sum = std::accumulate(b[i].begin(), b[i].end(), 0LL);
            int k = b[i].size();
            for (int j = 0; j < k; j++) {
                i64 nsum = sum - b[i][j];
                int nave = (nsum + k - 2) / (k - 1);
                nave = std::lower_bound(a.begin(), a.end(), nave) - a.begin();
                if (prev[nave] <= ave[i]) {
                    std::cout << "1";
                } else {
                    std::cout << "0";
                }
            }
        }
        std::cout << "\n";
    } else {
        int l = -1, r = -1;
        for (int i = 0; i <= n; i++) {
            if (s[i] < 0) {
                if (l == -1) {
                    l = i;
                }
                r = i;
            }
        }
        for (int i = 0; i < m; i++) {
            i64 sum = std::accumulate(b[i].begin(), b[i].end(), 0LL);
            int k = b[i].size();
            for (int j = 0; j < k; j++) {
                i64 nsum = sum - b[i][j];
                int nave = (nsum + k - 2) / (k - 1);
                nave = std::lower_bound(a.begin(), a.end(), nave) - a.begin();
                if (v == -1 && nave < l && r <= ave[i]) {
                    std::cout << "1";
                } else {
                    std::cout << "0";
                }
            }
        }
        std::cout << "\n";
    }
    
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

