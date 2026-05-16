#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using ll = long long;
using namespace std;
using namespace __gnu_pbds;
template<class  T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class  T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
struct SegTree {
    vector<ll> t, add, a;
    ll sz;
    SegTree(vector<ll> v) {
        sz = v.size();
        a = v;
        t.resize(4*sz);
        add.resize(4*sz);
        build(1, 0, sz);
    }
    void build(ll v, ll tl, ll tr) {
        if (tl+1==tr) {
            t[v]=a[tl];
        }
        else {
            ll tm = (tl+tr)/2;
            build(2*v, tl, tm);
            build(2*v+1, tm, tr);
            t[v]=t[2*v]+t[2*v+1];
        }
    }
    void push(ll v, ll tl, ll tr) {
        t[v]+=add[v]*(tr-tl);
        if (tl+1!=tr) {
            add[2*v]+=add[v];
            add[2*v+1]+=add[v];
        }
        add[v]=0;
    }
    ll get(ll l, ll r) {
        return _get(1, 0, sz, l, r);
    }
    ll _get(ll v, ll tl, ll tr, ll l, ll r) {
        push(v, tl, tr);
        if (tl==l&&tr==r)return t[v];
        ll tm = (tr+tl)/2;
        if (r<=tm)return _get(2*v, tl, tm, l, r);
        if (l>=tm)return _get(2*v+1, tm, tr, l, r);
        return _get(2*v, tl, tm, l, tm)+_get(2*v+1, tm, tr, tm, r);
    }
    void update(ll l, ll r, ll val) {
        _update(1, 0, sz, l, r, val);
    }
    void _update(ll v, ll tl, ll tr, ll l, ll r, ll val) {
        push(v, tl, tr);
        if (l<=tl&&tr<=r) {
            add[v]+=val;
            push(v, tl, tr);
            return;
        }
        if (l>=tr||tl>=r)return;
        ll tm = (tl+tr)/2;
        _update(2*v, tl, tm, l, r, val);
        _update(2*v+1, tm, tr, l, r, val);
        t[v]=t[2*v]+t[2*v+1];
    }
};
template<typename T, typename U>
istream &operator>>(istream &in, pair<T, U> &p) {
    in>>p.first>>p.second;
    return in;
}
template<typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> p) {
    out<<p.first<<" "<<p.second<<"\n";
    return out;
}
template<typename T>
istream &operator>>(istream &in, vector<T> &v) {
    for (int i = 0; i<v.size(); i++)in>>v[i];
    return in;
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> v) {
    for (auto &x: v)out<<x<<" ";
    return out;
}

vector<ll> prefix_func(string s) {
    ll n = s.size();
    vector<ll> prefix(n);
    prefix[0]=0;
    for (int i = 1; i<n; i++) {
        ll j = prefix[i-1];
        while (j>0&&s[i]!=s[j]) {
            j = prefix[j-1];
        }
        if (s[i]==s[j])j++;
        prefix[i]=j;
    }
    return prefix;
}
vector<ll> z_func(string s) {
    ll n = s.size();
    vector<ll> z(n, 0);
    ll l = 0, r = -1;
    for (int i = 1; i<n; i++) {
        z[i]=min(max(r-i+1, 0ll), z[i-l]);
        while (i+z[i]<n&&s[i+z[i]]==s[z[i]])z[i]++;
        if (i+z[i]-1>r) {
            l = i;
            r = i+z[i]-1;
        }
    }
    z[0]=n;
    return z;
}
struct st {
    ll d, mn, mx;
};
void solve() {
    ll q, n;
    cin>>n>>q;
    vector<pair<ll, ll>> v(n);
    cin>>v;
    set<ll> crd;
    for (int i = 0; i<n; i++) {
        crd.insert(v[i].first);
        crd.insert(v[i].second);
    }
    map<ll, ll> mp;
    ll cur = 0;
    for (auto x: crd) {
        mp[x]=cur++;
    }
    for (int i = 0; i<n; i++) {
        v[i].first=mp[v[i].first];
        v[i].second = mp[v[i].second];
    }
    ll cnt1 = 0, cnt2 = n, d = 0;
    vector<st> v1;
    vector<ll> is(2*n);
    for (int i = 0; i<n; i++) {
        is[v[i].first]=1;
    }
    for (int i = 0; i<2*n-1; i++) {
        if (is[i]==0) {
            d--;
            cnt1++;
        }
        else {
            cnt2--;
            d++;
        }
        v1.push_back({d, min(cnt2, cnt1), max(cnt2, cnt1)});
    }
    for (ll i = 0; i<q; i++) {
        ll k;
        cin>>k;
        ll ans = 2*n;
        cout<<(k-1)/2<<"\n";
        // for (int i = 0; i<v1.size(); i++) {
        //     if (v1[i].d>=k) {
        //         ans = 0;
        //     }
        //     else {
        //        if (v1[i].d+2*v1[i].mn>=k) {
        //            ans = min(ans, (k-v1[i].d+1)/2);
        //        }
        //         else {
        //             if (min((ll)i+1, (ll)2*n-i-1)>=k) {
        //                 ans = min(ans, v1[i].mn+k-v1[i].d-2*v1[i].mn);
        //             }
        //         }
        //     }
        // }
        // cout<<ans<<"\n";
    }
}
signed main() {
#ifdef home
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#endif
    ll t=1;
    //cin>>t;
    while (t--)solve();
}