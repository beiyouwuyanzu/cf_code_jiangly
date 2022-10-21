// url:https://codeforces.com/contest/1208/problem/E
// time:2022-03-16 15:53:13
// name:E-LetThemSlide

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

const int N = 1e6 + 10;
struct Node {
  Node *left, *right;
  int64 sum, delta;
  void update(int a, int b, int64 c) {
    sum += (b - a) * c;
    delta += c;
  }
  void pushup() {
    sum = left->sum + right->sum;
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
  ret->sum = ret->delta = 0;
  if (a + 1 == b) return ret;
  int mid = (a + b) / 2;
  ret->left = build(a, mid);
  ret->right = build(mid, b);
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
  if (ll >= rr || a >= rr || b <= ll) return 0LL;
  if (a >= ll && b <= rr) {
    return cur->sum;
  }
  cur->pushdown(a, b);
  int mid = (a + b) / 2;
  int64 ret = 0;
  ret += query(cur->left, a, mid, ll, rr);
  ret += query(cur->right, mid, b, ll, rr);
  return ret;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> L(n), R(n);
  vector<int> a;
  for (int i = 0; i < n; ++i) {
    int len;
    cin >> len;
    L[i] = SZ(a);
    for (int j = 0; j < len; ++j) {
      int x;
      cin >> x;
      a.push_back(x);
    }
    R[i] = SZ(a);
  }

  last = pool;
  Node* rt = build(0, m);

  vector<int64> ret(m);
  for (int i = 0; i < n; ++i) {
    trace(i);
    int len = R[i] - L[i];
    if (len * 2 <= m) {
      int mx = 0;
      for (int j = 0; j < len - 1; ++j) {
        ckmax(mx, a[L[i] + j]);
        insert(rt, 0, m, j, j + 1, mx);
      }
      mx = 0;
      for (int j = 0; j < len - 1; ++j) {
        ckmax(mx, a[R[i] - 1 - j]);
        insert(rt, 0, m, m - 1 - j, m - j, mx);
      }
      ckmax(mx, a[L[i]]);
      insert(rt, 0, m, len - 1, m - len + 1, mx);
    } else {
      multiset<int> A;
      int gap = m - len + 1;
      for (int j = 0; j < len; ++j) {
        A.insert(a[L[i] + j]);
        if (SZ(A) > gap) A.erase(A.find(a[L[i] + j - gap]));
        int x = *A.rbegin();
        if (j < gap - 1) ckmax(x, 0);
        trace(i, j, x);
        insert(rt, 0, m, j, j + 1, x);
      }
      A.clear();
      for (int j = 0; j < len; ++j) {
        if (m - j - 1 <= len - 1) break;
        A.insert(a[R[i] - 1 - j]);
        if (SZ(A) > gap) A.erase(A.find(a[R[i] - 1 - j + gap]));
        int x = *A.rbegin();
        if (j < gap - 1) ckmax(x, 0);
        trace(i, j, x);
        insert(rt, 0, m, m - j - 1, m - j, x);
      }
    }
  }
  for (int j = 0; j < m; ++j) ret[j] = query(rt, 0, m, j, j + 1);
  out(ret);

  return 0;
}

