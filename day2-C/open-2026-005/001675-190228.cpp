#include <bits/stdc++.h>

#define int long long

using namespace std;

using pii = pair<int, int>;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int Q, n;
    cin >> Q >> n;
    vector<pii> e(2 * n);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        e[2 * i] = {l, -1};
        e[2 * i + 1] = {r, 1};
    }
    sort(e.begin(), e.end());

    vector<int> ans(n + 1);
    vector<pii> f;

    int bal = 0, L = 0, R = n;
    for (int i = 0; i < 2 * n; i++) {
        auto [x, op] = e[i];
        if (op == -1) {
            bal++;
            R--;
        } else {
            bal--;
            L++;
        }
        f.push_back({bal, min(L, R)});
    }

    sort(f.begin(), f.end());
    priority_queue<pii, vector<pii>, greater<pii>> q;
    int fi = 0;
    for (int i = 0; i <= n; i++) {
        while (fi < f.size() && f[fi].first == i) {
            q.push({-i, i + f[fi].second * 2});
            fi++;
        }
        while (!q.empty() && q.top().second < i) {
            q.pop();
        }
        if (!q.empty()) ans[i] = q.top().first;
    }

    for (int i = 0; i <= n; i++) {
        ans[i] = (ans[i] + i + 1) / 2;
    }

    while (Q--) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
    cout << "\n";
}
