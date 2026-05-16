#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
using ll = long long;

using oset = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

void Solve();

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ll tt = 1;
    // cin >> tt;
    while (tt--) {
        Solve();
    }
    return 0;
}

# define ff first
# define ss second

const ll inf = 1e15;

void Solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> a(n);
    for (auto &x : a) cin >> x.ff >> x.ss;
    vector<pair<ll, ll>> b(q);
    for (ll i = 0; i < q; ++i) {
        cin >> b[i].ff;
        b[i].ss = i;
    }
    sort(b.begin(), b.end(), [&](auto f, auto s) {
        return f.ff < s.ff;
    });
    ll cntl = 0, cntf = 0;
    vector<pair<ll, ll>> a1 = a;
    vector<ll> pon;
    for (auto &x : a) {
        pon.push_back(x.ff);
        pon.push_back(x.ss);
    }
    sort(a.begin(), a.end(), [&](auto f, auto s) {
        return f.ff < s.ff;
    });
    sort(a1.begin(), a1.end(), [&](auto f, auto s) {
        return f.ss < s.ss;
    });
    sort(pon.begin(), pon.end());
    vector<ll> ans(n, inf);
    for (ll i = 0; i < pon.size(); ++i) {
        while (cntl < n && a[cntl].ff <= pon[i]) cntl++;
        while (cntf < n && a1[cntf].ss <= pon[i]) cntf++;
        for (ll j = 0; j < q; ++j) {
            if (min(i + 1, n * 2 - i) < b[j].ff) continue;
            ans[b[j].ss] = min(ans[b[j].ss], (b[j].ff - (cntl - cntf) + 1) / 2);
        }
    }
    for (auto &x : ans) cout << x << ' ';
    cout << '\n';
}