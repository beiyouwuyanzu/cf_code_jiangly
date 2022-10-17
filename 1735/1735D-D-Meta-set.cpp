//url:https://codeforces.com/contest/1735/problem/D
//time:2022-10-04 14:09:00
//name:D-Meta-set

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::map<std::vector<int>, int> cnt;
    
    i64 ans = 0;
    
    std::vector c(n, std::vector<int>(k));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            std::cin >> c[i][j];
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            std::vector<int> a(k);
            for (int x = 0; x < k; x++) {
                a[x] = (c[i][x] + c[j][x]) % 3;
            }
            cnt[a]++;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            
            std::vector<int> a(k);
            for (int x = 0; x < k; x++) {
                a[x] = (c[i][x] + c[j][x]) % 3;
            }
            cnt[a]--;
        }
        std::vector<int> a(k);
        for (int j = 0; j < k; j++) {
            a[j] = (3 - c[i][j]) % 3;
        }
        if (cnt.contains(a)) {
            int x = cnt[a];
            ans += 1LL * x * (x - 1) / 2;
        }
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            
            std::vector<int> a(k);
            for (int x = 0; x < k; x++) {
                a[x] = (c[i][x] + c[j][x]) % 3;
            }
            cnt[a]++;
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
