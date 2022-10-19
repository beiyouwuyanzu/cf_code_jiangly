// url:https://codeforces.com/contest/1679/problem/B
// time:2022-05-16 15:13:07
// name:B-StoneAgeProblem

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    i64 sum = 0;
    std::vector<int> a(n), t(n, -1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        sum += a[i];
    }
    
    int tim = -2, b = 0;
    
    for (int i = 0; i < q; i++) {
        int tp;
        std::cin >> tp;
        if (tp == 1) {
            int j, x;
            std::cin >> j >> x;
            j--;
            if (t[j] < tim) {
                sum -= b;
            } else {
                sum -= a[j];
            }
            sum += x;
            a[j] = x;
            t[j] = i;
        } else {
            int x;
            std::cin >> x;
            tim = i;
            b = x;
            sum = 1LL * n * x;
        }
        std::cout << sum << "\n";
    }
    
    return 0;
}
