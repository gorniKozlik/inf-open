#include<bits/stdc++.h>
//#include<bits/extc++.h>
//using namespace __gnu_pbds;
using namespace std;
using ll = long long;
//using oset = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;


/*
struct segtree{
    vector<ll> tree;
    ll sz;
    ll def = 0;
    ll merg(ll a, ll b) {
        return a + b;
    }
    void clar(ll n) {
        tree.assign(4 * n, def);
        sz = n;
    }
    segtree() {

    }
    void build(ll v, ll l, ll r, vector<ll> & a) {
        if (r - l == 1) {
            tree[v] = a[l];
            return;
        }
        ll m = (l + r) / 2;
        build(v * 2 + 1, l, m, a);
        build(v * 2 + 2, m, r, a);
        tree[v] = merg(tree[v * 2 + 1], tree[v * 2 + 2]);
    }
    segtree(vector<ll> & a) {
        ll n = (ll)a.size();
        clar(n);
        build(0, 0, sz, a);
    }
};
*/

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> ve;
    for (ll i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        ve.push_back({l, 1});
        ve.push_back({r, 0});
    }
    sort(ve.begin(), ve.end());
    ll vse = n;
    ll lef = 0;
    ll cur = 0;
    vector<ll> ans(n + 1, 1e9);
    for (auto [a, b] : ve) {
        if (b == 1) {
            cur++;
        } else {
            lef++;
            cur--;
        }
        ll rig = vse - lef - cur;
        ll r = min(lef, rig) * 2 + cur;
        for (ll i = 1; i <= r; i++) {
            ans[i] = min(ans[i], (i - cur + 1) / 2);
        }
    }
    for (ll i = 0; i < q; i++) {
        ll c;
        cin >> c;
        cout << max(0ll, ans[c]) << " ";
    }
}

signed main() {
    int MULTITEST = 0;
    #ifdef zapvm
        MULTITEST = 1;
        freopen("in.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    if (MULTITEST) {
        cin >> t;
    }
    while (t--) {
        solve();
    }
}