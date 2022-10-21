// url:https://codeforces.com/contest/1519/problem/E
// time:2021-11-01 16:55:05
// name:E-OffbyOne

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

array<int64, 2> norm(int64 x, int64 y) {
  int64 g = gcd(x, y);
  return {x / g, y / g};
}

const int N = 4e5 + 10;
vector<ii> a[N];
int used[N];

void add_edge(int u, int v, int k) {
  a[u].push_back({v, k});
  a[v].push_back({u, k});
}

vector<ii> ans;

int dfs(int u) {
  int ret = -1;
  used[u] = 1;
  for (auto& [v, k] : a[u]) {
    if (used[v] == 1) continue;
    int up = k;
    if (!used[v]) {
      int t = dfs(v);
      if (t != -1) {
        ans.push_back({t, up});
        up = -1;
      }
    }
    if (up != -1) {
      if (ret != -1) {
        ans.push_back({ret, up});
        ret = -1;
      } else {
        ret = up;
      }
    }
  }
  used[u] = 2;
  return ret;
}

int main() {
  int n;
  cin >> n;
  map<array<int64, 2>, int> p;
  for (int i = 0; i < n; ++i) {
    int64 a, b, c, d;
    cin >> a >> b >> c >> d;
    array<int64, 2> x = norm((c + d) * b, d * a);
    array<int64, 2> y = norm(b * c, d * (a + b));
    if (!p.count(x)) p[x] = SZ(p);
    if (!p.count(y)) p[y] = SZ(p);
    int u = p[x], v = p[y];
    add_edge(u, v, i);
  }
  for (int i = 0; i < SZ(p); ++i) {
    if (!used[i]) dfs(i);
  }

  cout << SZ(ans) << '\n';
  for (auto& [x, y] : ans) {
    cout << x + 1 << " " << y + 1 << '\n';
  }
  return 0;
}

