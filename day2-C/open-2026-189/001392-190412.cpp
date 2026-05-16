#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;
using ll = long long;

#define x first
#define y second
#define all(x) x.begin(), x.end()

void solve();

int main() {
    // cin.tie(nullptr)->sync_with_stdio(false);

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
        if (bal < n - 1 - abs(cl - (n - bal - cl))) {
            seg2.emplace_back(bal, n - 1 - abs(cl - (n - bal - cl)));
        }
    }
    multiset<int> odd, even;
    ev.clear();
    for (auto [l, r] : seg2) {
        ev.emplace_back(l, l + 1);
        ev.emplace_back(r + 1, -l - 1);
    }
    sort(all(ev));
    vector<int> ans(n, INT32_MAX / 2);
    for (int i = 0; i < mx; i++) {
        ans[i] = 0;
    }
    int ptr = 0;
    for (int i = 0; i < n; i++) {
        // cout << "!! " << i << '\n';
        while (ptr < ev.size() && ev[ptr].x == i) {
            if (ev[ptr].y < 0) {
                int val = (-ev[ptr].y) - 1;
                // cout << "erase " << val << '\n';
                if (val % 2) {
                    odd.erase(odd.find(-val));
                } else {
                    even.erase(even.find(-val));
                }
            } else {
                int val = ev[ptr].y - 1;
                // cout << "insert " << val << '\n';
                if (val % 2) {
                    odd.insert(-val);
                } else {
                    even.insert(-val);
                }
            }
            // cout << ptr << '\n';
            ptr++;
        }
        if (!odd.empty()) {
            int mx_o = -(*odd.begin());
            ans[i] = min(ans[i], (i - mx_o + 2) / 2);
        }
        if (!even.empty()) {
            int mx_e = -(*even.begin());
            ans[i] = min(ans[i], (i - mx_e + 2) / 2);
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
