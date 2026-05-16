#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18;

struct DO {
    vector<ll> t;
    vector<ll> u;

    DO(vector<ll> u) : u(u) {
        t.resize(u.size() * 4);
    }

    ll combine(ll a, ll b) {
        return min(a, b);
    }

    void build(ll v, ll tl, ll tr) {
        if (tl + 1 == tr) {
            t[v] = u[tl];
            return;
        }
        ll tm = (tl + tr) / 2;
        build(v * 2 + 1, tl, tm);
        build(v * 2 + 2, tm, tr);
        t[v] = combine(t[v * 2 + 1], t[v * 2 + 2]);
    }

    void update(ll v, ll tl, ll tr, ll pos, ll x) {
        if (tl + 1 == tr) {
            t[v] = min(t[v], x);
            return;
        }
        ll tm = (tl + tr) / 2;
        if (pos < tm) {
            update(v * 2 + 1, tl, tm, pos, x);
        } else {
            update(v * 2 + 2, tm, tr, pos, x);
        }
        t[v] = combine(t[v * 2 + 1], t[v * 2 + 2]);
    }

    ll query(ll v, ll tl, ll tr, ll l, ll r) {
        if (tl >= r || tr <= r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return t[v];
        }
        ll tm = (tl + tr) / 2;
        ll left = query(v * 2 + 1, tl, tm, l, r);
        ll right = query(v * 2 + 2, tm, tr, l, r);
        return combine(left, right);
    }
};

void solve() {
    ll n, m, k, x;
    cin >> n >> m >> k >> x;
    vector<ll> all;
    vector<pair<ll, ll>> arr(n);
    for (ll i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
        all.emplace_back(arr[i].first);
    }
    vector<pair<ll, ll>> sword(m);
    for (ll i = 0; i < m; ++i) {
        cin >> sword[i].first >> sword[i].second;
        all.emplace_back(sword[i].first);
    }
    sort(all.begin(), all.end());
    all.resize(distance(all.begin(), unique(all.begin(), all.end())));
    auto compress = [&](ll x) {
        return lower_bound(all.begin(), all.end(), x) - all.begin();
    };
    ll sz = all.size();
    vector<ll> tmp(sz, INF);
    DO d(tmp);
    d.build(0, 0, sz);
    for (auto [s, c] : sword) {
        s = compress(s);
        d.update(0, 0, sz, s, c);
    }
    ll bal = x;
    for (auto [h, r] : arr) {
        h = compress(h);
        ll mn = d.query(0, 0, sz, h, sz);
        if (bal < mn) {
            cout << "No";
            return;
        }
        bal += r;
        bal -= mn;
    }
    cout << "Yes\n";
}

signed main() {
    ll t = 1;
    while (t--) {
        solve();
    }
}