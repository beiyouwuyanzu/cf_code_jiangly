// url:https://codeforces.com/contest/1641/problem/D
// time:2022-04-19 15:23:34
// name:D-TwoArrays

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

int main() {
  int n, m;
  cin >> n >> m;
  auto a = vect<int>(0, n, m + 1);

  unordered_map<int, int64> A;
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
      auto it = A.find(a[i][j]);
      if (it == A.end()) A[a[i][j]] = mrand();
    }
    cin >> a[i][0];
  }

  sort(a.begin(), a.end());

  unordered_map<int64, int> cnt;
  auto Add =
    [&](int x, int y) {
      for (int mask = 0; mask < (1 << m); ++mask) {
        int64 H = 0;
        for (int i = 0; i < m; ++i) {
          if ((mask >> i) & 1) H ^= A[a[x][i + 1]];
        }
        if (__builtin_parity(mask)) {
          cnt[H] -= y;
        } else {
          cnt[H] += y;
        }
      }
    };

  auto Get =
    [&](int x) {
      int ret = 0;
      for (int mask = 0; mask < (1 << m); ++mask) {
        int64 H = 0;
        for (int i = 0; i < m; ++i) {
          if ((mask >> i) & 1) H ^= A[a[x][i + 1]];
        }
        ret += cnt[H];
      }
      return ret;
    };

  // trace(a);
  int ret = INT_MAX;
  for (int rr = 1, ll = 0; rr < n; ++rr) {
    // trace(rr, ll);
    if (ll == rr - 1) Add(ll, 1);
    // trace(cnt);
    // trace(Get(rr));
    for (; Get(rr) > 0; --ll) {
      Add(ll, -1);
    }
    // trace(ll, rr, a[ll + 1][0] + a[rr][0], Get(rr));
    if (ll + 1 != rr) {
      ckmin(ret, a[ll + 1][0] + a[rr][0]);
    } else {
      ll += 1;
    }
  }

  if (ret == INT_MAX) ret = -1;
  cout << ret << '\n';
  return 0;
}

