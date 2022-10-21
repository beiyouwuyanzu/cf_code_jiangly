// url:https://codeforces.com/contest/1444/problem/C
// time:2022-03-26 05:25:04
// name:C-Team-Building

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

template<size_t N>
struct DSU {
  stack<ii> st;
  int f[N], c[N];

  DSU(int n) {
    for (int i = 0; i < n; ++i) f[i] = i, c[i] = 1;
  }
  int find(int x) {
    return x == f[x] ? x : find(f[x]);
    // if (f[x] != f[f[x]]) f[x] = find(f[x]);
    // return f[x];
  }
  bool join(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;
    if (c[rx] < c[ry]) swap(rx, ry);
    f[ry] = rx;
    c[rx] += c[ry];
    st.push({rx, ry});
    return true;
  }
  void undo() {
    auto [rx, ry] = st.top();
    st.pop();
    f[ry] = ry;
    c[rx] -= c[ry];
  }
};

int main() {
  int n, m, ck;

  cin >> n >> m >> ck;
  vector<int> c(n);
  for (int i = 0; i < n; ++i) cin >> c[i], --c[i];

  const int N = 1e6 + 10;
  DSU<N> dsu(n * 2);

  vector<ii> e(m);
  vector<bool> bad(ck);
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x; --y;
    e[i] = {x, y};
    if (c[x] == c[y]) {
      int rx = dsu.find(x), ry = dsu.find(y);
      if (rx == ry) {
        bad[c[x]] = 1;
      } else {
        dsu.join(x, y + n);
        dsu.join(x + n, y);
      }
    }
  }
  map<ii, vector<ii>> can;
  for (auto& [x, y] : e) {
    if (c[x] != c[y] && !bad[c[x]] && !bad[c[y]]) {
      int cx = c[x], cy = c[y];
      if (cx > cy) swap(cx, cy);
      can[{cx, cy}].push_back({x, y});
    }
  }
  int64 cnt = 0;
  for (int i = 0; i < ck; ++i) cnt += !bad[i];
  int64 ret = cnt * (cnt - 1) / 2;

  int old_size = SZ(dsu.st);
  for (auto& [_, v] : can) {
    for (auto& [x, y] : v) {
      int rx = dsu.find(x), ry = dsu.find(y);
      if (rx == ry) {
        --ret;
        break;
      }
      dsu.join(x, y + n);
      dsu.join(x + n, y);
    }
    while (SZ(dsu.st) > old_size) dsu.undo();
  }
  cout << ret << '\n';

  return 0;
}

