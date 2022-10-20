// url:https://codeforces.com/contest/1679/problem/E
// time:2022-05-14 17:07:41
// name:E-TypicalPartyinDorm

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
// const int MOD = 1e9 + 7;
const int MOD = 998244353;
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
  int n;
  cin >> n;
  // n = 1000;
  string s;
  cin >> s;
  // s = string(n, '?');

  const int K = 17;
  auto cnt = vect<int>(0, K + 1, 1 << K);

  const int M = 1e3 + 10;
  auto pw = vect<int>(0, K + 1, M);
  for (int t = 1; t <= K; ++t) {
    for (int i = 0; i < M; ++i) {
      pw[t][i] = i == 0 ? 1 : 1LL * pw[t][i - 1] * t % MOD;
    }
  }
  vector<int> pre(n + 1);
  for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + (s[i] == '?');
  for (int k = 1; k <= n; ++k) {
    for (int i = 0; i + k <= n; ++i) {
      bool ok = 1;
      int mask = 0, freedom = pre[i] + pre[n] - pre[i + k];
      for (int L = i, R = i + k - 1; L <= R; ++L, --R) {
        if (s[L] == s[R]) {
          if (s[L] == '?') ++freedom;
          continue;
        }
        if (s[L] != '?' && s[R] != '?') {
          ok = 0;
          break;
        }
        int x = s[L] + s[R] - '?' - 'a';
        mask |= 1 << x;
      }
      if (ok) {
        for (int t = 1; t <= K; ++t) {
          add_mod(cnt[t][mask], pw[t][freedom]);
        }
      }
    }
  }
  for (int t = 1; t <= K; ++t) {
    auto& cur = cnt[t];
    for (int k = 0; k < K; ++k) {
      for (int i = 0; i < (1 << K); ++i) {
        if ((i >> k) & 1) add_mod(cur[i], cur[i ^ (1 << k)]);
      }
    }
  }

  int q;
  cin >> q;
  while (q--) {
    string t;
    cin >> t;
    int mask = 0;
    for (auto& c : t) mask |= 1 << (c - 'a');
    int u = __builtin_popcount(mask);
    cout << cnt[u][mask] << '\n';
  }
  return 0;
}

