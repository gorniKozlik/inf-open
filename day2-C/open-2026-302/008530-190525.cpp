#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#pragma GCC target("avx2,bmi2")
using namespace std;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;
using ul = unsigned long long;
using ld = long double;
using lll = __int128;

struct segtree {
    ll R = 1;
    vector<ll> t, lazy;
    segtree (ll n) {
        while (R < n) R *= 2;
        t.resize(2 * R);
        lazy.resize(2 * R);
    }
    void push(ll node) {
        t[node] += lazy[node];
        if (node < R) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    void add(ll x, ll l, ll r, ll node = 1, ll nl = 0, ll nr = -1) {
        if (nr == -1) nr = R;
        if (nr <= l || nl >= r) return;
        if (l <= nl && nr <= r) {
            lazy[node] += x;
            push(node);
            return;
        }
        push(node);
        ll nm = (nl + nr) / 2;
        add(x, l, r, node * 2, nl, nm);
        add(x, l, r, node * 2 + 1, nm, nr);
        t[node] = max(t[node * 2], t[node * 2 + 1]);
    }

    ll get(ll l, ll r, ll node = 1, ll nl = 0, ll nr = -1) {
        if (nr == -1) nr = R;
        push(node);
        if (nl >= r || nr <= l) return 0;
        if (l <= nl && nr <= r) return t[node];
        ll nm = (nl + nr) / 2;
        return max(
            get(l, r, node * 2, nl, nm),
            get(l, r, node * 2 + 1, nm, nr)
            );
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n, q;
    cin >> n >> q;
    segtree t(2 * n);
    vector<ll> l(n), r(n), k(q);
    ordered_set<ll> cord;
    set<ll> ls, rs;
    for (ll i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        cord.insert(l[i]);
        cord.insert(r[i]);
        ls.insert(l[i]);
        rs.insert(r[i]);
    }
    for (ll i = 0; i < n; i++) {
        t.add(1, cord.order_of_key(l[i]), cord.order_of_key(r[i]) + 1);
    }
    ll mv = 0;
    vector<ll> ans(n, 1000);
    for (ll j = 0; j < n; j++) {
        ll res = t.get(0, 2 * n);
        ans[mv] = res;
        mv++;
        ll lq = cord.order_of_key(*rs.begin());
        ll rq = cord.order_of_key(*prev(ls.end()));
        ls.erase(prev(ls.end()));
        rs.erase(rs.begin());
        t.add(1, lq, rq + 1);
        t.add(1, lq + 1, rq + 1);
    }
    while (q--) {
        ll s;
        cin >> s;
        cout << lower_bound(ans.begin(), ans.end(), s) - ans.begin() << ' ';
    }
    cout << endl;
    return 0;
}