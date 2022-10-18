//url:https://codeforces.com/contest/819/problem/E
//time:2021-03-31 16:15:45
//name:E-MisterBandFlighttotheMoon

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::iota(a.begin(), a.end(), 0);
    std::vector<std::vector<int>> ans;
    std::function<void(std::vector<int>)> solve = [&](std::vector<int> a) {
        if (a.size() == 3) {
            ans.push_back(a);
            ans.push_back(a);
        } else if (a.size() == 4) {
            ans.push_back({a[0], a[1], a[2]});
            ans.push_back({a[0], a[1], a[3]});
            ans.push_back({a[0], a[2], a[3]});
            ans.push_back({a[1], a[2], a[3]});
        } else {
            solve(std::vector<int>(a.begin() + 2, a.end()));
            for (int i = 2; i < int(a.size()); i += 2) {
                if (i == 2) {
                    if (a.size() == 5) {
                        ans.push_back({a[0], a[1], a[2]});
                        ans.push_back({a[0], a[1], a[3]});
                        ans.push_back({a[0], a[2], a[1], a[4]});
                        ans.push_back({a[0], a[3], a[1], a[4]});
                        break;
                    } else {
                        ans.push_back({a[0], a[1], a[2]});
                        ans.push_back({a[0], a[1], a[3]});
                        ans.push_back({a[0], a[2], a[1], a[3]});
                    }
                } else {
                    if (int(a.size()) == i + 3) {
                        ans.push_back({a[0], a[i], a[1], a[i + 1]});
                        ans.push_back({a[0], a[i], a[1], a[i + 2]});
                        ans.push_back({a[0], a[i + 2], a[1], a[i + 1]});
                        break;
                    } else {
                        ans.push_back({a[0], a[i], a[1], a[i + 1]});
                        ans.push_back({a[0], a[i], a[1], a[i + 1]});
                    }
                }
            }
        }
    };
    solve(a);
    std::cout << ans.size() << "\n";
    for (int i = 0; i < int(ans.size()); i++) {
        std::cout << ans[i].size();
        for (auto j : ans[i]) {
            std::cout << " " << j + 1;
        }
        std::cout << "\n";
    }
    return 0;
}

