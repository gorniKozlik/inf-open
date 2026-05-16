#include <bits/stdc++.h>

using namespace std;
using ll = long long;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int> > seg(n);
    vector<int> len;
    for (int i = 0; i < n; i++) {
        cin >> seg[i].first >> seg[i].second;
        len.push_back(seg[i].first);
        len.push_back(seg[i].second);
    }
    std::sort(len.begin(), len.end());
    for (auto &[u, v] : seg) {
        u = lower_bound(len.begin(), len.end(), u) - len.begin();
        v = lower_bound(len.begin(), len.end(), v) - len.begin();
    }
    vector<int> ev(2 * n, 0);
    for (auto [u, v] : seg) {
        ev[u] = 1;
        ev[v] = -1;
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        int cl = 0;
        int op = 0;
        int ans = 1e9;
        for (int j = 0; j < 2 * n - 1; j++) {
            if (ev[j] == 1) {
                op++;
            }
            if (ev[j] == -1) {
                cl++;
                op--;
            }
            if (k <= op) {
                ans = 0;
                break;
            }
            if (k - op <= 2 * min(cl, n - op - cl) && min(cl, n - op - cl) >= 0) {
                ans = min(ans, (k - op + 1) / 2);
            }
        }
        if (ans == 1e9) {assert(0);
        }
        cout << ans << ' ';
    }
}
