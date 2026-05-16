#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;

constexpr ll maxn = 200001;
ll tr[maxn * 4];
ll late[maxn * 4];

void push(ll v, ll l, ll r) {
    if (late[v] == 0) return;
    tr[v] += late[v];
    if (r - l != 1) {
        late[2 * v + 1] += late[v];
        late[2 * v + 2] += late[v];
    }
    late[v] = 0;
}

void upd(ll v, ll l, ll r, ll ql, ll qr, ll x) {
    push(v, l, r);
    if (r <= ql || l >= qr) return;
    if (r <= qr && l >= ql) {
        late[v] += x;
        push(v, l, r);
        return;
    }
    ll m = (r + l) / 2;
    upd(2 * v + 1, l, m, ql, qr, x);
    upd(2 * v + 2, m, r, ql, qr, x);
    tr[v] = max(tr[2 * v + 1], tr[2 * v + 2]);
}

ll get(ll v, ll l, ll r, ll ql, ll qr) {
    push(v, l, r);
    if (r <= ql || l >= qr) return 0;
    if (l >= ql && r <= qr) return tr[v];
    ll m = (r + l) / 2;
    return max(get(2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
}

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> l(n), r(n);
    vector<ll> b;
    for (ll i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        b.push_back(l[i]);
        b.push_back(r[i]);
    }
    sort(b.begin(), b.end());
    for (ll i = 0; i < n; i++) {
        l[i] = lower_bound(b.begin(), b.end(), l[i]) - b.begin();
        r[i] = lower_bound(b.begin(), b.end(), r[i]) - b.begin();
    }
    vector<pair<ll, ll>> lg, rg;
    for (ll i = 0; i < n; i++) {
        lg.push_back({l[i], i});
        rg.push_back({r[i], i});
    }
    sort(lg.begin(), lg.end());
    sort(rg.begin(), rg.end());
    reverse(rg.begin(), rg.end());
    vector<ll> mn(n + 1, 1e17);
    ll cur = 0;
    for (ll i = 0; i < n; i++) {
        upd(0, 0, maxn, l[i], r[i], 1);
    }
    {
        ll mx = get(0, 0, maxn, 0, b.size());
        mn[mx] = cur;
    }
    vector<bool> used(n, 0);
    while (lg.size() > 0 && rg.size() > 0 && lg.back().first > rg.back().first) {
        if (used[lg.back().second] || used[rg.back().second]) {
            lg.pop_back(), rg.pop_back();
            continue;
        }
        cur++;
        ll lf = lg.back().first;
        ll rf = rg.back().first;
        used[lg.back().second] = 1;
        used[rg.back().second] = 1;
        upd(0, 0, maxn, rf + 1, lf, 2);
        upd(0, 0, maxn, rf, rf + 1, 1);
        upd(0, 0, maxn, lf, lf + 1, 1);
        ll mx = get(0, 0, maxn, 0, b.size());
        // cout << mx << lg.back().second << ' ' << rg.back().second << ' ' << endl;
        mn[mx] = min(mn[mx], cur);
        lg.pop_back(), rg.pop_back();
    }
    for (ll i = n - 1; i >= 0; i--) {
        mn[i] = min(mn[i], mn[i + 1]);
    }
    while (q--) {
        ll x;
        cin >> x;
        cout << mn[x] << ' ';
    }
}

signed main() {
    // #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // #endif
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    ll t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}