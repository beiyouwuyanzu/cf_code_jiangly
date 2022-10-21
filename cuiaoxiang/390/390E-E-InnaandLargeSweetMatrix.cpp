// url:https://codeforces.com/contest/390/problem/E
// time:2021-11-14 17:28:43
// name:E-InnaandLargeSweetMatrix

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

typedef long long int64;
typedef pair<int, int> ii;
#define SZ(x) (int)((x).size())
template <typename T> static constexpr T inf = numeric_limits<T>::max() / 2;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;
mt19937 mrand(random_device{}());
int rnd(int x) { return mrand() % x; }
// mt19937_64 mrand(random_device{}());
// int64 rnd(int64 x) { return mrand() % x; }
template <class T> void out(const vector<T>& a) { for (int i = 0; i < SZ(a); ++i) cout << a[i] << " \n"[i + 1 == SZ(a)]; }
template <class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> void dedup(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
void add(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

template<typename T, size_t N>
struct fenwick {
  T c[N];
  fenwick() {
    fill(c + 1, c + N, 0);
  }
  void add(int x, T y) {
    for (; x < N; x += x & -x) {
      c[x] += y;
    }
  }
  T query(int x) {
    T ret = 0;
    for (; x; x -= x & -x) {
      ret += c[x];
    }
    return ret;
  }
};

int main() {
  int n, m, q;
  cin >> n >> m >> q;
  struct Query {
    int op;
    int x1, y1, x2, y2, v;
  };
  const int N = 4e6 + 10;
  fenwick<int64, N> X0, X1, Y0, Y1;
  int64 sum = 0;
  for (int i = 0; i < q; ++i) {
    int64 op, x1, y1, x2, y2, v = 0;
    cin >> op;
    if (op == 0) {
      cin >> x1 >> y1 >> x2 >> y2 >> v;
      ++x2; ++y2;
      int64 vx = v * (y2 - y1);
      X0.add(x1, vx);
      X0.add(x2, -vx);
      X1.add(x1, vx * x1);
      X1.add(x2, -vx * x2);

      int64 vy = v * (x2 - x1);
      Y0.add(y1, vy);
      Y0.add(y2, -vy);
      Y1.add(y1, vy * y1);
      Y1.add(y2, -vy * y2);

      sum += (y2 - y1) * (x2 - x1) * v;
    } else {
      cin >> x1 >> y1 >> x2 >> y2;
      --x1; --y1;
      int64 retX = X0.query(x2) * (x2 + 1) - X1.query(x2);
      retX -= X0.query(x1) * (x1 + 1) - X1.query(x1);
      int64 retY = Y0.query(y2) * (y2 + 1) - Y1.query(y2);
      retY -= Y0.query(y1) * (y1 + 1) - Y1.query(y1);
      int64 ret = retX + retY - sum;
      cout << ret << '\n';
    }
  }

  return 0;
}

