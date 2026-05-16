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
    vector<pair<int, int>> evs;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        evs.emplace_back(a[i].first, -1);
        evs.emplace_back(a[i].second, 1);
    }
    sort(all(evs));
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        int bal = 0;
        int ans = n;
        int l = 0;
        int r = n;
        for (auto[x, st]:evs) {
            if (st == -1) {
                bal++;
                r--;
                if (k - bal <= min(l, r) * 2) {
                    ans = min(ans, (k - bal + 1) / 2);
                }
            }
            else {
                bal--;
                l++;
                if (k - bal <= min(l, r) * 2) {
                    ans = min(ans, (k - bal + 1) / 2);
                }
            }
        }
        cout << max(ans, 0) << ' ';
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