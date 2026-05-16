#include <bits/stdc++.h>

using ll = long long;

using namespace std;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> A;
    for (ll i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        A.push_back({a, 1});
        A.push_back({b, -1});
    }
    vector<ll> X(q);
    for (ll i = 0; i < q; i++) {
        cin >> X[i];
    }
    sort(A.begin(), A.end());
    ll mn = n, c = 0;
    for (ll i = 0; i < 2 * n; i++) {
        c += A[i].second;
        mn = min(mn, n - 1 - c);
    }
    cout << mn << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll t = 1;
    //cin >> t;
    for (ll i = 0; i < t; i++) {
        solve();
    }
    return 0;
}
