#include <bits/stdc++.h>

// #pragma GCC optimize("Ofast")

using namespace std;

using ll = long long;
using ld = long double;

constexpr long long INF = 1e18, MOD = 1e9 + 7;

struct DO {
    vector<ll> tree, a;
    void build(ll v, ll l, ll r) {
        if (r - l == 1) {
            tree[v] = a[l];
            return;
        }
        ll m = (l + r) / 2;
        build(v * 2 + 1, l, m);
        build(v * 2 + 2, m, r);
        tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
    }
    ll get(ll v, ll l, ll r, ll ql, ll qr) {
        if (ql <= l and r <= qr) {
            return tree[v];
        }
        if (r <= ql or qr <= l) {
            return -INF;
        }
        ll m = (l + r) / 2;
        return max(get(v * 2 + 1, l, m, ql, qr), get(v * 2 + 2, m, r, ql, qr));
    }
    void upd(ll v, ll l, ll r, ll ind, ll x) {
        if (r - l == 1) {
            tree[v] = x;
            return;
        }
        ll m = (l + r) / 2;
        if (ind < m) {
            upd(v * 2 + 1, l, m, ind, x);
        }
        else {
            upd(v * 2 + 2, m, r, ind, x);
        }
        tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> p;
    vector<ll> sg;
    for (ll i = 0; i < n; ++i) {
        ll l, r;
        cin >> l >> r;
        p.push_back({l, r});
        sg.push_back(l);
        sg.push_back(r);
    }
    sort(sg.begin(), sg.end());
    sg.erase(unique(sg.begin(), sg.end()), sg.end());
    for (auto &[l, r] : p) {
        l = lower_bound(sg.begin(), sg.end(), l) - sg.begin();
        r = lower_bound(sg.begin(), sg.end(), r) - sg.begin();
    }
    sort(p.begin(), p.end());
    vector<pair<ll, ll>> ev(2 * n);
    vector<ll> a(2 * n);
    vector<ll> ad(2 * n + 1);
    for (auto u : p) {
        ad[u.first]++;
        ad[u.second + 1]--;
    }
    ll ot = 0;
    for (ll i = 0; i < n * 2; ++i) {
        ot += ad[i];
        a[i] = ot;
    }
    DO do1;
    do1.a = a;
    do1.tree.resize(8 * n);
    do1.build(0, 0, n * 2);
    while (q--) {
        ll k;
        cin >> k;
        ll l = k - 1;
        ll r = 2 * n - k;
        ll x = do1.get(0, 0, 2 * n, l, r + 1);
        if (x >= k) {
            cout << 0;
        }
        else {
            cout << (k - x + 1) / 2;
        }
        cout << " ";
    }
}

