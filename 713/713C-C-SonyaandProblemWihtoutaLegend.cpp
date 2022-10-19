// url:https://codeforces.com/contest/713/problem/C
// time:2021-07-07 16:11:04
// name:C-SonyaandProblemWihtoutaLegend

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i] -= i;
    }
    
    std::vector<std::pair<int, int>> stk;
    for (int i = 0; i < n; i++) {
        int l = i, mid = a[i];
        while (!stk.empty() && mid <= stk.back().second) {
            l = stk.back().first;
            std::nth_element(a.begin() + l, a.begin() + (i + l) / 2, a.begin() + i + 1);
            mid = a[(i + l) / 2];
            stk.pop_back();
        }
        stk.emplace_back(l, mid);
    }
    
    i64 ans = 0;
    for (int i = 0, j = 0; i < n; i++) {
        if (j + 1 < int(stk.size()) && stk[j + 1].first <= i) {
            j++;
        }
        ans += std::abs(a[i] - stk[j].second);
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
