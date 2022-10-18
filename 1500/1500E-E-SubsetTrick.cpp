//url:https://codeforces.com/contest/1500/problem/E
//time:2021-03-13 14:11:20
//name:E-SubsetTrick

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
struct Data {
    int cnt = 0;
    i64 sum = 0;
    i64 psum = 0;
};
Data operator+(const Data &a, const Data &b) {
    return {a.cnt + b.cnt, a.sum + b.sum, a.psum + b.psum + a.cnt * b.sum};
}
struct SegmentTree {
    std::vector<Data> sum;
    SegmentTree(int n) : sum(4 * n) {}
    void pull(int p) {
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
    void add(int p, int l, int r, int x, int c, i64 v) {
        if (r - l == 1) {
            sum[p].cnt += c;
            sum[p].sum += v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            add(2 * p, l, m, x, c, v);
        } else {
            add(2 * p + 1, m, r, x, c, v);
        }
        pull(p);
    }
    Data presum(int p, int l, int r, int x) {
        if (x == 0) {
            return {};
        }
        if (r - l == 1) {
            return sum[p];
        }
        int m = (l + r) / 2;
        if (sum[2 * p].cnt >= x) {
            return presum(2 * p, l, m, x);
        } else {
            return sum[2 * p] + presum(2 * p + 1, m, r, x - sum[2 * p].cnt);
        }
    }
    Data sufsum(int p, int l, int r, int x) {
        if (x == 0) {
            return {};
        }
        if (r - l == 1) {
            return sum[p];
        }
        int m = (l + r) / 2;
        if (sum[2 * p + 1].cnt >= x) {
            return sufsum(2 * p + 1, m, r, x);
        } else {
            return sufsum(2 * p, l, m, x - sum[2 * p + 1].cnt) + sum[2 * p + 1];
        }
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<i64> s(n), val;
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    val = s;
    std::vector<int> t(q);
    std::vector<i64> a(q);
    for (int i = 0; i < q; i++) {
        std::cin >> t[i] >> a[i];
        val.push_back(a[i]);
    }
    i64 sum = std::accumulate(s.begin(), s.end(), 0ll);
    int siz = n;
    std::sort(val.begin(), val.end());
    val.erase(std::unique(val.begin(), val.end()), val.end());
    for (int i = 0; i < n; i++) {
        s[i] = std::lower_bound(val.begin(), val.end(), s[i]) - val.begin();
    }
    for (int i = 0; i < q; i++) {
        a[i] = std::lower_bound(val.begin(), val.end(), a[i]) - val.begin();
    }
    int m = val.size();
    SegmentTree segt(val.size());
    for (int i = 0; i < n; i++) {
        segt.add(1, 0, m, s[i], 1, val[s[i]]);
    }
    auto f = [&](int x) -> i64 {
        return segt.presum(1, 0, m, x + 1).sum - segt.sufsum(1, 0, m, x).sum;
    };
    auto prefsum = [&](int x) -> i64 {
        auto p = segt.presum(1, 0, m, x);
        return p.sum * x - p.psum - segt.sufsum(1, 0, m, x).psum;
    };
    auto suffsum = [&](int x) -> i64 {
        return segt.sum[1].sum * siz - segt.sum[1].psum * 2 - prefsum(x);
    };
    auto query = [&]() -> i64 {
        if (siz == 0) {
            return 0;
        }
        int mn = (siz - 1) / 2;
        i64 ans = 0;
        if (f(mn) >= 0) {
            ans += segt.sum[1].sum * siz - segt.sum[1].psum * 2;
        } else {
            int l = 0, r = mn;
            while (l < r) {
                int mid = (l + r) / 2;
                if (f(mid) < 0) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            ans += prefsum(l);
            l = mn, r = siz - 1;
            while (l < r) {
                int mid = (l + r) / 2;
                if (f(mid) >= 0) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            ans += suffsum(l);
        }
        ans = sum - ans;
        return ans;
    };
    std::cout << query() << "\n";
    for (int i = 0; i < q; i++) {
        if (t[i] == 1) {
            siz++;
            sum += val[a[i]];
            segt.add(1, 0, m, a[i], 1, val[a[i]]);
        } else {
            siz--;
            sum -= val[a[i]];
            segt.add(1, 0, m, a[i], -1, -val[a[i]]);
        }
        std::cout << query() << "\n";
    }
    return 0;
}
