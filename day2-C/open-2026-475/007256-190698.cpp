#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        if (k != n) cout << 1 << ' ';
        else cout << 0 << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (T--) {
        solve();
        cout << '\n';
    }
    return 0;
}