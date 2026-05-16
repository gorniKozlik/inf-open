#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Segtree {
    vector<ll> tree;
    ll sz;

    void build(ll n) {
        sz = 1;
        while (sz < n) {
            sz *= 2;
        }
        tree.resize(sz * 2 - 1);
    }

    void update(ll v, ll l, ll r, ll q) {
        if (l > q || r <= q) {
            return;
        }
        if (r - l == 1) {
            tree[v]++;
            return;
        }
        ll m = (l + r) / 2;
        update(v * 2 + 1, l, m, q);
        update(v * 2 + 2, m, r, q);
        tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
    }

    ll get(ll v, ll l, ll r, ll lq) {
        if (r <= lq) {
            return 0;
        }
        if (l >= lq) {
            return tree[v];
        }
        ll m = (l + r) / 2;
        return get(v * 2 + 1, l, m, lq) + get(v * 2 + 2, m, r, lq);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, q;
    cin >> n >> q;
    vector<ll> l(n), r(n);
    map<ll, ll> mp;
    for (ll i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        mp[l[i]];
        mp[r[i]];
    }
    ll sz = 0;
    for (auto &i: mp) {
        i.second = sz;
        sz++;
    }
    set<pair<ll, ll> > sl, sr;
    for (ll i = 0; i < n; ++i) {
        l[i] = mp[l[i]];
        r[i] = mp[r[i]];
        sl.emplace(l[i], r[i]);
        sr.emplace(r[i], l[i]);
    }
    Segtree tree;
    tree.build(sz);
    ll last = 0;
    for (auto i: sl) {
        tree.update(0, 0, tree.sz, i.second);
        ll g = tree.get(0, 0, tree.sz, i.first);
        last = max(last, g);
    }
    vector<ll> ans(n + 1);
    ll cur = 0;
    while (1) {
        cur++;
        auto il = sl.end();
        il--;
        auto l = *il;
        auto ir = sr.begin();
        auto r = *ir;
        if (l.first < r.first) {
            break;
        }
        pair<ll, ll> nl = {r.first, l.first}, nr = {r.second, l.second};
        sl.erase(l);
        sl.erase({r.second, r.first});
        sr.erase({l.second, l.first});
        sr.erase(r);
        sl.emplace(nl);
        sl.emplace(nr);
        sr.emplace(nl.second, nl.first);
        sr.emplace(nr.second, nr.first);
        Segtree t;
        t.build(sz);
        ll mx = 0;
        for (auto i: sl) {
            t.update(0, 0, t.sz, i.second);
            ll g = t.get(0, 0, t.sz, i.first);
            mx = max(mx, g);
        }
        for (ll i = last + 1; i <= mx; ++i) {
            ans[i] = cur;
        }
        last = mx;
    }
    while (q--) {
        ll k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}
