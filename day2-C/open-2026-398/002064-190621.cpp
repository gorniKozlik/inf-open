//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define ld long double
using namespace std;
using namespace __gnu_pbds;
// gp_hash_table<int, int>table;
typedef tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update>
ordered_set;
//find_by_order(x) - итератор на k по величине элемент
//order_of_key(x) - колво элементов в множестве строго меньших чем наш элемент

const ll MOD = 998244353;
ll binpow(ll a, ll n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return a % MOD;
    }
    ll g = binpow(a, n / 2);
    if (n % 2 == 0) {
        return (g * g) % MOD;
    }
    return (((g * g) % MOD) * a) % MOD;
}

struct obj {
    ll l, r;
    bool isClosed;
};


void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll,ll> > lr(n);
    vector<ll> lb;
    for (ll i = 0; i < n; ++i) {
        cin >> lr[i].first >> lr[i].second;
        lb.push_back(lr[i].first);
    }
    sort(lb.begin(), lb.end());
    vector<obj> sq;
    for (ll i = 0; i < n; ++i) {
        sq.push_back({lr[i].first, lr[i].second, false});
        sq.push_back({lr[i].first, lr[i].second, true});
    }
    sort(sq.begin(), sq.end(), [](obj a, obj b) {
        ll x1, x2;
        if (!a.isClosed) {
            x1 = a.l;
        } else {
            x1 = a.r;
        }
        if (!b.isClosed) {
            x2 = b.l;
        } else {
            x2 = b.r;
        }
        if (x1 == x2) {
            return a.isClosed < b.isClosed;
        }
        return x1 < x2;
    });
    ll cnt = 0;
    ll mxcnt = 0;
    ll cntl = 0;
    vector<pair<ll, pair<ll,ll> > > cs;
    for (auto &i: sq) {
        ll x;
        if (!i.isClosed) {
            x = i.l;
        } else {
            x = i.r;
        }
        ll cntr = lb.end() - upper_bound(lb.begin(), lb.end(), x);
        if (!i.isClosed) {
            ++cnt;
        } else {
            ++cntl;
            --cnt;
        }
        cs.push_back({cnt, {cntl, cntr}});
    }
    while (q--) {
        ll k;
        cin >> k;
        if (k == 1) {
            cout << 0 << '\n';
            continue;
        }
        ll bestans = LLONG_MAX;
        for (auto &c: cs) {
            ll ans = 0;
            ll ct = c.first, ctl = c.second.first, ctr = c.second.second;
            ll ost = k - ct;
            if (2 * min(ctl, ctr) >= ost) {
                ans += ost / 2 + ost % 2;
            } else {
                ans += min(ctl, ctr);
                ost -= 2 * min(ctl, ctr);
                ans += ost;
            }
            bestans = min(bestans, ans);
        }
        cout << bestans << '\n';
    }
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
#ifndef LOCAL
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
#endif
    ll t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
