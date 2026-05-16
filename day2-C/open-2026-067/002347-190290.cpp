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
    for (auto x:p) {
        while (li<n&&l1[li]<=x)
            li++;
        while (ri+1<n&&r1[ri+1]<x)
            ri++;
        ll lk=n-li;
        ll rk=ri+1;
        ll k0=n-lk-rk;
        ll op=0;
        while (k0<=n) {
            an[k0]=min(an[k0],op);
            op++;
            if (k0==n)
                break;
            if (lk&&rk) {
                an[k0+1]=min(an[k0+1],op);
                lk--;
                rk--;
                k0+=2;
            }else {
                if (lk)
                    lk--;
                else
                    rk--;
                k0++;
            }
        }
    }
    while (q--) {
        ll x;cin>>x;
        cout<<an[x]<<' ';
    }
}