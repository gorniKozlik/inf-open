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
    for (auto &[u, v]: seg) {
        u = lower_bound(len.begin(), len.end(), u) - len.begin();
        v = lower_bound(len.begin(), len.end(), v) - len.begin();
    }
    vector<int> ev(2 * n, 0);
    for (auto [u, v]: seg) {
        ev[u] = 1;
        ev[v] = -1;
    }
    vector<int> ans(n + 1, 1e9);
    multiset<int> kl;
    vector<vector<int> > d(2 * n + 1);
    int cl = 0;
    int op = 0;
    for (int j = 0; j < 2 * n - 1; j++) {
        if (ev[j] == 1) {
            op++;
        }
        if (ev[j] == -1) {
            cl++;
            op--;
        }
        kl.insert(op);
        d[op + 2 * min(cl, n - op - cl)].push_back(op);
    }
    for (int k = 1; k <= n; k++) {
        int m = *kl.rbegin();
        if (k <= m) {
            ans[k] = 0;
        } else {
            ans[k] = (k - m + 1) / 2;
        }
        for (auto elem : d[k]) {
            kl.erase(kl.find(elem));
        }
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}