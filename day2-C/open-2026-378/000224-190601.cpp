#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, q; cin >> n >> q;
    vector<pair<int, int>> X(n);
    for (auto& [x, y] : X) cin >> x >> y;
    vector<pair<int, int>> T;
    for (auto [x, y] : X) T.push_back({x, -1}), T.push_back({y, 1});
    ranges::sort(T);
    vector<int> Xs;
    for (auto [x, y] : X) Xs.push_back(x), Xs.push_back(y);
    ranges::sort(Xs);
    while (q--) {
        int k; cin >> k;
        int mn = Xs[k - 1], mx = Xs[Xs.size() - k];
        int cnt = 0, ans = 0;
        for (auto& [x, t] : T) {
            cnt -= t;
            if (mn <= x and x <= mx) ans = max(ans, cnt);
        }
        cout << max(0, (k - ans) / 2 + (k - ans) % 2) << '\n';
    }
    return 0;
}
