// url:https://codeforces.com/contest/1444/problem/A
// time:2022-03-26 04:18:28
// name:A-Division

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
using int128 = __int128_t;
using ii = pair<int, int>;
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

struct Mint {
  int64 n;
  static int64 mod, inv, r2;
  Mint() : n(0) { }
  Mint(const int64 &x) : n(init(x)) { }
  static int64 init(const int64 &w) { return reduce(__uint128_t(w) * r2); }
  static void set_mod(const int64 &m) {
    mod = inv = m;
    for (int i = 0; i < 5; ++i) inv *= 2 - inv * m;
    r2 = -__uint128_t(m) % m;
  }
  static int64 reduce(const __uint128_t &x) {
    int64 y = int64(x >> 64) - int64((__uint128_t(int64(x) * inv) * mod) >> 64);
    return int64_t(y) < 0 ? y + mod : y;
  }
  Mint& operator +=(const Mint &x) { n += x.n - mod; if (int64_t(n) < 0) n += mod; return *this; }
  Mint& operator +(const Mint &x) const { return Mint(*this) += x; }
  Mint& operator *=(const Mint &x) { n = reduce(__uint128_t(n) * x.n); return *this; }
  Mint& operator *(const Mint &x) const { return Mint(*this) *= x; }
  int64 val() const { return reduce(n); }
};

int64 Mint::mod, Mint::inv, Mint::r2;

bool suspect(const int64 &a, const int64 &s, int64 d, const int64 &n) {
  if (Mint::mod != n)  Mint::set_mod(n);
  Mint x(1), xx(a), one(x), minusone(n - 1);
  while (d > 0) {
    if (d & 1) x *= xx;
    xx *= xx;
    d >>= 1;
  }
  if (x.n == one.n)  return true;
  for (unsigned int r = 0; r < s; ++r) {
    if (x.n == minusone.n) return true;
    x *= x;
  }
  return false;
}

bool is_prime(const int64 &n) {
  if (n <= 1 || (n > 2 && (~n & 1))) return false;
  int64 d = n - 1, s = 0;
  while (~d & 1) ++s, d >>= 1;
  static const int64 a_big[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  static const int64 a_smol[] = {2, 7, 61};
  if (n <= 4759123141LL) {
    for (auto &&p : a_smol) {
      if (p >= n)  break;
      if (!suspect(p, s, d, n))  return false;
    }
  } else {
    for (auto &&p : a_big) {
      if (p >= n)  break;
      if (!suspect(p, s, d, n))  return false;
    }
  }
  return true;
}

int64 rho_pollard(const int64 &n) {
  if (~n & 1)  return 2u;
  static random_device rng;
  uniform_int_distribution<int64> rr(1, n - 1);
  if (Mint::mod != n)  Mint::set_mod(n);
  for (;;) {
    int64 c_ = rr(rng), g = 1, r = 1, m = 500;
    Mint y(rr(rng)), xx(0), c(c_), ys(0), q(1);
    while (g == 1) {
      xx.n = y.n;
      for (unsigned int i = 1; i <= r; ++i)  y *= y, y += c;
      int64 k = 0; g = 1;
      while (k < r && g == 1) {
        for (unsigned int i = 1; i <= (m > (r - k) ? (r - k) : m); ++i) {
          ys.n = y.n;
          y *= y; y += c;
          int64 xxx = xx.val(), yyy = y.val();
          q *= Mint(xxx > yyy ? xxx - yyy : yyy - xxx);
        }
        g = gcd(q.val(), n);
        k += m;
      }
      r *= 2;
    }
    if (g == n) g = 1;
    while (g == 1) {
      ys *= ys; ys += c;
      int64 xxx = xx.val(), yyy = ys.val();
      g = gcd(xxx > yyy ? xxx - yyy : yyy - xxx, n);
    }
    if (g != n && is_prime(g)) return g;
  }
}

vector<int64> factor(int64 n) {
  if (n < 2) return {};
  if (is_prime(n)) return {n};
  int64 d = rho_pollard(n);
  vector<int64> L = factor(d), R = factor(n / d);
  L.insert(L.end(), R.begin(), R.end());
  return L;
}

int main() {
  int cas;
  cin >> cas;
  while (cas--) {
    int64 p, q;
    cin >> p >> q;
    if (p % q) {
      cout << p << '\n';
    } else {
      auto f = factor(p);
      map<int64, int> cnt;
      for (auto& x : f) cnt[x]++;
      vector<pair<int64, int>> F;
      for (auto& [k, v] : cnt) F.push_back(make_pair(k, v));
      trace(F);
      int64 ret = 1;
      function<void(int, int64)> solve =
        [&](int pos, int64 cur) {
          if (pos == SZ(F)) {
            if (cur % q) ckmax(ret, cur);
            return;
          }
          int64 nxt = cur;
          solve(pos + 1, nxt);
          for (int i = 0; i < F[pos].second; ++i) {
            nxt *= F[pos].first;
            // trace(pos, nxt, p, q);
            solve(pos + 1, nxt);
          }
        };
      solve(0, 1);
      cout << ret << '\n';
    }
  }

  return 0;
}

