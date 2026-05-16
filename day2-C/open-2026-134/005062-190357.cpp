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

ll t[4*N];
ll tt[4*N];

void update(ll v, ll tl, ll tr, ll pos, ll val){
    if (tr-tl==1){
//        cout << "pos=" << tl << " " << pos << endl;
        t[v] = val;
        return;
    }
    ll tm = (tl+tr)/2;
    if (pos<tm){
        update(v*2+1,tl,tm,pos,val);
    }else update(v*2+2,tm,tr,pos,val);
    t[v] = max(t[v*2+1],t[v*2+2]);
}

ll get(ll v, ll tl, ll tr, ll l, ll r){
    if (tl>=r || tr<=l){
        return -INF;
    }
    if (tl>=l && tr<=r){
//        cout << t[v] << endl;
        return t[v];
    }
    ll tm = (tl+tr)/2;
    return max(get(v*2+1,tl,tm,l,r),get(v*2+2,tm,tr,l,r));
}

void update2(ll v, ll tl, ll tr, ll pos, ll val){
    if (tr-tl==1){
//        cout << "pos=" << tl << " " << pos << endl;
        tt[v] = val;
        return;
    }
    ll tm = (tl+tr)/2;
    if (pos<tm){
        update2(v*2+1,tl,tm,pos,val);
    }else update2(v*2+2,tm,tr,pos,val);
    tt[v] = max(tt[v*2+1],tt[v*2+2]);
}

ll get2(ll v, ll tl, ll tr, ll l, ll r){
    if (tl>=r || tr<=l){
        return -INF;
    }
    if (tl>=l && tr<=r){
//        cout << t[v] << endl;
        return tt[v];
    }
    ll tm = (tl+tr)/2;
    return max(get2(v*2+1,tl,tm,l,r),get2(v*2+2,tm,tr,l,r));
}

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
    vector<pair<ll,ll>> p, pp, ppp;
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
            pp.pb({ans+mn*2,ans});
//            pp.pb({ans+mn*2,ans});
//            ppp.pb({ans+mn*2,0});
//            ppp.pb({mn,ans+mn*2,ans+mn*2+abs(r-l)});
            ppp.pb({ans+mn*2,(ans+mn*2-mn)});
//            cout << x << " " << ans << " " << ans+mn*2 << endl;
//            cout << x << " " << ans+mn*2 << " " << ans+mn*2+(r-l) << endl;
//            cout << x << " " << l << " " << r << endl;
        }
        mx=max(mx,ans);
    }
    sort(all(pp));
    for (i=0;i<sz(pp);i++){
        update(0,0,sz(pp),i,pp[i].se);
//        cout << pp[i].se << endl;
    }
    sort(all(ppp));
    for (i=0;i<sz(ppp);i++){
        update2(0,0,sz(ppp),i,ppp[i].se);
//        cout << pp[i].se << endl;
    }
//    cout << get(0,0,sz(pp),0,sz(pp)) << endl;
    while(q--){
        ll x;
        cin >> x;
        if (x<=mx){
            cout << 0 << endl;
            continue;
        }
        ll res=INF;
        pair<ll,ll> fnd = {x-1,INF};
        ll pos = upper_bound(all(pp),fnd)-pp.begin();
//        for (i=pos;i<n;i++){
        res=min(res,(x-get(0,0,sz(pp),pos,sz(pp))+1)/2);
        pos = upper_bound(all(ppp),fnd)-ppp.begin();
//        for (i=0;i<sz(ppp);i++){
//            if (ppp[i].fi<=x){
////                cout << x << " " << ppp[i].fi << " " << ppp[i].se << endl;
//                res=min(res,x-ppp[i].se);
//            }
//        }
        res=min(res,(x-get2(0,0,sz(ppp),0,pos)));
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
