#include <bits/stdc++.h>

using ll = long long;

using namespace std;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> A, B;
    vector<ll> C;
    for (ll i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        A.push_back({a, 1});
        A.push_back({b, -1});
    }
    sort(A.begin(), A.end());
    vector<ll> Ans(100 + n + 1, n);
    ll c1 = 0, c2 = 0, c = 0;
    for (ll i = 0; i < 2 * n; i++) {
        if (A[i].second == 1) {
            c1++;
        } else {
            c2++;
        }
        for (ll j = 0; j <= c; j++) {
            Ans[j] = min(Ans[j], 0ll);
        }
        c += A[i].second;
        for (ll j = 0; j < min(c2, n - c2 - c); j++) {
            Ans[c + j * 2 + 1] = min(Ans[c + j * 2 + 1],  (j + 1));
            Ans[c + j * 2 + 2] = min(Ans[c + j * 2 + 2],  (j + 1));
        }
    }
    for (ll i = 0; i <= n; i++) {
        Ans[i] = min(Ans[i - 1] + 1, Ans[i]);
    }
    vector<ll> X(q);
    for (ll i = 0; i < q; i++) {
        cin >> X[i];
        cout << Ans[X[i]] << '\n';
    }
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
