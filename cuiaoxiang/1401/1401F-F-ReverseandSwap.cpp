// url:https://codeforces.com/contest/1401/problem/F
// time:2022-03-13 05:04:42
// name:F-ReverseandSwap

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
template<size_t N> int find_first(const bitset<N>& x) {
#ifdef LOCAL
  int k; for (k = 0; k < N && !x[k]; ++k);
  return k;
#else
  return x._Find_first();
#endif
}

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

const int K = 18;
const int N = 1 << K;
bool flag_rev[K], flag_swap[K];

struct Node {
  Node *left, *right;
  int64 sum;
  void pushup() {
    sum = left->sum + right->sum;
  }
};
Node pool[N << 1], *last;
Node* build(int a, int b, const vector<int>& v) {
  Node* ret = last++;
  if (a + 1 == b) {
    ret->sum = v[a];
    return ret;
  }
  int mid = (a + b) / 2;
  ret->left = build(a, mid, v);
  ret->right = build(mid, b, v);
  ret->pushup();
  return ret;
}
void insert(Node* cur, int a, int b, int pos, int val) {
  if (pos < a || pos >= b) return;
  if (a + 1 == b) {
    cur->sum = val;
    return;
  }
  int k = lg2(b - a) - 1;
  if (flag_rev[k]) pos = a + b - 1 - pos;
  if (flag_swap[k]) pos ^= 1 << k;
  int mid = (a + b) / 2;
  insert(cur->left, a, mid, pos, val);
  insert(cur->right, mid, b, pos, val);
  cur->pushup();
}
int64 query(Node* cur, int a, int b, int ll, int rr) {
  if (ll >= rr) return 0;
  if (ll == a && rr == b) {
    return cur->sum;
  }
  int k = lg2(b - a) - 1;
  trace("before rev", a, b, ll, rr);
  if (flag_rev[k]) {
    int nll = a + (b - rr);
    int nrr = b - (ll - a);
    ll = nll;
    rr = nrr;
  }
  trace("after rev", a, b, ll, rr);
  int mid = (a + b) / 2;
  int64 ret = 0;
  if (flag_swap[k]) {
    trace("left part: ", mid, b, ll - a + mid, min(b, rr));
    ret += query(cur->right, mid, b, ll - a + mid, min(b, rr - a + mid));
    trace(ret);
    trace("right part: ", a, mid, max(a, ll), mid - (b - rr));
    ret += query(cur->left, a, mid, max(a, mid - (b - ll)), mid - (b - rr));
    trace(ret);
  } else {
    ret += query(cur->left, a, mid, ll, min(mid, rr));
    ret += query(cur->right, mid, b, max(mid, ll), rr);
  }
  return ret;
}

int main() {
  int n, q;
  cin >> n >> q;

  vector<int> v(1 << n);
  for (int i = 0; i < (1 << n); ++i) cin >> v[i];

  last = pool;
  Node* rt = build(0, 1 << n, v);
  trace("init");
  {
  int64 ret = query(rt, 0, 1 << n, 0, 1 << n);
  trace(ret);
  }

  while (q--) {
    int op, pos, val, k;
    cin >> op;
    trace(op);
    if (op == 1) {
      cin >> pos >> val;
      --pos;
      insert(rt, 0, 1 << n, pos, val);
      int64 ret = query(rt, 0, 1 << n, 0, 1 << n);
      trace(ret);
    } else if (op == 2) {
      cin >> k;
      if (k == 0) continue;
      flag_rev[k - 1] ^= 1;
    } else if (op == 3) {
      cin >> k;
      flag_swap[k] ^= 1;
    } else {
      int L, R;
      cin >> L >> R;
      --L;
      int64 ret = query(rt, 0, 1 << n, L, R);
      cout << ret << '\n';
    }
  }
  return 0;
}

