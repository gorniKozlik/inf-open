#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> l(n), r(n);
    for (ll i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    while (q--) {
        ll k;
        cin >> k;
        cout << k / 2 << ' ';
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