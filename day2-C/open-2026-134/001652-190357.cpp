#include <bits/stdc++.h>

#define fi first
#define se second
#define pb push_back
#define ppb pop_back
#define pw(x) ((1LL)<<(x))
#define sz(x) (ll)x.size()
#define all(x) x.begin(), x.end()

using ll = long long;
using ld = long double;

using namespace std;

const ll N = 5e5 + 52;
const ll INF = 1e18;
const ll MOD = 998244353;

struct F{
    ll dop, l, r;
};

ll n, m;
ll i, j;
string s;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif // LOCAL
    ll q;
    cin >> n >> q;
    vector<pair<ll,ll>> p, pp;
    vector<F> ppp;
    for (i=0;i<n;i++){
        ll l, r;
        cin >> l >> r;
        p.pb({l,0});
        p.pb({r,1});
    }
    sort(all(p));
    ll ans=0, mx=0;
    vector<ll> lp;
    ll kk=0;
    for (auto [x,k] : p){
        if (!k) kk++, ans++, lp.pb(x);
        else ans--, lp.ppb();
        if (!k){
            ll l = kk-ans, r = n-kk;
            mx=max(mx,ans);
//            cout << ans << endl;
            ll mn = min(l,r);
            pp.pb({ans,ans+mn*2});
//            pp.pb({ans+mn*2,ans});
//            ppp.pb({ans+mn*2,0});
            ppp.pb({mn,ans+mn*2,ans+mn*2+(r-l)});
//            cout << x << " " << ans << " " << ans+mn*2 << endl;
//            cout << x << " " << ans+mn*2 << " " << ans+mn*2+(r-l) << endl;
//            cout << x << " " << l << " " << r << endl;
        }
        mx=max(mx,ans);
    }
    while(q--){
        ll x;
        cin >> x;
        ll res=INF;
        for (auto [l,r] : pp){
            if (l<=x && r>=x){
//                cout << l << " " << r << " " << (x-l+1)/2 << endl;
                res=min(res,(x-l+1)/2);
            }
        }
        for (auto [dop,l,r] : ppp){
            if (l<=x && r>=x){
                res=min(res,(x-l)+dop);
            }
        }
        cout << res << endl;
    }
//    sort(all(pp));
//    vector<ll> qq(q);
//    for (i=0;i<q;i++){
//        cin >> qq[i];
//    }
//    sort(all(qq));
//    set<ll> b;
//    for (auto [x,k] : pp){
//        ll pos = upper_bound()
//        if (!k){
//            b.insert(x);
//        }else b.erase(k);
//    }
    return 0;
}
