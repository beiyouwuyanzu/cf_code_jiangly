// url:https://codeforces.com/contest/1370/problem/F2
// time:2021-11-15 15:44:06
// name:F2-TheHiddenPair(HardVersion)

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

const int N = 1e3 + 10;
vector<int> a[N];

array<int, 2> query(const vector<int>& c) {
  cout << "? " << SZ(c);
  for (auto& x : c) {
    cout << " " << x + 1;
  }
  cout << endl;
  array<int, 2> ret;
  cin >> ret[0] >> ret[1];
  return ret;
}

vector<int> BFS(int s, int n) {
  vector<int> d(n, -1);
  d[s] = 0;
  queue<int> Q;
  Q.push(s);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (auto& v : a[u]) {
      if (d[v] >= 0) continue;
      d[v] = d[u] + 1;
      Q.push(v);
    }
  }
  return d;
}

int main() {
  int cas;
  cin >> cas;
  while (cas--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) a[i].clear();
    for (int i = 0; i < n - 1; ++i) {
      int x, y;
      cin >> x >> y;
      --x; --y;
      a[x].push_back(y);
      a[y].push_back(x);
    }
    auto g = vect<int>(0, n, n);
    for (int i = 0; i < n; ++i) {
      g[i] = BFS(i, n);
    }
    vector<int> cur(n);
    iota(cur.begin(), cur.end(), 0);
    auto ret = query(cur);
    int u = ret[0] - 1, v = u, D = ret[1];

    while (true) {
      if (g[u][v] == D) break;
      int gap = D - g[u][v];
      cur.clear();
      for (int i = 0; i < n; ++i) {
        if (max(g[i][u], g[i][v]) >= g[u][v] + (gap + 1) / 2) cur.push_back(i);
      }
      ret = query(cur);
      int w = ret[0] - 1;
      if (g[w][v] >= g[u][v] + (gap + 1) / 2) {
        u = w;
      } else {
        v = w;
      }
    }
    cout << "! " << u + 1 << " " << v + 1 << endl;
    string verify;
    cin >> verify;
    if (verify == "Incorrect") return 0;
  }
  return 0;
}

