// url:https://codeforces.com/contest/1785/problem/C
// time:2023-02-05 16:53:30
// name:C-Monsters(hardversion)

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

template<size_t N>
struct SegmentTree {
  struct Node {
    Node *left, *right;
    int64 cnt, mn, mx, delta;
    void update(int a, int b, int64 c) {
      mn += c;
      mx -= c;
      delta += c;
    }
    void pushup() {
      cnt = left->cnt + right->cnt;
      mn = min(left->mn, right->mn);
      mx = max(left->mx, right->mx);
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
  Node pool[N << 1], *last, *rt;
  int n;
  SegmentTree(int n): n(n) {
    last = pool;
    rt = build(0, n);
  }
  Node* build(int a, int b) {
    Node* ret = last++;
    ret->cnt = 0;
    ret->mx = -1;
    ret->mn = inf<int64>;
    ret->delta = 0;
    if (a + 1 == b) return ret;
    int mid = (a + b) / 2;
    ret->left = build(a, mid);
    ret->right = build(mid, b);
    return ret;
  }
  void set(int pos, int64 c, int64 c2) { return set(rt, 0, n, pos, c, c2); }
  void set(Node* cur, int a, int b, int pos, int64 c, int64 c2) {
    if (pos < a || pos >= b) return;
    if (a + 1 == b) {
      cur->cnt = 1;
      cur->mn = c;
      cur->mx = c2;
      return;
    }
    cur->pushdown(a, b);
    int mid = (a + b) / 2;
    set(cur->left, a, mid, pos, c, c2);
    set(cur->right, mid, b, pos, c, c2);
    cur->pushup();
  }
  void insert(int ll, int rr, int64 c) { return insert(rt, 0, n, ll, rr, c); }
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
  array<int64, 3> query(int ll, int rr) { return query(rt, 0, n, ll, rr); }
  array<int64, 3> query(Node* cur, int a, int b, int ll, int rr) {
    if (ll >= rr || a >= rr || b <= ll) return {0LL, inf<int64>, -1LL};
    if (a >= ll && b <= rr) {
      return {cur->cnt, cur->mn, cur->mx};
    }
    cur->pushdown(a, b);
    int mid = (a + b) / 2;
    int64 cnt = 0, mn = inf<int64>, mx = -1;
    auto L = query(cur->left, a, mid, ll, rr);
    auto R = query(cur->right, mid, b, ll, rr);
    cnt = L[0] + R[0];
    mn = min(L[1], R[1]);
    mx = max(L[2], R[2]);
    return {cnt, mn, mx};
  }
};

const int N = 2e5 + 10;
using segtree = SegmentTree<N>;

template<typename T=int>
struct Fenwick {
  vector<T> c;
  int n;
  Fenwick(int n): n(n) {
    c = vect<T>(T(), n + 1);
  }
  void add(int x, T y) {
    if (x <= 0) return;
    for (; x <= n; x += x & -x) {
      c[x] += y;
    }
  }
  T query(int x) {
    T ret = T();
    for (; x; x -= x & -x) {
      ret += c[x];
    }
    return ret;
  }
};

int main() {
  int cas;
  cin >> cas;
  while (cas--) {
    int n;
    cin >> n;
    vector<ii> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
      cin >> b[i];
      --b[i];
      a[i] = {b[i], -i};
    }
    sort(a.begin(), a.end());
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
      auto [val, k] = a[i];
      pos[-k] = i;
    }
    trace(pos);

    segtree tr(n);
    vector<int64> ret(n);
    // for (int i = 0; i < n; ++i) trace(i, tr.query(i, i + 1));
    // Fenwick F(n);
    for (int i = 0; i < n; ++i) {
      int k = pos[i];
      auto val = tr.query(0, k);
      int cnt = val[2] + 1;
      // int cnt = F.query(k + 1);
      trace(k, cnt);
      trace(i, k, b[i], b[i] - cnt);
      tr.set(k, max(0, b[i] - cnt), cnt);
      int low = k + 1, high = n;
      // for (int j = k + 1; j < n; ++j) {
      //   auto val = tr.query(j, j + 1);
      //   trace(j, val);
      // }
      while (low != high) {
        int mid = (low + high + 1) / 2;
        auto cur = tr.query(k + 1, mid);
        if (cur[1] == 0) {
          high = mid - 1;
        } else {
          low = mid;
        }
      }
      trace(k, k + 1, high);
      tr.insert(k + 1, high, -1);
      // if (k + 1 < high)

      ret[i] = i > 0 ? ret[i - 1] : 0;
      ret[i] += b[i] - cnt;
      cnt = tr.query(k + 1, high)[0];
      ret[i] -= cnt;
    }
    out(ret);
  }

  return 0;
}

