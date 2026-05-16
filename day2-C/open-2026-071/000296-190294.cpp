#pragma GCC optimize("O3","unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;
random_device rd;
mt19937 gen(rd());
#define fora(n) for(int a=0;a<n;++a)
#define forb(n) for(int b=0;b<n;++b)
#define forc(n) for(int c=0;c<n;++c)
#define ford(n) for(int d=0;d<n;++d)
#define fore(n) for(int e=0;e<n;++e)
#define forf(n) for(int f=0;f<n;++f)
#define forg(n) for(int g=0;g<n;++g)
#define forh(n) for(int h=0;h<n;++h)
#define fori(n) for(int i=0;i<n;++i)
#define forj(n) for(int j=0;j<n;++j)
#define fork(n) for(int k=0;k<n;++k)
#define forl(n) for(int l=0;l<n;++l)
#define form(n) for(int m=0;m<n;++m)
#define forn(n) for(int n=0;n<n;++n)
#define foro(n) for(int o=0;o<n;++o)
#define forp(n) for(int p=0;p<n;++p)
#define forq(n) for(int q=0;q<n;++q)
#define forr(n) for(int r=0;r<n;++r)
#define fors(n) for(int s=0;s<n;++s)
#define fort(n) for(int t=0;t<n;++t)
#define foru(n) for(int u=0;u<n;++u)
#define forv(n) for(int v=0;v<n;++v)
#define forw(n) for(int w=0;w<n;++w)
#define forx(n) for(int x=0;x<n;++x)
#define fory(n) for(int y=0;y<n;++y)
#define forz(n) for(int z=0;z<n;++z)
#define foras(n) for(int a=n-1;a>=0;--a)
#define forbs(n) for(int b=n-1;b>=0;--b)
#define forcs(n) for(int c=n-1;c>=0;--c)
#define fords(n) for(int d=n-1;d>=0;--d)
#define fores(n) for(int e=n-1;e>=0;--e)
#define forfs(n) for(int f=n-1;f>=0;--f)
#define forgs(n) for(int g=n-1;g>=0;--g)
#define forhs(n) for(int h=n-1;h>=0;--h)
#define foris(n) for(int i=n-1;i>=0;--i)
#define forjs(n) for(int j=n-1;j>=0;--j)
#define forks(n) for(int k=n-1;k>=0;--k)
#define forls(n) for(int l=n-1;l>=0;--l)
#define forms(n) for(int m=n-1;m>=0;--m)
#define forns(n) for(int n=n-1;n>=0;--n)
#define foros(n) for(int o=n-1;o>=0;--o)
#define forps(n) for(int p=n-1;p>=0;--p)
#define forqs(n) for(int q=n-1;q>=0;--q)
#define forrs(n) for(int r=n-1;r>=0;--r)
#define forss(n) for(int s=n-1;s>=0;--s)
#define forts(n) for(int t=n-1;t>=0;--t)
#define forus(n) for(int u=n-1;u>=0;--u)
#define forvs(n) for(int v=n-1;v>=0;--v)
#define forws(n) for(int w=n-1;w>=0;--w)
#define forxs(n) for(int x=n-1;x>=0;--x)
#define forys(n) for(int y=n-1;y>=0;--y)
#define forzs(n) for(int z=n-1;z>=0;--z)
#define forlr(l,r) for(int i=l;i<=r;++i)
#define forlrj(l,r) for(int j=l;j<=r;++j)
#define forlrk(l,r) for(int k=l;k<=r;++k)
#define forlrc(l,r) for(int c=l;c<=r;++c)
#define forlrs(l,r) for(int i=r;i>=l;--i)
#define forlrjs(l,r) for(int j=r;j>=l;--j)
#define forlrks(l,r) for(int k=r;k<=l;--k)
#define forlrcs(l,r) for(int c=r;c>=l;--c)
#define vec vector
#define ns cout<<"\n";
#define ret return
#define fst first
#define sec second
#define all(x) x.begin(),x.end()
#define uniq(x); sort(all(x));x.resize(unique(all(x))-x.begin());
#define pb push_back
#define int ll
#define resz resize
const int INF = 998244353, SINF = 1e18;
const int N = 1e6;
int n, q;
vec<vec<int> > a;
vec<int> inv;
int F() {
    int res = 0;
    vec<int> mx(2 * n);
    int x = 0;
    fori(2*n) {
        if (i < inv[i]) {
            res = max(res, x + 1);
            mx[inv[i]] = x + 1;
        }
        x = max(x, mx[i]);
    }
    ret res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> q;
    inv.resz(2 * n);
    vec<int> o;
    fori(n) {
        int l, r;
        cin >> l >> r;
        a.pb({l, r});
        o.pb(l);
        o.pb(r);
    }
    uniq(o);
    for (auto &i: a) {
         i[0] = lower_bound(all(o), i[0]) - o.begin();
        i[1] = lower_bound(all(o), i[1]) - o.begin();
         inv[i[0]] = i[1];
        inv[i[1]] = i[0];
    }
    vec<vec<int>>s;
    fori(2*n) {
        if (i<inv[i]) {
            s.pb({i,0});
            s.pb({inv[i],1});
        }
    }
    sort(all(s));
    vec<int>dp(n+1,INF);
    int w=0,cst=0;
    for (auto i:s) {
         int h=w;
        int L=cst*2,R=n*2-w*2-cst*2;
        int Mx=min(L,R);
         forlr(0,h+Mx) {
            dp[i]=min(dp[i],max(0ll,(i-h+1)/2));
        }
        if (i[1]==1) {
            w--;
            cst++;
        }
        else {
            w++;
        }
    }

    while (q--) {
        int x;
        cin>>x;
        cout<<dp[x]<<' ';
    }

}