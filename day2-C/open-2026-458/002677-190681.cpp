#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;


void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> v(n);
    for (ll i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }
    for (ll i = 0; i < q; i++) {
        ll k;
        cin >> k;
        cout << k-1 << ' ';
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //ios_base::sync_with_stdio(false); cin.tie(0);
    ll t = 1;
    //cin >> t;
    while(t--) solve();

    return 0;
}
