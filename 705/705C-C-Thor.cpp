// url:https://codeforces.com/contest/705/problem/C
// time:2023-03-14 19:55:02
// name:C-Thor

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> rd(n), un(n);
    std::vector<int> f;
    int ans = 0;
    int cur = 0;
    
    for (int i = 0; i < q; i++) {
        int t, x;
        std::cin >> t >> x;
        if (t == 1) {
            ans += 1;
            x--;
            f.push_back(x);
            un[x] += 1;
        } else if (t == 2) {
            x--;
            rd[x] = f.size();
            ans -= un[x];
            un[x] = 0;
        } else {
            while (cur < x) {
                if (f[cur] != -1 && cur >= rd[f[cur]]) {
                    ans -= 1;
                    un[f[cur]] -= 1;
                }
                cur += 1;
            }
        }
        std::cout << ans << "\n";
    }
    
    return 0;
}

