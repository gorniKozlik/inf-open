#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll mod = 998244353;
const ll inf = 1e17;

vector<ll> tree, pref;
vector<ll> up;

void build(ll v, ll l, ll r) {
    if (r - l == 1) {
        tree[v] = pref[l];
        return;
    }
    ll mid = (l + r) / 2;
    build(2 * v, l, mid);
    build(2 * v + 1, mid, r);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

void push(ll v) {
    up[2 * v] += up[v];
    up[2 * v + 1] += up[v];
    tree[2 * v] += up[v];
    tree[2 * v + 1] += up[v];
    up[v] = 0;
}

void upd(ll v, ll l, ll r, ll ql, ll qr, ll val) {
    if (l >= ql && r <= qr) {
        tree[v] += val;
        up[v] += val;
        return;
    }
    if (l >= qr || r <= ql) return;
    ll mid = (l + r) / 2;
    push(v);
    upd(2 * v, l, mid, ql, qr, val);
    upd(2 * v + 1, mid, r, ql, qr, val);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

void solve() {
    ll n, q; cin >> n >> q;
    multiset<ll> idxl, idxr;
    vector<pair<ll, ll>> A;
    for (ll i = 0; i < n; ++i) {
        ll l, r; cin >> l >> r;
        A.push_back({l, 1});
        A.push_back({r, -1});
    }
    vector<ll> ans(n + 1, inf);
    sort(A.begin(), A.end());
    pref.assign(2 * n, 0);
    ll tec = 0;
    for (ll i = 0; i < 2 * n; ++i) {
        tec += A[i].second;
        pref[i] = tec;
        if (A[i].second == 1) idxl.insert(i);
        else idxr.insert(i);
    }
    up.assign(8 * n, 0);
    tree.assign(8 * n, 0);
    build(1, 0, n);
    ll cnt = 0;
    ans[tree[1]] = 0;
    while (*idxl.rbegin() >= *idxr.begin()) {
        cnt++;
        ll idx1 = *idxr.begin();
        ll idx2 = *idxl.rbegin();
        upd(1, 0, n, idx1, idx2, 2);
        ll res = tree[1];
        if (ans[res] == inf) ans[res] = cnt;
        idxl.insert(idx1);
        idxr.insert(idx2);
        idxl.erase(idxl.find(idx2));
        idxr.erase(idxr.find(idx1));
    }
    for (ll i = n - 1; i >= 1; --i) ans[i] = min(ans[i + 1], ans[i]);
    while (q--) {
        ll k; cin >> k;
        cout << ans[k] << ' ';
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
}