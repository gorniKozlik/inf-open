#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

struct Node {
    ll max;
    ll add = 0;
};

class SegTree {
 private:
    ll sz;
    vector<Node> t;
 public:
    SegTree(const vector<ll>& data) {
        sz = data.size();
        t.resize(4*sz);
        build(1, 0, sz, data);
    }

    Node merge(const Node& a, const Node& b) {
        Node res;
        res.max = max(a.max, b.max);
        return res;
    }

    void build(ll v, ll l, ll r, const vector<ll>& data) {
        if (l + 1 == r) {
            t[v].max = data[l];
            return;
        }
        ll m = (l + r) / 2;
        build(2*v, l, m, data);
        build(2*v+1, m, r, data);
        t[v] = merge(t[2*v], t[2*v+1]);
    }

    void apply(ll v, ll add) {
        t[v].max += add;
        t[v].add += add;
    }

    void push(ll v) {
        if (t[v].add == 0) return;
        apply(2*v, t[v].add);
        apply(2*v+1, t[v].add);
        t[v].add = 0;
    }

    void upd(ll v, ll vl, ll vr, ll ql, ll qr, ll x) {
        if (ql >= vr || qr <= vl) {
            return;
        } else if (vl >= ql && vr <= qr) {
            apply(v, x);
            return;
        }
        push(v);
        ll m = (vl + vr) / 2;
        upd(2*v, vl, m, ql, qr, x);
        upd(2*v+1, m, vr, ql, qr, x);
        t[v] = merge(t[2*v], t[2*v+1]);
    }

    Node get(ll v, ll vl, ll vr, ll ql, ll qr) {
        if (ql >= vr || qr <= vl) {
            return {-1};
        } else if (vl >= ql && vr <= qr) {
            return t[v];
        }
        push(v);
        ll m = (vl + vr) / 2;
        return merge(get(2*v, vl, m, ql, qr), get(2*v+1, m, vr, ql, qr));
    }

    ll getmax() {
        return get(1, 0, sz, 0, sz).max;
    }

    void update(ll L, ll R, ll x) {
        upd(1, 0, sz, L, R, x);
    }
};


vector<ll> segs(set<pair<ll, ll>> v) {
    vector<pair<ll, ll>> events;
    for (auto [i, j] : v) {
        events.push_back({i, -1});
        events.push_back({j, 1});
    }
    sort(events.begin(), events.end());
    vector<ll> ans;
    ll t = 0;
    for (ll i = 0; i < events.size(); i++) {
        t += events[i].second;
        ans.push_back(t);
    }
    return ans;
}

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> cord;
    vector<pair<ll, ll>> v(n);
    for (ll i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        v[i] = {a, b};
        cord.push_back(a);
        cord.push_back(b);
    }
    sort(cord.begin(), cord.end());
    map<ll, ll> mp;
    for (ll x : cord) mp[x] = mp.size();
    set<pair<ll, ll>> r;
    set<pair<ll, ll>, greater<pair<ll, ll>>> l;
    for (ll i = 0; i < n; i++) {
        ll a = v[i].first;
        ll b = v[i].second;
        r.insert({mp[b], mp[a]});
        l.insert({mp[a], mp[b]});
    }
    vector<ll> start = segs(r);
    //for (ll x : start) cout << x << ' ';
    //cout << '\n';
    SegTree t(start);
    vector<ll> ans(n+1, 0);
    ll prev = t.getmax()+1;
    for (ll k = 0; k < n; k++) {
        pair<ll, ll> p1 = *r.begin();
        pair<ll, ll> p2 = *l.begin();
        pair<ll, ll> p3 = {p1.second, p2.second};
        pair<ll, ll> p4 = {p1.first, p2.first};
        t.update(p4.first, p4.second, 2);
        r.erase(p1);
        r.erase({p2.second, p2.first});
        r.insert({p3.second, p3.first});
        r.insert({p4.second, p4.first});
        l.erase({p1.second, p1.first});
        l.erase(p2);
        l.insert(p3);
        l.insert(p4);
        ll res = t.getmax();
        for (ll j = prev; j <= res; j++) {
            ans[j] = k+1;
        }
        prev = res+1;
        if (prev == n+1) break;
    }

    for (ll i = 0; i < q; i++) {
        ll k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //ios_base::sync_with_stdio(false); cin.tie(0);
    ll t = 1;
    //cin >> t;
    while(t--) solve();

    return 0;
}
