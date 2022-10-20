// url:https://codeforces.com/contest/896/problem/C
// time:2022-05-15 11:56:25
// name:C-Willem,ChthollyandSeniorious

#define LOCAL
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

template<typename T=int>
struct odt {
  struct Node {
    int l;
    mutable int r;
    mutable T v;
    bool operator <(const Node& rhs) const { return l < rhs.l; }
  };
  set<Node> a;
  int n;
  odt(int n): n(n) {
    a.insert({0, n, T()});
  }
  auto split(int x) {
    if (x >= n) return a.end();
    auto it = --a.upper_bound({x, 0, T()});
    if (it->l == x) return it;
    auto [l, r, v] = *it;
    it->r = x;
    return a.insert({x, r, v}).first;
  }
  void assign(int l, int r, T v) {
    auto R = split(r);
    auto L = split(l);
    a.erase(L, R);
    a.insert({l, r, v});
  }
  void add(int l, int r, T v) {
    auto R = split(r);
    auto L = split(l);
    for (auto it = L; it != R; ++it) it->v += v;
  }
  vector<Node> get(int l, int r) {
    auto R = split(r);
    auto L = split(l);
    vector<Node> ret;
    for (auto it = L; it != R; ++it) ret.push_back(*it);
    return ret;
  }
  void debug() {
    for (auto& [l, r, v] : a) {
      trace(l, r, v);
    }
  }
};

int seed;
int rnd() {
  int ret = seed;
  seed = (seed * 7LL + 13) % MOD;
  return ret;
}

int64 power_mod(int64 a, int64 n, int p = MOD) {
  int64 ret = 1;
  a %= p;
  for (; n; n >>= 1) {
    if (n & 1) ret = ret * a % p;
    a = a * a % p;
  }
  return ret;
}

int main() {
  int n, m, seed, vmax;
  cin >> n >> m >> seed >> vmax;

  auto rnd =
    [&]() {
      int ret = seed;
      seed = (seed * 7LL + 13) % MOD;
      return ret;
    };

  odt<int64> A(n);
  for (int i = 0; i < n; ++i) {
    int x = rnd() % vmax + 1;
    A.assign(i, i + 1, x);
  }

  while (m--) {
    int op = rnd() % 4 + 1;
    int p = rnd() % n + 1;
    int q = rnd() % n + 1;
    if (p > q) swap(p, q);
    --p;
    int x, y;
    if (op == 3) {
      x = rnd() % (q - p) + 1;
    } else {
      x = rnd() % vmax + 1;
    }
    if (op == 4) {
      y = rnd() % vmax + 1;
    }
    // trace(op, p, q, x, y);

    if (op == 1) {
      A.add(p, q, x);
    } else if (op == 2) {
      A.assign(p, q, x);
    } else if (op == 3) {
      auto a = A.get(p, q);
      sort(a.begin(), a.end(),
           [&](const auto& L, const auto& R) {
             return L.v < R.v;
           });
      int64 ret;
      for (auto& [l, r, v] : a) {
        if (x > r - l) {
          x -= r - l;
        } else {
          ret = v;
          break;
        }
      }
      cout << ret << '\n';
    } else {
      auto a = A.get(p, q);
      int ret = 0;
      for (auto& [l, r, v] : a) {
        ret += power_mod(v, x, y) * (r - l) % y;
        if (ret >= y) ret -= y;
      }
      cout << ret << '\n';
    }

    // A.debug();
  }

  return 0;
}

