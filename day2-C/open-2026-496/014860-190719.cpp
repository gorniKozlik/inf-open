#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> arr;
    for (ll i = 0; i < n; ++i) {
        ll l, r;
        cin >> l >> r;
        arr.emplace_back(l, r);
    }
    vector<pair<ll, ll>> event;
    set<ll> all;
    for (auto [l, r] : arr) {
        event.emplace_back(l, 1);
        event.emplace_back(r, -1);
        all.emplace(l);
        all.emplace(r);
    }
    for (ll x : all) {
        event.emplace_back(x, 0);
    }
    sort(event.begin(), event.end(), [&](pair<ll, ll>& a, pair<ll, ll>& b){
        if (a.first == b.first) {
            return a.second < b.second;
        }
        return a.first < b.first;
    });
    ll mx = 0;
    ll cnt = 0;
    for (auto [x, type] : event) {
        cnt += type;
        mx = max(mx, cnt);
    }
    vector<ll> ans(n + 1);
    for (ll i = 1; i <= n; ++i) {
        if (mx > i) {
            ans[i] = 0;
            continue;
        }
        ans[i] = (i - mx + 1) / 2;
    }
    while (q--) {
        ll x;
        cin >> x;
        cout << ans[x] << '\n';
    }
}

signed main() {
    ll t = 1;
    while (t--) {
        solve();
    }
}