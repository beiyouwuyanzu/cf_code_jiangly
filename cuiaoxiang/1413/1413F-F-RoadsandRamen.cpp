// url:https://codeforces.com/contest/1413/problem/F
// time:2022-03-17 05:47:19
// name:F-RoadsandRamen

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
struct Node {
  Node *left, *right;
  array<int, 2> best;
  bool flag;
  void update(int a, int b, int c) {
    trace(a, b, c);
    if (c) swap(best[0], best[1]);
    flag ^= c;
    trace(best, flag);
  }
  void pushup() {
    for (int k = 0; k < 2; ++k) {
      best[k] = max(left->best[k], right->best[k]);
    }
  }
  void pushdown(int a, int b) {
    if (flag) {
      int mid = (a + b) / 2;
      left->update(a, mid, flag);
      right->update(mid, b, flag);
      flag = 0;
    }
  }
};
Node pool[N << 2], *last;
Node* build(int a, int b, const vector<int>& dep, const vector<int>&
            parity, const vector<int>& idx) {
  Node* ret = last++;
  ret->flag = 0;
  ret->best = {-inf<int>, -inf<int>};
  if (a + 1 == b) {
    int u = idx[a];
    ret->best[parity[u]] = dep[u];
    trace(a, b, ret->best);
    return ret;
  }
  int mid = (a + b) / 2;
  ret->left = build(a, mid, dep, parity, idx);
  ret->right = build(mid, b, dep, parity, idx);
  ret->pushup();
  trace(a, b, ret->best);
  return ret;
}
void insert(Node* cur, int a, int b, int ll, int rr, int c) {
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
int query(Node* cur, int a, int b, int ll, int rr) {
  if (ll >= rr || a >= rr || b <= ll) return -inf<int>;
  if (a >= ll && b <= rr) {
    return cur->best[0];
  }
  cur->pushdown(a, b);
  int mid = (a + b) / 2;
  int ret = -inf<int>;
  ckmax(ret, query(cur->left, a, mid, ll, rr));
  ckmax(ret, query(cur->right, mid, b, ll, rr));
  return ret;
}

int main() {
  int n;
  cin >> n;
  vector<ii> e(n - 1);
  vector<vector<ii>> a(n);
  for (int i = 0; i < n - 1; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    --x; --y;
    a[x].push_back({y, z});
    a[y].push_back({x, z});
    e[i] = {x, y};
  }

  auto BFS =
    [&](int s) {
      queue<int> Q;
      Q.push(s);
      int u;
      vector<bool> visit(n);
      visit[s] = 1;
      while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        for (auto& [v, _] : a[u]) {
          if (!visit[v]) {
            visit[v] = 1;
            Q.push(v);
          }
        }
      }
      return u;
    };
  auto s = BFS(0);
  auto t = BFS(s);

  int stamp;
  function<void(int, int, vector<int>&, vector<int>&, vector<int>&,
  vector<int>&, vector<int>&)> DFS =
    [&](int u, int parent, vector<int>& tin, vector<int>& tout,
        vector<int>& dep, vector<int>& parity, vector<int>& idx) {
      dep[u] = parent < 0 ? 0 : dep[parent] + 1;
      idx[stamp] = u;
      tin[u] = stamp++;
      for (auto& [v, w] : a[u]) {
        if (v == parent) continue;
        parity[v] = parity[u] ^ w;
        DFS(v, u, tin, tout, dep, parity, idx);
      }
      tout[u] = stamp;
    };

  vector<int> tinS(n), toutS(n), depS(n), parityS(n), idxS(n);
  vector<int> tinT(n), toutT(n), depT(n), parityT(n), idxT(n);
  stamp = 0;
  DFS(s, -1, tinS, toutS, depS, parityS, idxS);
  stamp = 0;
  DFS(t, -1, tinT, toutT, depT, parityT, idxT);

  last = pool;
  Node* rtS = build(0, n, depS, parityS, idxS);
  Node* rtT = build(0, n, depT, parityT, idxT);

  trace(s, depS, parityS, tinS, toutS, idxS);
  trace(t, depT, parityT, tinT, toutT, idxT);

  int q;
  cin >> q;
  while (q--) {
    int k;
    cin >> k;
    auto [x, y] = e[k - 1];
    trace(x, y);
    int ret = 0;
    // s
    if (depS[x] > depS[y]) swap(x, y);
    insert(rtS, 0, n, tinS[y], toutS[y], 1);
    auto bestS = query(rtS, 0, n, 0, n);
    ckmax(ret, bestS);
    // t
    if (depT[x] > depT[y]) swap(x, y);
    trace(y, tinT[y], toutT[y]);
    insert(rtT, 0, n, tinT[y], toutT[y], 1);
    auto bestT = query(rtT, 0, n, 0, n);
    for (int u = 0; u < n; ++u) {
      trace(u, tinT[u], toutT[u], query(rtT, 0, n, tinT[u], tinT[u] + 1));
    }
    ckmax(ret, bestT);
    trace(bestS, bestT);
    cout << ret << '\n';
  }
  return 0;
}

