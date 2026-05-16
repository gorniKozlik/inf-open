#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
//#pragma GCC target("avx2,bmi2")
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
            t[node * 2] += lazy[node];
            t[node * 2 + 1] += lazy[node];
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
        if (nl >= r || nr <= l) return 0;

    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n, q;
    cin >> n >> q;
    vector<ll> l(n), r(n), k(q);
    for (ll i = 0; i < n; i++) cin >> l[i] >> r[i];
    for (auto &i : k) cin >> i;
    for (auto i : k) {
        if (i == 0) cout << 0 << ' ';
        else cout << 1 << ' ';
    }

}