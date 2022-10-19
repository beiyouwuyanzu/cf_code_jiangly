// url:https://codeforces.com/contest/1514/problem/E
// time:2021-04-19 19:53:46
// name:E-BabyEhab'sHyperApartment

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int query1(int a, int b) {
    std::cout << "1 " << a << " " << b << std::endl;
    int ans;
    std::cin >> ans;
    return ans;
}
int query2(int a, std::vector<int> b) {
    std::cout << "2 " << a << " " << b.size();
    for (auto x : b) {
        std::cout << " " << x;
    }
    std::cout << std::endl;
    int ans;
    std::cin >> ans;
    return ans;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a{0};
        for (int i = 1; i < n; i++) {
            if (query1(i, a[0])) {
                a.insert(a.begin(), i);
                continue;
            }
            if (query1(a.back(), i)) {
                a.insert(a.end(), i);
                continue;
            }
            int l = 0, r = a.size() - 1;
            while (l + 1 < r) {
                int m = (l + r) / 2;
                if (query1(i, a[m])) {
                    r = m;
                } else {
                    l = m;
                }
            }
            a.insert(a.begin() + r, i);
        }
        std::vector<std::string> ans(n, std::string(n, '0'));
        std::vector<int> r{0};
        for (int i = 1; i < n; i++) {
            int u = a[i];
            r.push_back(i);
            while (query2(u, std::vector(a.begin(), a.begin() + r.back()))) {
                r.pop_back();
            }
        }
        r.push_back(n);
        for (int i = 0; i < int(r.size()) - 1; i++) {
            for (int j = r[i]; j < r[i + 1]; j++) {
                int u = a[j];
                for (int k = r[i]; k < n; k++) {
                    int v = a[k];
                    ans[u][v] = '1';
                }
            }
        }
        std::cout << "3\n";
        for (int i = 0; i < n; i++) {
            std::cout << ans[i] << "\n";
        }
        std::cout.flush();
        int result;
        std::cin >> result;
    }
    return 0;
}
