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
    ll mx = 0;
    vector<ll> C1(100 + n, n), C2(100 + n, n);
    ll mx1 = 0, mx2 = 0;
    for (ll i = 0; i < 2 * n; i++) {
        if (A[i].second == 1) {
            c1++;
        } else {
            c2++;
        }
        mx = max(mx, c);
        c += A[i].second;
        if (c % 2 == 1) {
            C1[c + 1]++;
            C1[c + min(c2, n - c2 - c) * 2 + 1]--;
        } else {
            C2[c + 1]++;
            C2[c + min(c2, n - c2 - c) * 2 + 1]--;
        }
        mx1 = max(mx1, c);
        mx2 = max(mx2, c + min(c2, n - c2 - c));
    }
    for (ll j = 0; j <= mx; j++) {
        Ans[j] = min(Ans[j], 0ll);
    }
    c1 = 0;
    mx1 = 0;
    for (ll j = 2; j < n; j += 2) {
        c1 += C1[j];
        if (c1 > 0) {
            Ans[(j ) * 2 + 1] = min(Ans[(j ) * 2 + 1],  Ans[(j - 1) * 2 + 1] + 1);
            Ans[ (j ) * 2 + 2] = min(Ans[(j ) * 2 + 2],  Ans[ (j - 1) * 2 + 1] + 1);
        }
    }
    c1 = 0;
    for (ll j = 1; j < n; j += 2) {
        c1 += C2[j];
        if (c1 > 0) {
            Ans[mx1 + (j ) * 2 + 1] = min(Ans[mx1 + (j) * 2 + 1],  Ans[mx1 + (j - 1) * 2 + 1] + 1);
            Ans[mx1 + (j ) * 2 + 2] = min(Ans[mx1 + (j) * 2 + 2],  Ans[mx1 + (j - 1) * 2 + 1] + 1);
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
