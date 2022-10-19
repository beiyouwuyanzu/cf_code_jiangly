// url:https://codeforces.com/contest/1641/problem/B
// time:2022-02-23 13:24:49
// name:B-RepetitionsDecoding

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<std::pair<int, int>> ins;
    std::vector<int> lens;
    while (!a.empty()) {
        int i = a.size() - 1;
        int j = i - 1;
        while (j >= 0 && a[i] != a[j]) {
            j--;
        }
        if (j == -1) {
            std::cout << "-1\n";
            return;
        }
        for (int k = 0; k < i - j - 1; k++) {
            ins.emplace_back(j + k, a[i - 1 - k]);
        }
        lens.push_back(2 * (i - j));
        std::reverse(a.begin() + j + 1, a.begin() + i);
        a.pop_back();
        a.erase(a.begin() + j);
    }
    
    std::reverse(lens.begin(), lens.end());
    
    std::cout << ins.size() << "\n";
    for (auto [p, c] : ins) {
        std::cout << p << " " << c << "\n";
    }
    std::cout << lens.size() << "\n";
    for (int i = 0; i < int(lens.size()); i++) {
        std::cout << lens[i] << " \n"[i == int(lens.size()) - 1];
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
