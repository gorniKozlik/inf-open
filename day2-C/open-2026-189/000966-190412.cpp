#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;
using ll = long long;

#define x first
#define y second
#define all(x) x.begin(), x.end()

void solve();

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cout << fixed << setprecision(20);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> seg(n);
    vector<pair<int, int>> ev;
    for (int i = 0; i < n; i++) {
        cin >> seg[i].x >> seg[i].y;
        ev.emplace_back(seg[i].x, 1);
        ev.emplace_back(seg[i].y + 1, -1);
    }
    sort(all(ev));
    int mx = 0, bal = 0, cl = 0;
    vector<pair<int, int>> seg2;
    for (auto [c, v] : ev) {
        bal += v;
        mx = max(mx, bal);
        if (v == -1) cl++;
        seg2.emplace_back(bal, n - 1 - abs(cl - (n - bal - cl)));
    }
    vector<int> ans(n, INT32_MAX / 2);
    for (int i = 0; i < mx; i++) {
        ans[i] = 0;
    }
    for (auto [l, r] : seg2) {
        for (int i = l; i <= r; i++) {
            ans[i] = min(ans[i], (i - l + 2) / 2);
        }
    }
    for (int i = 0; i < n - 1; i++) {
        ans[i + 1] = min(ans[i + 1], ans[i] + 1);
    }
    while (q--) {
        int k;
        cin >> k; k--;
        cout << ans[k] << ' ';
    }
    cout << '\n';
}
