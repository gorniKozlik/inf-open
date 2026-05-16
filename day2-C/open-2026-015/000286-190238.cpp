#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    {
        vector<int> b;
        for (int i = 0; i < n; i++) {
            cin >> a[i].first >> a[i].second;
            b.push_back(a[i].first); b.push_back(a[i].second);
        }
        sort(b.begin(), b.end());
        unordered_map<int, int> ma;
        for (int i = 0; i < 2 * n; i++) {
            ma[b[i]] = i;
        }
        for (int i = 0; i < n; i++) {
            a[i].first = ma[a[i].first];
            a[i].second = ma[a[i].second];
        }
    }

    vector<int> x(2 * n - 1);
    vector<int> cnt(2 * n);
    for (auto [z, y] : a) {
        cnt[z]++;
        cnt[y]--;
    }
    int cu = 0;
    for (int i = 0; i + 1 < 2 * n; i++) {
        cu += cnt[i];
        x[i] = cu;
    }
    vector<int> ans(n + 1, 1e9);

    vector<vector<int>> dob(n + 2);
    vector<vector<int>> del(n + 2);

    for (int i = 0; i + 1 < 2 * n; i++) {
        int l = i + 1 - x[i], r = 2 * n - i - 1 - x[i];
        dob[x[i]].push_back(x[i]);
        del[x[i] + min(l, r) / 2 * 2 + 1].push_back(x[i]);
    }

    multiset<int> cur;
    for (int i = 0; i <= n; i++) {
        for (auto y : dob[i]) {
            cur.insert(y);
        }
        for (auto y : del[i]) {
            cur.erase(cur.find(y));
        }
        if (cur.empty()) continue;
        auto y = *(--cur.end());
        ans[i] = (i - y + 1) / 2;
    }

    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }

    for (int abab = 0; abab < q; abab++) {
        int r;
        cin >> r;
        cout << ans[r] << " ";
    }
}