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
        B.push_back({a, b});
        A.push_back({a, 1});
        A.push_back({b, -1});
        C.push_back(a);
        C.push_back(b);
    }
    sort(C.begin(), C.end());
    map<ll, ll> M;
    for (ll i = 0; i < 2 * n; i++) {
        M[C[i]] = i;
    }
    vector<ll> X(q);
    for (ll i = 0; i < q; i++) {
        cin >> X[i];
    }
    sort(A.begin(), A.end());
    ll mn = n, c = 0;
    for (ll i = 0; i < n; i++) {
        if (M[B[i].first] < n && M[B[i].second] < n) {
            c++;
        }
    }
    cout << c << '\n';
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
