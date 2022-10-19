// url:https://codeforces.com/contest/1677/problem/F
// time:2022-05-08 20:23:37
// name:F-TokitsukazeandGems

#include <bits/stdc++.h>
#define ll long long
const int mod=998244353,N=262145+10;

// just interpolation
namespace ns {
    using namespace std;
    int a[N],b[N],c[N],d[N],e[N],g[N],f2[N],rev[N],p[N],ans[N],qq[N],lim;
    unsigned ll s[N];
    inline int qpow(int x,int y){
        int res=1;
        while(y){
            if(y&1) res=1ll*res*x%mod;
            x=1ll*x*x%mod;
            y>>=1;
        }
        return res;
    }
    inline void init(int mxn){
        int l=0;
        lim=1;
        while(lim<mxn)
            lim<<=1,l++;
        for(int i=1;i<lim;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
        int xx=qpow(3,mod>>l);
        p[lim>>1]=1;
        for(int i=lim/2+1;i<lim;i++)
            p[i]=1ll*p[i-1]*xx%mod;
        for(int i=lim/2-1;i>0;i--)
            p[i]=p[i<<1];
    }
    inline int getL(int mxn){
        return 1<<32-__builtin_clz(mxn);
    }
    inline void DFT(int *a,int len){
        int x=__builtin_ctz(lim/len);
        for(int i=0;i<len;i++)
            s[i]=a[rev[i]>>x];
        for(int i=1;i!=len;i<<=1){
            int dg=i<<1;
            for(int j=0;j!=len;j+=dg){
                for(int k=0;k<i;k++){
                    int t1=s[i|j|k]*p[i|k]%mod;
                    s[i|j|k]=s[j|k]+mod-t1;
                    s[j|k]+=t1;
                }
            }
        }
        for(int i=0;i<len;i++)
            a[i]=s[i]%mod;
    }
    inline void IDFT(int *a,int len){
        reverse(a+1,a+len);
        DFT(a,len);
        for(int i=0;i<len;i++)
            a[i]=1ll*a[i]*(mod-mod/len)%mod;
    }
    inline void Inv(int n,int *a,int *b){
        qq[0]=qpow(a[0],mod-2);
        memset(c,0,sizeof(c));
        memset(d,0,sizeof(d));
        for(int dg=1;dg<n;dg<<=1){
            for(int i=0;i<(dg<<1)&&i<n;i++)
                c[i]=a[i];
            for(int i=0;i<dg;i++)
                d[i]=qq[i];
            DFT(c,dg<<1),DFT(d,dg<<1);
            for(int i=0;i<(dg<<1);i++)
                c[i]=1ll*c[i]*d[i]%mod;
            IDFT(c,dg<<1);
            for(int i=0;i<dg;i++)
                c[i]=0;
            DFT(c,dg<<1);
            for(int i=0;i<(dg<<1);i++)
                c[i]=1ll*c[i]*d[i]%mod;
            IDFT(c,dg<<1);
            for(int i=dg;i<(dg<<1);i++)
                qq[i]=1ll*c[i]*(mod-1)%mod;
        }
        for(int i=0;i<n;i++)
            b[i]=qq[i];
    }
    inline void mul(int *a,int *b,int *s,int n,int m){
        int len=getL(n+m-1);
        static int c[N],d[N],e[N];
        memset(c,0,len<<2);
        memset(d,0,len<<2);
        for(int i=0;i<n;i++)
            c[i]=a[i];
        for(int i=0;i<m;i++)
            d[i]=b[i];
        DFT(c,len),DFT(d,len);
        for(int i=0;i<len;i++)
            c[i]=1ll*c[i]*d[i]%mod;
        IDFT(c,len);
        for(int i=0;i<n+m-1;i++)
            s[i]=c[i];
    }
    inline void mul2(int *a,int *b,int *s,int n,int m){
        int len=getL(n);
        static int c[N],d[N],e[N];
        memset(c,0,len<<2);
        memset(d,0,len<<2);
        for(int i=0;i<n;i++)
            c[i]=a[i];
        for(int i=0;i<m;i++)
            d[i]=b[m-i-1];
        DFT(c,len),DFT(d,len);
        for(int i=0;i<len;i++)
            e[i]=1ll*c[i]*d[i]%mod;
        IDFT(e,len);
        for(int i=0;i<n-m+1;i++)
            s[i]=e[m-1+i];
    }
    inline void Der(int *a,int *b,int n){
        for(int i=1;i<n;i++)
            b[i-1]=1ll*i*a[i]%mod;
        b[n-1]=0;
    }
    int n,m,f[N],q[N],*t[N],*t2[N],buf[N<<5],*now=buf,sz[N],x[N],y[N];
    inline void build(int l,int r,int rt){
        t[rt]=now,now+=r-l+2,t2[rt]=now,now+=r-l+2;
        if(l==r){
            t[rt][0]=1;
            t[rt][1]=x[l]?mod-x[l]:0;
            return ;
        }
        int mid=l+r>>1,ls=rt<<1,rs=rt<<1|1;
        build(l,mid,ls),build(mid+1,r,rs);
        mul(t[ls],t[rs],t[rt],mid-l+2,r-mid+1);
    }
    inline void solve(int l,int r,int rt,int *a){
        if(l==r){
            a[l]=t2[rt][0];
            return ;
        }
        int mid=l+r>>1,ls=rt<<1,rs=rt<<1|1;
        mul2(t2[rt],t[rs],t2[ls],r-l+1,r-mid+1);
        solve(l,mid,ls,a);
        mul2(t2[rt],t[ls],t2[rs],r-l+1,mid-l+2);
        solve(mid+1,r,rs,a);
    }
    int tmp1[N],tmp2[N],tmp3[N],tmp4[N],answ[N],*stein[N];
    inline void interpolation(int rt,int l,int r){
        stein[rt]=new int[r-l+1];
        if(l==r){
            stein[rt][0]=answ[l];
            return ;
        }
        int mid=l+r>>1;
        interpolation(rt<<1,l,mid),interpolation(rt<<1|1,mid+1,r);
        int len=getL(r-l+1);
        for(int i=0;i<mid-l+1;i++)
            tmp3[i]=stein[rt<<1][i];
        for(int i=0;i<r-mid;i++)
            tmp4[i]=stein[rt<<1|1][i];
        mul(t[rt<<1|1],tmp3,tmp3,r-mid+1,mid-l+1);
        mul(t[rt<<1],tmp4,tmp4,mid-l+1+1,r-mid);
        for(int i=0;i<=r-l;i++)
            stein[rt][i]=(tmp3[i]+tmp4[i])%mod;
    }
    inline void Interpolation(int *x,int *y,int *ans,int n){
        int len=getL(n);
        build(1,n,1);
        for(int i=0;i<=n;i++)
            tmp1[i]=t[1][i];
        reverse(tmp1,tmp1+n+1);
        Der(tmp1,tmp1,n+1);
        Inv(n+1,t[1],tmp2);
        mul2(tmp1,tmp2,t2[1],n*2-1,n);
        solve(1,n,1,answ);
        for(int i=1;i<=n;i++)
            answ[i]=1ll*y[i]*qpow(answ[i],mod-2)%mod;
        interpolation(1,1,n);
        for(int i=0;i<n;i++)
            ans[i]=stein[1][n-1-i];
    }
}
using i64 = long long;

constexpr int P = 998244353;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template<class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(P - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
};

std::vector<int> rev;
std::vector<Z> roots{0, 1};
void dft(std::vector<Z> &a) {
    int n = a.size();
    
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (rev[i] < i) {
            std::swap(a[i], a[rev[i]]);
        }
    }
    if (int(roots.size()) < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            Z e = power(Z(3), (P - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * e;
            }
            k++;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                Z u = a[i + j];
                Z v = a[i + j + k] * roots[k + j];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}
void idft(std::vector<Z> &a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
    Z inv = (1 - P) / n;
    for (int i = 0; i < n; i++) {
        a[i] *= inv;
    }
}
struct Poly {
    std::vector<Z> a;
    Poly() {}
    Poly(const std::vector<Z> &a) : a(a) {}
    Poly(const std::initializer_list<Z> &a) : a(a) {}
    int size() const {
        return a.size();
    }
    void resize(int n) {
        a.resize(n);
    }
    Z operator[](int idx) const {
        if (idx < size()) {
            return a[idx];
        } else {
            return 0;
        }
    }
    Z &operator[](int idx) {
        return a[idx];
    }
    Poly mulxk(int k) const {
        auto b = a;
        b.insert(b.begin(), k, 0);
        return Poly(b);
    }
    Poly modxk(int k) const {
        k = std::min(k, size());
        return Poly(std::vector<Z>(a.begin(), a.begin() + k));
    }
    Poly divxk(int k) const {
        if (size() <= k) {
            return Poly();
        }
        return Poly(std::vector<Z>(a.begin() + k, a.end()));
    }
    friend Poly operator+(const Poly &a, const Poly &b) {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] + b[i];
        }
        return Poly(res);
    }
    friend Poly operator-(const Poly &a, const Poly &b) {
        std::vector<Z> res(std::max(a.size(), b.size()));
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] - b[i];
        }
        return Poly(res);
    }
    friend Poly operator*(Poly a, Poly b) {
        if (a.size() == 0 || b.size() == 0) {
            return Poly();
        }
        int sz = 1, tot = a.size() + b.size() - 1;
        while (sz < tot) {
            sz *= 2;
        }
        a.a.resize(sz);
        b.a.resize(sz);
        dft(a.a);
        dft(b.a);
        for (int i = 0; i < sz; ++i) {
            a.a[i] = a[i] * b[i];
        }
        idft(a.a);
        a.resize(tot);
        return a;
    }
    friend Poly operator*(Z a, Poly b) {
        for (int i = 0; i < int(b.size()); i++) {
            b[i] *= a;
        }
        return b;
    }
    friend Poly operator*(Poly a, Z b) {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] *= b;
        }
        return a;
    }
    Poly &operator+=(Poly b) {
        return (*this) = (*this) + b;
    }
    Poly &operator-=(Poly b) {
        return (*this) = (*this) - b;
    }
    Poly &operator*=(Poly b) {
        return (*this) = (*this) * b;
    }
    Poly deriv() const {
        if (a.empty()) {
            return Poly();
        }
        std::vector<Z> res(size() - 1);
        for (int i = 0; i < size() - 1; ++i) {
            res[i] = (i + 1) * a[i + 1];
        }
        return Poly(res);
    }
    Poly integr() const {
        std::vector<Z> res(size() + 1);
        for (int i = 0; i < size(); ++i) {
            res[i + 1] = a[i] / (i + 1);
        }
        return Poly(res);
    }
    Poly inv(int m) const {
        Poly x{a[0].inv()};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{2} - modxk(k) * x)).modxk(k);
        }
        return x.modxk(m);
    }
    Poly log(int m) const {
        return (deriv() * inv(m)).integr().modxk(m);
    }
    Poly exp(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{1} - x.log(k) + modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }
    Poly pow(int k, int m) const {
        int i = 0;
        while (i < size() && a[i].val() == 0) {
            i++;
        }
        if (i == size() || 1LL * i * k >= m) {
            return Poly(std::vector<Z>(m));
        }
        Z v = a[i];
        auto f = divxk(i) * v.inv();
        return (f.log(m - i * k) * k).exp(m - i * k).mulxk(i * k) * power(v, k);
    }
    Poly sqrt(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((P + 1) / 2);
        }
        return x.modxk(m);
    }
    Poly mulT(Poly b) const {
        if (b.size() == 0) {
            return Poly();
        }
        int n = b.size();
        std::reverse(b.a.begin(), b.a.end());
        return ((*this) * b).divxk(n - 1);
    }
    std::vector<Z> eval(std::vector<Z> x) const {
        if (size() == 0) {
            return std::vector<Z>(x.size(), 0);
        }
        const int n = std::max(int(x.size()), size());
        std::vector<Poly> q(4 * n);
        std::vector<Z> ans(x.size());
        x.resize(n);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = Poly{1, -x[l]};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        std::function<void(int, int, int, const Poly &)> work = [&](int p, int l, int r, const Poly &num) {
            if (r - l == 1) {
                if (l < int(ans.size())) {
                    ans[l] = num[0];
                }
            } else {
                int m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};
int F[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k, p;
    std::cin >> n >> k >> p;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<Z> g(k + 2);
    for (int i = 1; i <= k + 1; i++) {
        g[i] = g[i - 1] + power(Z(p), i) * power(Z(i), k);
    }
    std::vector<Z> fac(k + 2), invfac(k + 2);
    fac[0] = 1;
    for (int i = 1; i <= k + 1; i++) {
        fac[i] = fac[i - 1] * i;
    }
    invfac[k + 1] = fac[k + 1].inv();
    for (int i = k + 1; i; i--) {
        invfac[i - 1] = invfac[i] * i;
    }
    for (int i = 0; i <= k + 1; i++) {
        g[i] /= power(Z(p), i);
    }
    
    Z C = 0;
    for (int i = 0; i <= k + 1; i++) {
        C += fac[k + 1] * invfac[i] * invfac[k + 1 - i] * (i % 2 == 0 ? 1 : -1) * g[i];
    }
    C /= power(Z(1 - Z(p).inv()), k + 1);
    
    for (int i = 0; i <= k + 1; i++) {
        g[i] -= C / power(Z(p), i);
    }
    
    ns::init(2 * (k + 1));
    for (int i = 0; i <= k; i++) {
        ns::x[i + 1] = i;
        ns::y[i + 1] = g[i].val();
    }
    ns::Interpolation(ns::x, ns::y, F, k + 1);
    
    auto f = Poly(std::vector<Z>(F, F + k + 1)).eval(std::vector<Z>(a.begin(), a.end()));
    for (int i = 0; i < n; i++) {
        f[i] = f[i] * power(Z(p), a[i]) + C;
    }
    
    std::vector<Z> l(n), r(n);
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            l[i] = 1;
        } else {
            l[i] = l[i - 1] * (a[i - 1] + 1) + 1;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1) {
            r[i] = 1;
        } else {
            r[i] = r[i + 1] * (a[i + 1] + 1) + 1;
        }
    }
    
    Z ans = 0;
    Z x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        ans += f[i] * l[i] * r[i];
        ans += (f[i] * x + a[i] * y) * r[i];
        x *= a[i] + 1;
        y *= a[i] + 1;
        x += Z(a[i]) * l[i];
        y += f[i] * l[i];
    }
    std::cout << ans.val() << "\n";
    
    return 0;
}
