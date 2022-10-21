// url:https://codeforces.com/contest/666/problem/B
// time:2022-04-02 13:35:13
// name:B-WorldTour

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

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n), b(n);
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x; --y;
    a[x].push_back(y);
    b[y].push_back(x);
  }

  auto d = vect<ii>({0, 0}, n, n);
  auto e = vect<ii>({0, 0}, n, n);
  auto BFS =
    [&](vector<vector<int>>& g, int s) {
      vector<int> d(n, -1);
      d[s] = 0;
      queue<int> Q;
      Q.push(s);
      while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for (auto& y : g[x]) {
          if (d[y] < 0) {
            d[y] = d[x] + 1;
            Q.push(y);
          }
        }
      }
      return d;
    };
  auto g = vect<int>(0, n, n);
  for (int i = 0; i < n; ++i) {
    auto D = BFS(a, i);
    auto E = BFS(b, i);
    for (int j = 0; j < n; ++j) {
      g[i][j] = D[j];
      d[i][j] = {D[j], j};
      e[i][j] = {E[j], j};
    }
    sort(d[i].rbegin(), d[i].rend());
    sort(e[i].rbegin(), e[i].rend());
  }
  // trace(e);
  int best = 0;
  vector<int> ret;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j || g[i][j] < 0) continue;
      for (int u = 0; u < 4; ++u) {
        for (int v = 0; v < 4; ++v) {
          int cur = g[i][j];
          auto [D, x] = e[i][u];
          auto [E, y] = d[j][v];
          // trace(i, j, u, v, cur, D, E);
          if (D < 0 || E < 0) continue;
          if (x == y || x == i || x == j || i == y || j == y) continue;
          cur += D + E;
          // trace(i, j, x, y, cur);
          if (cur > best) {
            best = cur;
            ret = {x + 1, i + 1, j + 1, y + 1};
          }
        }
      }
    }
  }

  out(ret);
  return 0;
}

