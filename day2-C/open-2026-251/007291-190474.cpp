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
    int ans = 0;
    std::sort(len.begin(), len.end());
    for (auto &[u, v] : seg) {
        u = lower_bound(len.begin(), len.end(), u) - len.begin();
        v = lower_bound(len.begin(), len.end(), v) - len.begin();
        if (v < n) {
            ans++;
        }
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << ans << ' ';
    }
}
