#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, q;
    cin >> n >> q;
    for (ll i = 0; i < n; ++i) {
        ll l;
        cin >> l >> l;
    }
    vector<ll> ans(n + 1);
    ans[1] = 0;
    ll cur = 0;
    for (ll i = 2; i < n; ++i) {
        if (i % 2 == 0) {
            cur++;
        }
        ans[i] = cur;
    }
    while (q--) {
        ll k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}
