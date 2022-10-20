// url:https://codeforces.com/contest/741/problem/B
// time:2022-05-20 11:15:44
// name:B-Arpa'sweakamphitheaterandMehrdad'svaluableHoses

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

template<size_t N>
struct DSU {
  int f[N];
  set<int> c[N];

  DSU(int n) {
    for (int i = 0; i < n; ++i) {
      f[i] = i;
      c[i] = {i};
    }
  }
  int find(int x) {
    if (f[x] != f[f[x]]) f[x] = find(f[x]);
    return f[x];
  }
  bool join(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;
    if (SZ(c[rx]) < SZ(c[ry])) swap(rx, ry);
    f[ry] = rx;
    for (auto& t : c[ry]) c[rx].insert(t);
    return true;
  }
};

const int N = 1e3 + 10;
using dsu = DSU<N>;

int main() {
  int n, m, cap;
  cin >> n >> m >> cap;

  vector<int> w(n), b(n);
  for (int i = 0; i < n; ++i) cin >> w[i];
  for (int i = 0; i < n; ++i) cin >> b[i];

  dsu uf(n);
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x; --y;
    uf.join(x, y);
  }
  vector<int> dp(cap + 1, -inf<int>);
  dp[0] = 0;

  for (int i = 0; i < n; ++i) {
    if (uf.find(i) != i) continue;
    int sumW = 0, sumB = 0;
    for (auto t : uf.c[i]) sumW += w[t], sumB += b[t];
    trace(i, sumW, sumB);
    auto ndp = dp;
    for (int j = cap; j >= sumW; --j) {
      ckmax(ndp[j], dp[j - sumW] + sumB);
    }
    for (auto t : uf.c[i]) {
      for (int j = cap; j >= w[t]; --j) {
        ckmax(ndp[j], dp[j - w[t]] + b[t]);
      }
    }
    swap(dp, ndp);
    trace(dp);
  }
  int ret = *max_element(dp.begin(), dp.end());
  cout << ret << '\n';
  return 0;
}

