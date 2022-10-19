// url:https://codeforces.com/contest/713/problem/B
// time:2021-07-07 16:05:30
// name:B-SearchingRectangles

#include <bits/stdc++.h>

using i64 = long long;

std::vector<std::tuple<int, int, int, int>> ans;

int query(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2) {
        return 0;
    }
    std::cout << "? " << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
    int res;
    std::cin >> res;
    for (auto [a, b, c, d] : ans) {
        res -= (x1 <= a && c <= x2 && y1 <= b && d <= y2);
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    auto get = [&](auto self, int a, int b, int c, int d) -> void {
        for (int i = 1 << 15; i > 0; i /= 2) {
            if (query(a + i, b, c, d) > 0) {
                a += i;
            }
            if (query(a, b + i, c, d) > 0) {
                b += i;
            }
            if (query(a, b, c - i, d) > 0) {
                c -= i;
            }
            if (query(a, b, c, d - i) > 0) {
                d -= i;
            }
        }
        ans.emplace_back(a, b, c, d);
        if (ans.size() == 1) {
            self(self, 1, 1, n, n);
        } else {
            std::cout << "!";
            for (auto [a, b, c, d] : ans) {
                std::cout << " " << a << " " << b << " " << c << " " << d;
            }
            std::cout << std::endl;
            std::exit(0);
        }
    };
    
    int lo = 1, hi = n;
    while (lo < hi) {
        int m = (lo + hi) / 2;
        int a = query(lo, 1, m, n);
        int b = query(m + 1, 1, hi, n);
        if (a + b == 0) {
            break;
        }
        if (a == 1) {
            get(get, lo, 1, m, n);
        } else if (b == 1) {
            get(get, m + 1, 1, hi, n);
        } else if (a == 2) {
            hi = m;
        } else {
            lo = m + 1;
        }
    }
    
    int loy = 1, hiy = n;
    while (true) {
        int m = (loy + hiy) / 2;
        int a = query(lo, loy, hi, m);
        int b = query(lo, m + 1, hi, hiy);
        if (a + b == 0) {
            break;
        }
        if (a == 1) {
            get(get, lo, loy, hi, m);
        } else if (b == 1) {
            get(get, lo, m + 1, hi, hiy);
        } else if (a == 2) {
            hiy = m;
        } else {
            loy = m + 1;
        }
    }
}
