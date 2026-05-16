#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(2 * n);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        a[2 * i] = {l, 1};
        a[2 * i + 1] = {r, -1};
    }
    sort(a.begin(), a.end());
    int bal = 0;
    vector<int> ans(n + 1, 1e9);
    ans[0] = 0;
    int mx=0;
    for (auto [l, tp] : a) {
        bal += tp;
        ++mx;
        for (int i = bal; i <= min(mx, 2 * n - mx); i += 2) {
            ans[i] = min(ans[i], (i - bal) / 2);
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    while (q-- > 0) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
    return 0;
}