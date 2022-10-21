// url:https://codeforces.com/contest/1627/problem/F
// time:2022-04-06 06:57:34
// name:F-NotSplitting

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
  int cas;
  cin >> cas;
  while (cas--) {
    int m, n;
    cin >> m >> n;
    assert(n % 2 == 0);

    int len = (n / 2) * (n + 1) + n / 2 + 1;
    auto normalize =
      [&](int& pos) {
        if (pos >= len) pos = (n + 1) * (n + 1) - pos - 1;
      };
    vector<map<int, int>> a(len);
    auto add_edge =
      [&](int x1, int y1, int x2, int y2, int cost) {
        int u, v;
        if (x1 == x2) {
          if (y1 > y2) swap(y1, y2);
          u = x2 * (n + 1) + y2;
          v = (x2 + 1) * (n + 1) + y2;
        } else {
          if (x1 > x2) swap(x1, x2);
          u = x2 * (n + 1) + y2;
          v = x2 * (n + 1) + (y2 + 1);
        }
        normalize(u); normalize(v);
        // trace(x1, y1, x2, y2, u, v, cost);
        // trace(u, v, len);
        a[u][v] += cost;
        a[v][u] += cost;
      };
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n - 1; ++j) {
        add_edge(i, j, i, j + 1, 0);
      }
    }
    for (int i = 0; i < n - 1; ++i) {
      for (int j = 0; j < n; ++j) {
        add_edge(i, j, i + 1, j, 0);
      }
    }
    for (int i = 0; i < m; ++i) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      --x1; --y1; --x2; --y2;
      add_edge(x1, y1, x2, y2, 1);
    }
    // trace("init");
    priority_queue<ii, vector<ii>, greater<ii>> Q;
    vector<int> d(len, inf<int>);
    for (int j = 0; j <= n; ++j) {
      int u = j;
      d[u] = 0;
      // trace(u, len);
      Q.push({d[u], u});
    }
    for (int i = 1; i <= n / 2; ++i) {
      int u = i * (n + 1);
      d[u] = 0;
      // trace(u, len);
      Q.push({d[u], u});
      if (i < n / 2) {
        u = i * (n + 1) + n;
        d[u] = 0;
        // trace(u, len);
        Q.push({d[u], u});
      }
    }
    while (!Q.empty()) {
      auto [dd, u] = Q.top();
      Q.pop();
      if (dd != d[u]) continue;
      for (auto& [v, w] : a[u]) {
        // trace(u, v, w);
        if (d[v] > d[u] + w) {
          d[v] = d[u] + w;
          Q.push({d[v], v});
        }
      }
    }
    cout << m - d[len - 1] << '\n';

  }

  return 0;
}

