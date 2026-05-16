#include <iostream>
#include <set>
#include <map>
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
    vector<vector<int>> scnl(n + 10);

    for (auto [l, tp] : a) {
        bal += tp;
        ++mx;
        int L = bal;
        int R = min(mx, 2 * n - mx) + 2;
        R = min(R, n + 1);
        scnl[L].emplace_back(L);
        scnl[R].emplace_back(L);
    }
    multiset<int> best;
    for (int i = 0; i <= n; i += 2) {
        for (int x : scnl[i]) {
            if (x == i) {
                best.insert(x);
            } else {
                if (best.count(x)) {
                    best.erase(best.find(x));
                }
            }
        }
        if (!best.empty()) {
            ans[i] = min(ans[i], (i - *best.rbegin()) / 2);
        }
    }
    best.clear();
    for (int i = 1; i <= n; i += 2) {
        for (int x : scnl[i]) {
            if (x == i) {
                best.insert(x);
            } else if (best.count(x)) {
                best.erase(best.find(x));
            }
        }
        if (!best.empty()) {
            ans[i] = min(ans[i], (i - *best.rbegin()) / 2);
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