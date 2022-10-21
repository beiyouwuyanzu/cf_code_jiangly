// url:https://codeforces.com/contest/504/problem/D
// time:2022-03-12 14:18:29
// name:D-MishaandXOR

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
template<size_t N> int find_first(const bitset<N>& x) {
#ifdef LOCAL
  int k;
  for (k = 0; k < N && !x[k]; ++k);
  return k;
#else
  return x._Find_first();
#endif
}

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

const int N = 2e3;
using bs = bitset<N>;

int main() {
  int n;
  cin >> n;
  // n = 2000;

  const int K = 26;
  const int M = 1 << K;

  vector<bs> a;
  vector<bs> idx;
  for (int i = 0; i < n; ++i) {
    bs x, y;
    y[i] = 1;
    string s;
    cin >> s;
    // s.resize(600);
    // for (auto& c : s) c = rnd(10) + '0';
    int offset = 0;
    while (SZ(s)) {
      string t;
      int r = 0;
      for (auto& c : s) {
        r = r * 10 + (c - '0');
        if (r < M) {
          if (SZ(t)) t += '0';
        } else {
          t += '0' + r / M;
          r %= M;
        }
      }
      for (int k = 0; k < K; ++k) {
        x[offset + k] = (r >> k) & 1;
      }
      offset += K;
      s = t;
    }
    // trace(x, y);
    for (int j = 0; j < SZ(a); ++j) {
      auto& v = a[j];
      auto& w = idx[j];
      int kx = find_first(x);
      int kv = find_first(v);
      if (kx <= kv) {
        if (v[kx]) {
          x ^= v; y ^= w;
        } else {
          v ^= x; w ^= y;
          x ^= v; y ^= w;
        }
      }
      // for (int k = j; k < N; ++k) {
      //   if (x[k]) {
      //     if (v[k]) {
      //       x ^= v; y ^= w;
      //     } else {
      //       v ^= x; w ^= y;
      //       x ^= v; y ^= w;
      //     }
      //     break;
      //   } else if (v[k]) {
      //     break;
      //   }
      // }
    }
    if (x.count()) {
      a.push_back(x);
      idx.push_back(y);
      cout << 0 << '\n';
    } else {
      y[i] = 0;
      vector<int> ret;
      for (int k = 0; k < N; ++k) {
        if (y[k]) ret.push_back(k);
      }
      cout << SZ(ret) << " ";
      out(ret);
    }
    // trace(a);
    // trace(idx);

  }

  return 0;
}

