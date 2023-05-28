// url:https://codeforces.com/contest/1787/problem/E
// time:2023-01-29 19:06:56
// name:E-TheHarmonizationofXOR

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
mt19937_64 mrand(random_device{}());
int64 rnd(int64 x) { return mrand() % x; }
constexpr inline int lg2(int64 x) { return x == 0 ? -1 : sizeof(int64) * 8 - 1 - __builtin_clzll(x); }
constexpr inline int p2ceil(int64 x) { return 1 << (lg2(x - 1) + 1); }
template <class T> void out(const vector<T>& a) { for (int i = 0; i < SZ(a); ++i) cout << a[i] << " \n"[i + 1 == SZ(a)]; }
template <class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> void dedup(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
inline void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
inline void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }
inline int mod(int x) { return x >= MOD ? x - MOD : x; }

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

int main() {
  int cas;
  cin >> cas;

  while (cas--) {
    int n, m, x;
    cin >> n >> m >> x;
    int sum = 0;
    for (int i = 1; i <= n; ++i) sum ^= i;
    bool ok = 1;
    if (m % 2 == 0) {
      if (sum != 0) ok = 0;
    } else {
      if (sum != x) ok = 0;
    }
    if (!ok) {
      cout << "NO" << '\n';
      continue;
    }

    vector<vector<int>> ret;
    vector<bool> vis(n + 1);
    for (int i = 1; i <= n && SZ(ret) < m - 1; ++i) {
      if (vis[i]) continue;
      int j = i ^ x;
      if (j >= 1 && j <= n) {
        vis[i] = vis[j] = 1;
        ret.push_back({i, j});
      }
    }
    if (SZ(ret) == m - 1) {
      vector<int> v;
      for (int i = 1; i <= n; ++i) {
        if (!vis[i]) v.push_back(i);
      }
      ret.push_back(v);
      if (SZ(ret) == m) {
        cout << "YES" << '\n';
        for (auto& v : ret) {
          cout << SZ(v) << " ";
          out(v);
        }
      } else {
        cout << "NO" << '\n';
      }
    } else if (SZ(ret) == m - 2) {
      if (x <= n) {
        vis[x] = 1;
        ret.push_back({x});
      }
      vector<int> v;
      for (int i = 1; i <= n; ++i) {
        if (!vis[i]) v.push_back(i);
      }
      ret.push_back(v);
      if (SZ(ret) == m) {
        cout << "YES" << '\n';
        for (auto& v : ret) {
          cout << SZ(v) << " ";
          out(v);
        }
      } else {
        cout << "NO" << '\n';
      }
    } else {
      cout << "NO" << '\n';
    }
  }

  return 0;
}

