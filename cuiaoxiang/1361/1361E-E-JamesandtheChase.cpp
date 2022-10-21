// url:https://codeforces.com/contest/1361/problem/E
// time:2022-04-04 02:38:19
// name:E-JamesandtheChase

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
    int n, m;
    cin >> n >> m;
    vector<vector<ii>> a(n);
    for (int i = 0; i < m; ++i) {
      int x, y;
      cin >> x >> y;
      --x; --y;
      a[x].push_back({y, i});
    }

    vector<int> color(n);
    function<bool(int)> test =
      [&](int u) {
        // trace(u, parent, color);
        color[u] = 1;
        for (auto& [v, k] : a[u]) {
          // trace(u, v, color[v]);
          if (color[v] == 0) {
            if (!test(v)) return false;
          } else if (color[v] == 2) {
            return false;
          }
        }
        color[u] = 2;
        return true;
      };

    int T = 100;
    int r = -1;
    for (int t = 0; t < T; ++t) {
      int R = rnd(n);
      fill(color.begin(), color.end(), 0);
      if (test(R)) {
        r = R;
        break;
      }
    }

    if (r < 0) {
      cout << -1 << '\n';
      continue;
    }

    trace(r);
    vector<int> ret;
    vector<int> dfn(n);
    vector<array<ii, 2>> low(n, {{{inf<int>, -1}, {inf<int>, -1}}});

    auto update =
      [&](array<ii, 2>& cur, ii nxt) {
        if (nxt < cur[0]) {
          cur[1] = cur[0];
          cur[0] = nxt;
        } else if (nxt < cur[1]) {
          cur[1] = nxt;
        }
      };

    vector<int> ord, bad(n);
    int stamp = 1;
    function<void(int)> solve =
      [&](int u) {
        ord.push_back(u);
        dfn[u] = stamp++;
        for (auto& [v, k] : a[u]) {
          if (dfn[v]) {
            update(low[u], {dfn[v], k});
          } else {
            solve(v);
            update(low[u], low[v][0]);
            update(low[u], low[v][1]);
          }
        }
        if (low[u][0].first < dfn[u] &&
            low[u][1].first < dfn[u]) {
          bad[u] = 1;
        }
        // trace(u, dfn[u], low[u]);
      };
    solve(r);
    for (auto& u : ord) {
      if (!bad[u] && low[u][0].first != inf<int>) {
        int p = ord[low[u][0].first - 1];
        trace(u, low[u], p, bad[p]);
        bad[u] = bad[p];
      }
    }
    trace(bad);
    for (int i = 0; i < n; ++i) {
      if (!bad[i]) ret.push_back(i + 1);
    }

    if (SZ(ret) * 5 < n) {
      cout << -1 << '\n';
    } else {
      out(ret);
    }

  }

  return 0;
}

