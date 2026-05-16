#include <bits/stdc++.h>
using namespace std;
using ll = int;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> arr(n);
    for (ll i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
    }
    while (q--) {
        ll k;
        cin >> k;
        cout << k / 2 << ' ';
    }
}

signed main() {
    ll t = 1;
    while (t--) {
        solve();
    }
}