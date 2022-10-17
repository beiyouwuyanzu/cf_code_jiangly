//url:https://codeforces.com/contest/1738/problem/D
//time:2022-09-30 18:01:00
//name:D-PermutationAddicts

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> ch(n + 2);
    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
        ch[b[i]].push_back(i + 1);
    }
    
    int k = 0;
    for (int i = 0; i < n; i++) {
        k += b[i] > i + 1;
    }
    
    int x = 0;
    if (ch[x].empty()) {
        x = n + 1;
    }
    
    std::vector<int> a;
    
    int cnt = 0;
    while (cnt < n) {
        cnt += ch[x].size();
        for (auto &z : ch[x]) {
            if (!ch[z].empty()) {
                std::swap(z, ch[x].back());
            }
        }
        a.insert(a.end(), ch[x].begin(), ch[x].end());
        x = ch[x].back();
    }
    
    std::cout << k << "\n";
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " \n"[i == n - 1];
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
