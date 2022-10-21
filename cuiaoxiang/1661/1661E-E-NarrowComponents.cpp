// url:https://codeforces.com/contest/1661/problem/E
// time:2022-04-09 18:15:33
// name:E-NarrowComponents

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

const int M = 6;
struct State {
  int ll, rr;
  array<bitset<M>, M> state {};
  int cnt;
  State(): ll(0), rr(0), cnt(0) {};
  friend ostream& operator <<(ostream& out, const State& obj) {
    out << obj.ll << " " << obj.rr << " " << obj.cnt;
    return out;
  }
};

template<size_t N>
struct DSU {
  int f[N];

  DSU(int n) {
    for (int i = 0; i < n; ++i) f[i] = i;
  }
  int find(int x) {
    if (f[x] != f[f[x]]) f[x] = find(f[x]);
    return f[x];
  }
  bool join(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;
    // if (c[rx] < c[ry]) swap(rx, ry);
    f[ry] = rx;
    // c[rx] += c[ry];
    return true;
  }
};

State merge(const State& L, const State& R) {
  State ret;
  ret.cnt = L.cnt + R.cnt;
  DSU<12> dsu(12);
  for (int i = 0; i < M; ++i) {
    for (int j = i + 1; j < M; ++j) {
      if (L.state[i][j]) dsu.join(i, j);
    }
  }
  for (int i = 0; i < M; ++i) {
    for (int j = i + 1; j < M; ++j) {
      if (R.state[i][j]) dsu.join(i + M, j + M);
    }
  }
  for (int k = 0; k < 3; ++k) {
    int x = (L.rr >> k) & 1;
    int y = (R.ll >> k) & 1;
    if (x && y) {
      if (dsu.join(3 + k, 6 + k)) ret.cnt--;
    }
  }
  ret.ll = L.ll;
  ret.rr = R.rr;
  for (int i = 0; i < M; ++i) {
    for (int j = i + 1; j < M; ++j) {
      int x = i < 3 ? i : i + 6;
      int y = j < 3 ? j : j + 6;
      ret.state[i][j] = dsu.find(x) == dsu.find(y);
    }
  }
  return ret;
}

State get(int mask) {
  State ret;
  ret.ll = ret.rr = mask;
  DSU<3> dsu(3);
  ret.cnt = __builtin_popcount(mask);
  for (int k = 1; k < 3; ++k) {
    int x = (mask >> (k - 1)) & 1;
    int y = (mask >> k) & 1;
    if (x && y) {
      if (dsu.join(k - 1, k)) ret.cnt--;
    }
  }
  for (int i = 0; i < M; ++i) {
    for (int j = i + 1; j < M; ++j) {
      int x = i % 3;
      int y = j % 3;
      ret.state[i][j] = dsu.find(x) == dsu.find(y);
    }
  }
  trace(mask, ret);
  return ret;
}

const int N = 5e5 + 10;
struct Node {
  Node *left, *right;
  State s;
  void pushup() {
    s = merge(left->s, right->s);
  }
};
Node pool[N << 1], *last;
Node* build(int a, int b, const vector<int>& mask) {
  Node* ret = last++;
  if (a + 1 == b) {
    ret->s = get(mask[a]);
    return ret;
  }
  int mid = (a + b) / 2;
  ret->left = build(a, mid, mask);
  ret->right = build(mid, b, mask);
  ret->pushup();
  return ret;
}
State query(Node* cur, int a, int b, int ll, int rr) {
  if (ll >= rr || a >= rr || b <= ll) return State();
  if (a >= ll && b <= rr) {
    return cur->s;
  }
  int mid = (a + b) / 2;
  State L = query(cur->left, a, mid, ll, rr);
  State R = query(cur->right, mid, b, ll, rr);
  return merge(L, R);
}

int main() {
  int n;
  cin >> n;
  // n = 5e5;
  vector<int> mask(n);
  string s;
  for (int i = 0; i < 3; ++i) {
    cin >> s;
    for (int j = 0; j < n; ++j) {
      mask[j] |= (s[j] - '0') << i;
      // mask[j] |= rnd(2) << i;
    }
  }

  last = pool;
  Node* rt = build(0, n, mask);

  int q;
  cin >> q;
  // q = 3e5;
  // int ret = 0;
  while (q--) {
    int L, R;
    cin >> L >> R;
    // L = rnd(n) + 1; R = rnd(n) + 1;
    // if (L > R) swap(L, R);
    --L;
    auto s = query(rt, 0, n, L, R);
    // ret += s.cnt;
    cout << s.cnt << '\n';
  }
  // cout << ret << '\n';

  return 0;
}

