// url:https://codeforces.com/contest/1253/problem/F
// time:2022-04-18 15:11:54
// name:F-CheapRobot

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

const int N = 1e5 + 10;
const int M = 3e5 + 10;
int64 ret[M];
vector<ii> b[N];

template<size_t N>
struct DSU {
  int f[N], c[N];

  DSU(int n) {
    for (int i = 0; i < n; ++i) f[i] = i, c[i] = 1;
  }
  int find(int x) {
    if (f[x] != f[f[x]]) f[x] = find(f[x]);
    return f[x];
  }
  bool join(int x, int y, int64 w) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;
    if (c[rx] < c[ry]) swap(rx, ry);
    // trace(x, y, rx, ry, b[rx], b[ry]);
    for (auto& [x, id] : b[ry]) {
      if (find(x) == rx) {
        ret[id] = w;
      } else {
        b[rx].push_back({x, id});
      }
    }
    f[ry] = rx;
    c[rx] += c[ry];
    return true;
  }
};

int main() {
  int n, m, k, q;
  cin >> n >> m >> k >> q;
  vector<vector<array<int64, 2>>> a(n);
  for (int i = 0; i < m; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    --x; --y;
    a[x].push_back({y, z});
    a[y].push_back({x, z});
  }

  for (int i = 0; i < q; ++i) {
    int x, y;
    cin >> x >> y;
    --x; --y;
    b[x].push_back({y, i});
    b[y].push_back({x, i});
  }

  vector<int64> d(n, inf<int64>);
  priority_queue<ii, vector<ii>, greater<ii>> Q;
  for (int i = 0; i < k; ++i) {
    d[i] = 0;
    Q.push({d[i], i});
  }
  while (!Q.empty()) {
    auto [dd, u] = Q.top();
    Q.pop();
    if (dd != d[u]) continue;
    for (auto& [v, w] : a[u]) {
      if (d[v] > d[u] + w) {
        d[v] = d[u] + w;
        Q.push({d[v], v});
      }
    }
  }

  vector<array<int64, 3>> e;
  for (int u = 0; u < n; ++u) {
    for (auto& [v, w] : a[u]) {
      e.push_back({d[u] + d[v] + w, u, v});
    }
  }
  sort(e.begin(), e.end());

  DSU<N> uf(n);
  for (auto& [dis, u, v] : e) {
    trace(u, v, dis);
    uf.join(u, v, dis);
  }
  for (int i = 0; i < q; ++i) {
    cout << ret[i] << '\n';
  }

  return 0;
}

