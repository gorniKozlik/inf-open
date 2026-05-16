// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

// #pragma clang __attribute__(optimize("O3,unroll-loops"))
// #pragma clang __attribute__(target("avx2,bmi,bmi2,popcnt,lzcnt"))

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef __int128 lll;

const ll inf=1e18+1,mod=998244353;
const ld eps=1e-9,pi=acos(-1);
#define all(a) a.begin(), a.end()
#define mpp make_pair
#define F first
#define S second

mt19937_64 rng(234);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n,q;cin>>n>>q;
    vector<ll>l(n),r(n),p;
    for (ll i=0;i<n;i++) {
        cin>>l[i]>>r[i];
        p.push_back(l[i]);
        p.push_back(r[i]);
    }
    auto l1=l,r1=r;
    sort(all(l1));
    sort(all(r1));
    sort(all(p));
    ll li=0,ri=-1;
    vector<ll>an(n+1,inf);
    vector<vector<ll>>op2(n+2),op1(n+2);
    vector<ll>x0,p0,y0;
    ll itt=0;
    for (auto x:p) {
        itt++;
        while (li<n&&l1[li]<=x)
            li++;
        while (ri+1<n&&r1[ri+1]<x)
            ri++;
        ll lk=n-li;
        ll rk=ri+1;
        ll k0=n-lk-rk;
        ll op=0;
        ll k2=min(lk,rk);
        ll k1=lk+rk-2*k2;
        op2[k0].push_back(-itt);
        ll y0=k0+k2*2+1;
        op2[y0].push_back(itt);
        op1[y0].push_back(itt);
        x0.push_back(k0);
        p0.push_back((k2+1)-y0);
    }
    multiset<ll>bs2;
    ll bs1=inf;
    for (ll i=0;i<=n;i++) {
        sort(all(op2[i]));
        for (auto o2:op2[i])
            if (o2<0) {
                ll id=(-o2)-1;
                bs2.insert(-(x0[id]-1));
            }else {
                ll id=o2-1;
                bs2.erase(bs2.find(-(x0[id]-1)));
            }
        for (auto o1:op1[i])
            bs1=min(bs1,p0[o1-1]);
        an[i]=i+bs1;
        if (!bs2.empty()) {
            auto x=*(bs2.begin());
            x=-x;
            an[i]=min(an[i],(i-x)/2);
        }
    }
    for (ll i=n-1;i>=0;i--)
        an[i]=min(an[i],an[i+1]);
    while (q--) {
        ll x;cin>>x;
        cout<<an[x]<<' ';
    }
}