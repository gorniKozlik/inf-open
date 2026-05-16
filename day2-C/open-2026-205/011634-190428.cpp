#include <bits/stdc++.h>
using  namespace std;
#define all(x) x.begin(), x.end()
using ll = long long;
using sll = __int128;
using ld = long double;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << k / 2 << ' ';
    }

}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}