// url:https://codeforces.com/contest/311/problem/E
// time:2022-01-09 17:46:06
// name:E-Biologist

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

template<size_t N, typename T=int>
struct maxflow {
  struct Edge {
    int v, dual;
    T c;
    Edge(int v, int dual, T c) : v(v), dual(dual), c(c) {}
  };
  vector<Edge> a[N];
  typename vector<Edge>::iterator idx[N];
  int d[N];

  void add_edge(int u, int v, int c, bool bidirection = false) {
    a[u].emplace_back(v, SZ(a[v]), c);
    a[v].emplace_back(u, SZ(a[u]) - 1, bidirection ? c : 0);
  }
  T augment(int u, int t, T bound) {
    if (u == t) return bound;
    T ret = 0;
    // current arc optimization
    for (auto& it = idx[u]; it != a[u].end() && ret < bound; ++it) {
      if (it->c && d[it->v] == d[u] + 1) {
        T aug = augment(it->v, t, min(it->c, bound - ret));
        ret += aug;
        it->c -= aug;
        a[it->v][it->dual].c += aug;
      }
    }
    if (ret == 0) d[u] = -1;
    return ret;
  }
  int n;
  bool path(int s, int t) {
    fill(d, d + n, -1);
    d[s] = 0;
    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      for (auto& p : a[u]) {
        if (p.c && d[p.v] == -1) {
          Q.push(p.v);
          d[p.v] = d[u] + 1;
          if (p.v == t) return true;
        }
      }
    }
    return false;
  }
  maxflow(int n) {
    this->n = n;
    for (int i = 0; i < n; ++i) a[i].clear();
  }
  T dinic(int s, int t) {
    T ret = 0;
    while (path(s, t)) {
      // current arc optimization
      for (int i = 0; i < n; ++i) idx[i] = a[i].begin();
      while (T aug = augment(s, t, inf<T>)) {
        ret += aug;
      }
    }
    return ret;
  }
  vector<int> reach(int s) {
    vector<int> Q;
    Q.push_back(s);
    vector<bool> visit(n);
    visit[s] = true;
    for (int k = 0; k < SZ(Q); ++k) {
      int u = Q[k];
      for (auto& p : a[u]) {
        if (p.c && !visit[p.v]) {
          visit[p.v] = true;
          Q.push_back(p.v);
        }
      }
    }
    return Q;
  }
};

int main() {
  int n, m, g;
  cin >> n >> m >> g;

  vector<int> d(n), v(n);
  for (int i = 0; i < n; ++i) cin >> d[i];
  for (int i = 0; i < n; ++i) cin >> v[i];

  int s = n + m, t = s + 1;
  const int N = 2e4 + 10;
  maxflow<N> flow(t + 1);
  for (int i = 0; i < n; ++i) {
    if (!d[i]) {
      flow.add_edge(s, i, v[i]);
    } else {
      flow.add_edge(i, t, v[i]);
    }
  }

  int ret = 0, sum_g = 0;
  for (int i = 0; i < m; ++i) {
    int k, w, len;
    cin >> k >> w >> len;
    while (len--) {
      int x;
      cin >> x;
      --x;
      if (!k) {
        flow.add_edge(n + i, x, inf<int>);
      } else {
        flow.add_edge(x, n + i, inf<int>);
      }
    }
    int f;
    cin >> f;
    if (f) w += g, sum_g += g;
    if (!k) {
      flow.add_edge(s, n + i, w);
    } else {
      flow.add_edge(n + i, t, w);
    }
    ret += w;
  }

  auto cut = flow.dinic(s, t);
  trace(cut);
  ret -= cut;
  ret -= sum_g;
  cout << ret << '\n';
  return 0;
}

