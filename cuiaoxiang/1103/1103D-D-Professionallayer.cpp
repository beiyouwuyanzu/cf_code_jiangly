// url:https://codeforces.com/contest/1103/problem/D
// time:2022-04-04 14:02:35
// name:D-Professionallayer

// #define LOCAL
#define _USE_MATH_DEFINES
#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <complex>
#include <cmath>
#include <numeric>
#include <bitset>
#include <functional>
#include <random>
#include <ctime>

using namespace std;

template <typename A, typename B>
ostream& operator <<(ostream& out, const pair<A, B>& a) {
  out << "(" << a.first << "," << a.second << ")";
  return out;
}
template <typename T, size_t N>
ostream& operator <<(ostream& out, const array<T, N>& a) {
  out << "["; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "]";
  return out;
}
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "]";
  return out;
}
template <typename T, class Cmp>
ostream& operator <<(ostream& out, const set<T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "}";
  return out;
}
template <typename T, class Cmp>
ostream& operator <<(ostream& out, const multiset<T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "}";
  return out;
}
template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}
#ifdef LOCAL
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
#else
#define trace(...) 42
#endif
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << ": " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << ": " << arg1 << " |";
  __f(comma + 1, args...);
}

template <class T> auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D> auto vect(const T& v, int n, D... m) {
  return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

using int64 = long long;
// using int128 = __int128_t;
using ii = pair<int64, int64>;
#define SZ(x) (int)((x).size())
template <typename T> static constexpr T inf = numeric_limits<T>::max() / 2;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;
// mt19937 mrand(random_device{}());
// int rnd(int x) { return mrand() % x; }
mt19937_64 mrand(random_device{}());
int64 rnd(int64 x) { return mrand() % x; }
int lg2(int64 x) { return sizeof(int64) * 8 - 1 - __builtin_clzll(x); }
template <class T> void out(const vector<T>& a) { for (int i = 0; i < SZ(a); ++i) cout << a[i] << " \n"[i + 1 == SZ(a)]; }
template <class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> void dedup(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

vector<ii> factor(int64 n) {
  vector<ii> ret;
  for (int64 p = 2; p * p <= n; ++p) {
    if (n % p == 0) {
      int cnt = 0;
      while (n % p == 0) {
        n /= p;
        ++cnt;
      }
      ret.push_back({p, cnt});
    }
  }
  if (n > 1) ret.push_back({n, 1});
  return ret;
}

int main() {
  // vector<int64> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
  // vector<int64> three(SZ(p) + 1);
  // three[0] = 1;
  // for (int i = 1; i < SZ(three); ++i) three[i] = three[i - 1] * 3;

  // int64 m = 1e12;
  // for (int k = 1; k <= SZ(p); ++k) {
  //   int64 cnt = 0;
  //   function<void(int, int64)> solve =
  //     [&](int pos, int64 cur) {
  //       // trace(k, pos, cur);
  //       if (pos == k) {
  //         ++cnt;
  //         return;
  //       }
  //       cur *= p[pos];
  //       while (cur <= m) {
  //         solve(pos + 1, cur);
  //         cur *= p[pos];
  //       }
  //     };
  //   solve(0, 1);
  //   trace(k, cnt, cnt * three[k] * k * k / 1e9);
  //   trace(k, cnt, (cnt << k) / 1e6 * 8);
  // }

  int64 n, bound;
  cin >> n >> bound;
  // n = 1000000; bound = 103;
  int64 g = 0;
  vector<int64> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    g = gcd(g, a[i]);
  }
  if (g == 1) {
    cout << 0 << '\n';
    return 0;
  }

  vector<ii> f = factor(g);
  trace(f);

  for (auto& x : a) {
    int64 t = x;
    for (auto& [p, k] : f) {
      while (t % p == 0) t /= p;
    }
    x /= t;
  }

  int len = SZ(f);
  map<int64, vector<int64>> cost;
  for (int i = 0; i < n; ++i) {
    int64 x;
    cin >> x;
    cost[a[i]].push_back(x);
  }

  vector<ii> c;
  vector<int64> can;
  for (auto& [k, v] : cost) {
    sort(v.begin(), v.end());
    for (int i = 0; i < SZ(v) && i < len; ++i) {
      c.push_back({SZ(can), v[i]});
    }
    can.push_back(k);
  }
  // trace(SZ(can), SZ(c), len, SZ(can) * (1 << len) * 8 / 1e6);
  double estimated_ram = SZ(can) * (1 << len) * 8 / 1e6;
  if (estimated_ram >= 100) {
    cout << estimated_ram << " " << len << " " << SZ(can) << '\n';
    return 0;
  }

  auto pick = vect<int64>(0, SZ(can), 1 << len);
  vector<int64> p(len);
  for (int i = 0; i < SZ(can); ++i) {
    auto x = can[i];
    for (int i = 0; i < len; ++i) {
      p[i] = 1;
      while (x % f[i].first == 0) {
        x /= f[i].first;
        p[i] *= f[i].first;
      }
    }
    for (int mask = 0; mask < (1 << len); ++mask) {
      int64 cur = 1;
      for (int i = 0; i < len; ++i) {
        if ((mask >> i) & 1) cur *= p[i];
      }
      pick[i][mask] = cur;
    }
  }
  // trace(pick);

  // trace((1 << len) * (len + 1) * 8 * 2 / 1e3);
  estimated_ram = (1 << len) * (len + 1) * 8 * 2 / 1e6;
  if (estimated_ram >= 100) {
    cout << estimated_ram << " " << len << '\n';
    return 0;
  }

  auto dp = vect<int64>(inf<int64>, 1 << len, len + 1);
  trace(SZ(dp) * SZ(dp[0]) * 8 / 1e6);
  dp[0][0] = 0;
  int all = (1 << len) - 1;
  for (int i = 0; i < SZ(c); ++i) {
    auto ndp = dp;
    for (int mask = 0; mask < (1 << len); ++mask) {
      for (int cnt = 0; cnt < len; ++cnt) {
        if (dp[mask][cnt] == inf<int64>) continue;
        int U = all ^ mask;
        for (int T = U; T; T = (T - 1) & U) {
          if (pick[c[i].first][T] <= bound) {
            ckmin(ndp[mask | T][cnt + 1], c[i].second + dp[mask][cnt]);
          }
        }
      }
    }
    swap(dp, ndp);
  }

  // trace(all, dp[all], bound);

  int64 ret = inf<int64>;
  for (int i = 1; i <= len; ++i) {
    if (dp[all][i] != inf<int64>) {
      ckmin(ret, i * dp[all][i]);
    }
  }
  if (ret == inf<int64>) ret = -1;
  cout << ret << '\n';

  return 0;
}

