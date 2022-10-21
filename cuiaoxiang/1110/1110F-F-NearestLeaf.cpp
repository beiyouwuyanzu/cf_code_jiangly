// url:https://codeforces.com/contest/1110/problem/F
// time:2022-04-04 10:35:46
// name:F-NearestLeaf

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

const int N = 5e5 + 10;
vector<ii> a[N];
int64 dep[N];
int ord[N], leaf[N], tin[N], tout[N];

int stamp;
void DFS(int u, int parent) {
  leaf[u] = 1;
  tin[u] = stamp;
  ord[stamp] = u;
  ++stamp;
  for (auto& [v, w] : a[u]) {
    if (v == parent) continue;
    dep[v] = dep[u] + w;
    DFS(v, u);
    leaf[u] = 0;
  }
  tout[u] = stamp;
}

struct Node {
  Node *left, *right;
  int64 mn, delta;
  void update(int a, int b, int64 c) {
    mn += c;
    delta += c;
  }
  void pushup() {
    mn = min(left->mn, right->mn);
  }
  void pushdown(int a, int b) {
    if (delta) {
      int mid = (a + b) / 2;
      left->update(a, mid, delta);
      right->update(mid, b, delta);
      delta = 0;
    }
  }
};
Node pool[N << 1], *last;
Node* build(int a, int b) {
  Node* ret = last++;
  ret->delta = 0;
  if (a + 1 == b) {
    int u = ord[a];
    ret->mn = leaf[u] ? dep[u] : inf<int64>;
    return ret;
  }
  int mid = (a + b) / 2;
  ret->left = build(a, mid);
  ret->right = build(mid, b);
  ret->pushup();
  trace(a, b, ret->mn, ret->delta);
  return ret;
}
void insert(Node* cur, int a, int b, int ll, int rr, int64 c) {
  if (ll >= rr || a >= rr || b <= ll) return;
  if (a >= ll && b <= rr) {
    cur->update(a, b, c);
    return;
  }
  cur->pushdown(a, b);
  int mid = (a + b) / 2;
  insert(cur->left, a, mid, ll, rr, c);
  insert(cur->right, mid, b, ll, rr, c);
  cur->pushup();
}
int64 query(Node* cur, int a, int b, int ll, int rr) {
  if (ll >= rr || a >= rr || b <= ll) return inf<int64>;
  if (a >= ll && b <= rr) {
    return cur->mn;
  }
  cur->pushdown(a, b);
  int mid = (a + b) / 2;
  int64 ret = inf<int64>;
  ckmin(ret, query(cur->left, a, mid, ll, rr));
  ckmin(ret, query(cur->right, mid, b, ll, rr));
  return ret;
}

int main() {
  int n, q;
  cin >> n >> q;

  for (int i = 1; i < n; ++i) {
    int p, w;
    cin >> p >> w;
    --p;
    a[p].push_back({i, w});
    a[i].push_back({p, w});
  }
  for (int i = 0; i < n; ++i) sort(a[i].begin(), a[i].end());

  stamp = 0;
  DFS(0, -1);

  // for (int i = 0; i < n; ++i) {
  //   trace(i, dep[i], tin[i], tout[i], leaf[i]);
  // }
  // for (int i = 0; i < n; ++i) {
  //   trace(i, ord[i]);
  // }

  last = pool;
  Node* rt = build(0, n);

  vector<vector<array<int, 3>>> b(n);
  for (int i = 0; i < q; ++i) {
    int u, L, R;
    cin >> u >> L >> R;
    --L; --u;
    b[u].push_back({L, R, i});
  }

  vector<int64> ret(q);
  function<void(int, int)> solve =
    [&](int u, int parent) {
      for (auto& [L, R, k] : b[u]) {
        ret[k] = query(rt, 0, n, L, R);
      }
      for (auto& [v, w] : a[u]) {
        if (v == parent) continue;
        insert(rt, 0, n, tin[v], tout[v], -w);
        insert(rt, 0, n, 0, tin[v], w);
        insert(rt, 0, n, tout[v], n, w);
        solve(v, u);
        insert(rt, 0, n, tout[v], n, -w);
        insert(rt, 0, n, 0, tin[v], -w);
        insert(rt, 0, n, tin[v], tout[v], w);
      }
    };

  solve(0, -1);

  for (auto& x : ret) cout << x << '\n';
  return 0;
}

