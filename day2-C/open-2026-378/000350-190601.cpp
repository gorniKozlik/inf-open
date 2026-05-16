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
    vector<int> ans(n + 1); int cnt = 0, C = 0;
    for (auto& [x, t] : T) {
        C++;
        cnt -= t;
        int r = C < n ? C : 2 * n - C;
        ans[r] = max(ans[r], cnt);
    }
    for (int i = n - 1; i >= 0; i--) ans[i] = max(ans[i], ans[i + 1]);
    while (q--) {
        int k; cin >> k;
        cout << max(0, (k - ans[k]) / 2 + (k - ans[k]) % 2) << '\n';
    }
    return 0;
}
