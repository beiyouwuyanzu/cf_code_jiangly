// url:https://codeforces.com/contest/1307/problem/G
// time:2022-04-05 11:06:49
// name:G-CowandExercise

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

template<size_t N, typename C=int, typename W=int>
struct mcmf {
  struct Edge {
    int v, dual;
    C c;
    W w;
    Edge(int v, int dual, C c, W w) : v(v), dual(dual), c(c), w(w) {}
  };
  vector<Edge> a[N];
  typename vector<Edge>::iterator idx[N];
  int pre[N];
  W d[N], h[N];
  bool visit[N];
  void add_edge(int x, int y, C c, W w) {
    a[x].emplace_back(y, SZ(a[y]), c, w);
    a[y].emplace_back(x, SZ(a[x]) - 1, 0, -w);
  }
  int n;
  mcmf(int n): n(n) {}
  vector<pair<C, W>> dijkstra(int s, int t) {
    vector<pair<C, W>> ret;
    fill(h, h + n, 0);
    C flow = 0;
    W cost = 0;
    while (true) {
      priority_queue<pair<W, int>, vector<pair<W, int>>, greater<pair<W, int>>> Q;
      fill(pre, pre + n, -1);
      fill(d, d + n, inf<W>);
      d[s] = 0;
      Q.push({d[s], s});
      while (!Q.empty()) {
        auto [dd, u] = Q.top();
        Q.pop();
        if (d[u] != dd) continue;
        for (auto it = a[u].begin(); it != a[u].end(); ++it) {
          if (it->c && d[it->v] + h[it->v] > d[u] + h[u] + it->w) {
            d[it->v] = d[u] + h[u] + it->w - h[it->v];
            pre[it->v] = u;
            idx[it->v] = it;
            Q.push({d[it->v], it->v});
          }
        }
      }
      if (pre[t] < 0) break;
      for (int i = 0; i < n; ++i) h[i] += pre[i] < 0 ? 0 : d[i];
      C aug = inf<C>;
      for (int i = t; pre[i] != -1; i = pre[i]) aug = min(aug, idx[i]->c);
      flow += aug;
      for (int i = t; pre[i] != -1; i = pre[i]) {
        idx[i]->c -= aug;
        a[idx[i]->v][idx[i]->dual].c += aug;
        cost += idx[i]->w * aug;
      }
      ret.push_back({flow, cost});
    }
    return ret;
  }
};

int main() {
  int n, m;
  cin >> n >> m;

  const int N = 60;
  mcmf<N> flow(n);
  for (int i = 0; i < m; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    --x; --y;
    flow.add_edge(x, y, 1, z);
  }

  auto cost = flow.dijkstra(0, n - 1);
  trace(cost);

  int q;
  cin >> q;
  while (q--) {
    double x, ret = inf<double>;
    cin >> x;
    for (auto& [f, c] : cost) {
      ckmin(ret, (c + x) / f);
    }
    cout << ret << '\n';
  }

  return 0;
}

