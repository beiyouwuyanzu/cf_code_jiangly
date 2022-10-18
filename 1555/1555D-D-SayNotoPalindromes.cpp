//url:https://codeforces.com/contest/1555/problem/D
//time:2022-06-12 12:27:24
//name:D-SayNotoPalindromes

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::string s;
    std::cin >> s;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - 'a';
    }
    
    std::vector sum(6, std::vector<int>(n + 1));
    std::vector p{ 0, 1, 2 };
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < n; j++) {
            sum[i][j + 1] = sum[i][j] + (a[j] != p[j % 3]);
        }
        std::next_permutation(p.begin(), p.end());
    }
    
    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        
        int ans = n;
        for (int j = 0; j < 6; j++) {
            ans = std::min(ans, sum[j][r] - sum[j][l]);
        }
        
        std::cout << ans << "\n";
    }
    
    return 0;
}

